#pragma once

#include <glm/mat4x4.hpp>

namespace UrbanEngine
{
	class Window;
	class Graphics
	{
	public:
		enum class API
		{
			NONE,
			D3D11,	// TODO: Implement D3D11 Graphics (for Windows)
			GL460,
			GLES30	// TODO: Implement OpenGL ES 3.0 graphics (for mobile platforms)
		};

	public:
		Graphics(Window* window);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		virtual ~Graphics();

		virtual void EndFrame();
		virtual void ClearBuffer(float red, float green, float blue, float alpha) noexcept;
		virtual void DrawIndexed(unsigned int count) noexcept(!URBAN_IS_DEBUG);

		API GetRendererAPI() const noexcept;
	
	protected:
		API m_API;
		Window* m_TargetWindow;
	};
}
