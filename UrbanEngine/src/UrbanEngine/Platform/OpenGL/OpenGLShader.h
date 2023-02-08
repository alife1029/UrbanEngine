#pragma once

#include "UrbanEngine/Graphics/Shader.h"
#include "UrbanEngine/UrbanException.h"

#include <glm/glm.hpp>

namespace UrbanEngine
{
	class OpenGLShader : public Shader
	{
	public:
		class NotFoundError : public UrbanException
		{
		public:
			NotFoundError(int line, const char* file, const std::string& path);
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept override;

			std::string GetNotFoundPath() const noexcept;

		private:
			std::string m_NotFoundPath;
		};

		class CompileError : public UrbanException
		{
		public:
			CompileError(int line, const char* file, const std::string& glslFile, const std::string& infoLog);
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept override;

			std::string GetGLSLsrcFile() const noexcept;
			std::string GetGPULog() const noexcept;
		private:
			std::string m_Glslfile;
			std::string m_InfoLog;
		};

		class LinkError : public UrbanException
		{
		public:
			LinkError(int line, const char* file, unsigned int programID, const std::string& infoLog);
			const char* what() const noexcept override;
			virtual const char* GetType() const noexcept override;

			unsigned int GetProgramID() const noexcept;
			std::string GetGPULog() const noexcept;
		private:
			unsigned int m_ProgramID;
			std::string m_InfoLog;
		};

	public:
		OpenGLShader(Graphics* gfx, const std::string& vsFile, const std::string& fsFile);
		~OpenGLShader();
		void Bind() override;

		void SetUniformMat4(const std::string& varName, const glm::mat4& value) const noexcept;
		void SetIntArray(const std::string& varName, int* array, int arraySize) const noexcept;

	private:
		void AttachShader(const std::string& shaderFile, unsigned int type);
		void LinkProgram();

	private:
		unsigned int m_ProgramID;
	};
}
