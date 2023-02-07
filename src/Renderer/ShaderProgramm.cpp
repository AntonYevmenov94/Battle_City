#include "ShaderProgramm.h"
#include <iostream>

Renderer::ShaderProgramm::ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint vertexShaderID;
	if (!createShared(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
	{
		std::cerr << "VERTEX SHADERE compile time error" << std::endl;
		return;
	}

	GLuint fragmentShaderID;
	if (!createShared(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
	{
		std::cerr << "FRAGMENT SHADERE compile time error" << std::endl;
		glDeleteShader(vertexShaderID);
		return;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShaderID);
	glAttachShader(m_ID, fragmentShaderID);
	glLinkProgram(m_ID);

	GLint success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infolog[1024];
		glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
		std::cerr << "Error::SHADER: Link time error:\n" << infolog << std::endl;
	}
	else
		m_isCompiled = true;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

Renderer::ShaderProgramm& Renderer::ShaderProgramm::operator=(ShaderProgramm&& shaderProgramm) noexcept
{
	glDeleteShader(m_ID);
	m_ID = shaderProgramm.m_ID;
	m_isCompiled = shaderProgramm.m_isCompiled;

	shaderProgramm.m_ID = 0;
	shaderProgramm.m_isCompiled = false;

	return *this;
}

Renderer::ShaderProgramm::ShaderProgramm(ShaderProgramm&& shaderProgramm) noexcept
{
	m_ID = shaderProgramm.m_ID;
	m_isCompiled = shaderProgramm.m_isCompiled;

	shaderProgramm.m_ID = 0;
	shaderProgramm.m_isCompiled = false;
}

bool Renderer::ShaderProgramm::createShared(const std::string& source, const GLenum shaderType, GLuint& shaderID)
{
	shaderID = glCreateShader(shaderType);
	const char* code = source.c_str();
	glShaderSource(shaderID, 1, &code, nullptr);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infolog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
		std::cerr << "Error::SHADER: Compile time error:\n" << infolog << std::endl;
		return false;
	}
	return true;
}

void Renderer::ShaderProgramm::Use() const
{
	glUseProgram(m_ID);
}

Renderer::ShaderProgramm::~ShaderProgramm()
{
	glDeleteProgram(m_ID);
}
