#pragma once
#include <string>
#include <glad/glad.h>

namespace Renderer
{
	class ShaderProgramm
	{
		bool m_isCompiled = false;
		GLuint m_ID = 0;

		bool createShared(const std::string& source, const GLenum shaderType, GLuint& shaderID);
	public:
		ShaderProgramm() = delete;
		ShaderProgramm(ShaderProgramm&) = delete;
		ShaderProgramm& operator =(const ShaderProgramm&) = delete;

		ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader);

		ShaderProgramm& operator= (ShaderProgramm&& shaderProgramm) noexcept;
		ShaderProgramm(ShaderProgramm&& shaderProgramm) noexcept;
		
		bool isCompiled() const { return m_isCompiled; }

		void Use() const;

		~ShaderProgramm();
	};
}
