#pragma once

#include "D3D11Graphics.h"

#include <glm/glm.hpp>

namespace UrbanEngine
{
	class D3D11Renderer2D
	{
	private:
		static void Initialize(Graphics* gfx);
		static void Shutdown();

	public:
		static void BeginFrame(const glm::mat4& viewProject = glm::mat4(1.0f));
		static void EndFrame();

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
	};
}
