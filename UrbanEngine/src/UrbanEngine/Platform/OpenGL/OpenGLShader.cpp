#include "OpenGLShader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace UrbanEngine
{
	std::string ReadFileContent(const std::string& file)
	{
		std::ifstream file_handler(file);
		std::stringstream ret;
		
		if (file_handler.is_open())
		{
			ret << file_handler.rdbuf();
		}
		else
		{
			throw OpenGLShader::NotFoundError(__LINE__, __FILE__, file);
		}
		
		return ret.str();
	}

	OpenGLShader::OpenGLShader(Graphics* gfx, const std::string& vsFile, const std::string& fsFile)
		:
		Shader(gfx, vsFile, fsFile)
	{
		m_ProgramID = glCreateProgram();
		
		AttachShader(vsFile, GL_VERTEX_SHADER);
		AttachShader(fsFile, GL_FRAGMENT_SHADER);

		LinkProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ProgramID);
	}
	
	void OpenGLShader::Bind()
	{
		glUseProgram(m_ProgramID);
	}

	void OpenGLShader::SetUniformMat4(const std::string& varName, const glm::mat4& value) const noexcept
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, varName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetIntArray(const std::string& varName, int* array, int arraySize) const noexcept
	{
		glUniform1iv(glGetUniformLocation(m_ProgramID, varName.c_str()), arraySize, array);
	}

	void OpenGLShader::AttachShader(const std::string& file, unsigned int type)
	{
		// Read glsl source file
		std::string file_content = ReadFileContent(file);
		const char* src = file_content.c_str();

		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		// Compile errors
		int isCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		
		// Couldn't compiled! Throw exception
		if (!isCompiled)
		{
			int logLen;
			char* log;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
			log = (char*)malloc(logLen);
			glGetShaderInfoLog(shader, logLen, &logLen, log);
			
			throw CompileError(__LINE__, __FILE__, file, log);
		}

		// Everything is ok, attach shader to the program
		glAttachShader(m_ProgramID, shader);

		// We won't use the shader again, we already attached it. So we can delete it
		glDeleteShader(shader);
	}
	
	void OpenGLShader::LinkProgram()
	{
		glLinkProgram(m_ProgramID);

		// Is it linked?
		int isLinked;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &isLinked);

		// Couldn't linked! Throw an exception
		if (!isLinked)
		{
			int logLen;
			char* log;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &logLen);
			log = (char*)malloc(logLen);
			glGetProgramInfoLog(m_ProgramID, logLen, &logLen, log);

			throw LinkError(__LINE__, __FILE__, m_ProgramID, log);
		}
	}
	
	OpenGLShader::CompileError::CompileError(int line, const char* file, const std::string& glslFile, const std::string& infoLog)
		:
		UrbanException(line, file),
		m_Glslfile(glslFile),
		m_InfoLog(infoLog)
	{
	}
	
	const char* OpenGLShader::CompileError::what() const noexcept
	{
		std::ostringstream oss;

		oss << GetType() << std::endl
			<< "[GLSL Source File] " << m_Glslfile << std::endl
			<< "\n[GPU Log] " << std::endl << m_InfoLog << std::endl
			<< "\n" << GetOriginString();
		
		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}

	const char* OpenGLShader::CompileError::GetType() const noexcept
	{
		return "UrbanEngine OpenGL Graphics Shader Compilation Error";
	}

	std::string OpenGLShader::CompileError::GetGLSLsrcFile() const noexcept
	{
		return m_Glslfile;
	}

	std::string OpenGLShader::CompileError::GetGPULog() const noexcept
	{
		return m_InfoLog;
	}
	
	
	OpenGLShader::LinkError::LinkError(int line, const char* file, unsigned int programID, const std::string& infoLog)
		:
		UrbanException(line, file),
		m_ProgramID(programID),
		m_InfoLog(infoLog)
	{
	}
	
	const char* OpenGLShader::LinkError::what() const noexcept
	{
		std::ostringstream oss;

		oss << GetType() << std::endl
			<< "[Program ID] 0x" << std::hex << std::uppercase << m_ProgramID
			<< std::dec << " (" << m_ProgramID << ")" << std::endl
			<< "\n[GPU Log]" << std::endl << m_InfoLog << std::endl
			<< "\n" << GetOriginString();

		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	
	const char* OpenGLShader::LinkError::GetType() const noexcept
	{
		return "UrbanEngine OpenGL Graphics Shader Program Linkage Error";
	}
	
	unsigned int OpenGLShader::LinkError::GetProgramID() const noexcept
	{
		return m_ProgramID;
	}
	
	std::string OpenGLShader::LinkError::GetGPULog() const noexcept
	{
		return m_InfoLog;
	}
	
	OpenGLShader::NotFoundError::NotFoundError(int line, const char* file, const std::string& path)
		:
		UrbanException(line, file),
		m_NotFoundPath(path)
	{
	}
	const char* OpenGLShader::NotFoundError::what() const noexcept
	{
		std::ostringstream oss;

		oss << GetType() << std::endl
			<< "[File Not Found] " << GetNotFoundPath() << std::endl
			<< "\n" << GetOriginString();

		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* OpenGLShader::NotFoundError::GetType() const noexcept
	{
		return "OpenGL Shader File Not Found";
	}
	std::string OpenGLShader::NotFoundError::GetNotFoundPath() const noexcept
	{
		return m_NotFoundPath;
	}
}
