#pragma once

#include "UrbanEngine/Graphics/Graphics.h"

namespace UrbanEngine
{
	class OpenGLGraphics : public Graphics
	{
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
