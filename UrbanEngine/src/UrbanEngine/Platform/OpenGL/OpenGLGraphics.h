#pragma once

#include "UrbanEngine/Graphics/Graphics.h"
#include "UrbanEngine/UrbanException.h"

namespace UrbanEngine
{
	class OpenGLGraphics : public Graphics
	{
	public:
		class InitializationError : public UrbanException
		{
		public:
			InitializationError(int line, const char* file, const std::string& errorDetails);
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			std::string GetErrorDetails() const noexcept;
		private:
			std::string m_Details;
		};

		class FramebufferSwapError : public UrbanException
		{
		public:
			FramebufferSwapError(int line, const char* file);
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
		};

	public:
		OpenGLGraphics(Window* window);
		OpenGLGraphics(const OpenGLGraphics&) = delete;
		OpenGLGraphics& operator=(const OpenGLGraphics&) = delete;
		~OpenGLGraphics();

		void EndFrame() override;
		void ClearBuffer(float red, float green, float blue, float alpha) noexcept override;
		void DrawIndexed(unsigned int count) noexcept (!URBAN_IS_DEBUG) override;

	private:
		HGLRC	m_Context;
		HDC		m_Device;
		HWND	m_TargetWnd;
	};
}
