#pragma once

#include "OpenGLTexture2D.h"
#include "UrbanEngine/Graphics/Graphics.h"

#include <glm/glm.hpp>

namespace UrbanEngine
{
	class OpenGLRenderer2D
	{
		friend class Renderer2D;
	private:
		static void Initialize(Graphics* gfx);
		static void Shutdown();

	public:
		static void BeginFrame(const glm::mat4& viewProject = glm::mat4(1.0f));
		static void EndFrame();

		static void DrawQuad(OpenGLTexture2D* texture, const glm::mat4& transform, const glm::vec4& color);
	};
}
