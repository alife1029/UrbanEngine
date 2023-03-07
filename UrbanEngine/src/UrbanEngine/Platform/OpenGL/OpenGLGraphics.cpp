#include "urbanpch.h"
#include "OpenGLGraphics.h"
#include "UrbanEngine/Platform/Win32/Win32Window.h"

#include <glad/glad.h>
#include <glad/glad_wgl.h>

#pragma comment (lib, "opengl32.lib")

namespace UrbanEngine
{
	UrbanEngine::OpenGLGraphics::OpenGLGraphics(Window* window)
		:
		Graphics(window),
		m_TargetWnd(reinterpret_cast<Win32Window*>(window)->GetHWND())
	{
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		m_Device = GetDC(reinterpret_cast<Win32Window*>(window)->GetHWND());

		int letWindowChoosePixelFormat = ChoosePixelFormat(m_Device, &pfd);
		SetPixelFormat(m_Device, letWindowChoosePixelFormat, &pfd);

		m_Context = wglCreateContext(m_Device);
		wglMakeCurrent(m_Device, m_Context);

		// Load Modern OpenGL
		if (!gladLoadGL())
		{
			throw InitializationError(__LINE__, __FILE__, "Failed to load Modern OpenGL functions!");
		}

		// Load GLAD WGL
		if (!gladLoadWGL(m_Device))
		{
			throw InitializationError(__LINE__, __FILE__, "Failed to load WGL extensions!");
		}

		// Initial viewport
		glViewport(0, 0, window->Width(), window->Height());

		// Enable V-Sync
		// TODO: Make it mutable
		wglSwapIntervalEXT(1);
		
		std::cout << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << std::endl;

		m_API = API::GL460;
	}

	OpenGLGraphics::~OpenGLGraphics()
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(m_Context);
		ReleaseDC(m_TargetWnd, m_Device);
	}

	void OpenGLGraphics::EndFrame()
	{
		// Cahnge framebuffers only if the window is alive
		if (m_TargetWindow->IsOpen())
		{
			if (SwapBuffers(m_Device) == FALSE)
			{
				throw FramebufferSwapError(__LINE__, __FILE__);
			}
		}
	}

	void OpenGLGraphics::ClearBuffer(float red, float green, float blue, float alpha) noexcept
	{
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLGraphics::DrawIndexed(unsigned int count) noexcept(!URBAN_IS_DEBUG)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, (const void*)0);
	}
	
	OpenGLGraphics::InitializationError::InitializationError(int line, const char* file, const std::string& errorDetails)
		:
		UrbanException(line, file),
		m_Details(errorDetails)
	{
	}
	const char* OpenGLGraphics::InitializationError::what() const noexcept
	{
		std::ostringstream oss;

		oss << GetType() << std::endl
			<< "[Error Details] " << GetErrorDetails() << std::endl
			<< GetOriginString();

		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* OpenGLGraphics::InitializationError::GetType() const noexcept
	{
		return "Urban Engine OpenGL Graphics Initialization Error";
	}
	std::string OpenGLGraphics::InitializationError::GetErrorDetails() const noexcept
	{
		return m_Details;
	}
	
	OpenGLGraphics::FramebufferSwapError::FramebufferSwapError(int line, const char* file)
		:
		UrbanException(line, file)
	{
	}
	const char* OpenGLGraphics::FramebufferSwapError::what() const noexcept
	{
		std::ostringstream oss;

		oss << GetType() << std::endl
			<< "Failed to swap front and back framebuffers!" << std::endl
			<< GetOriginString();

		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
	const char* OpenGLGraphics::FramebufferSwapError::GetType() const noexcept
	{
		return "Urban Engine OpenGL Graphics Framebuffer Swap Error";
	}
}
