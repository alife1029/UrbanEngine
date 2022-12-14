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
			D3D11,
			GL450,	// TODO: Implement OpenGL 4.5 graphics (for Windows, Linux and Mac)
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
		void SetProjection(const glm::mat4& projectionMatrix) noexcept;
		glm::mat4 Projection() const noexcept;

		API GetRendererAPI() const noexcept;
	
	protected:
		glm::mat4 m_Projection;
		Window* m_Window;
		API m_API;
	};
}
