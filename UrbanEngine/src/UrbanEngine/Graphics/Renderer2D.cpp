#include "urbanpch.h"
#include "Renderer2D.h"

#ifdef URBAN_PLATFORM_WINDOWS
#include "UrbanEngine/Platform/DirectX/D3D11Renderer2D.h"
#include "UrbanEngine/Platform/DirectX/D3D11Texture2D.h"
#endif

#include "UrbanEngine/Platform/OpenGL/OpenGLRenderer2D.h"
#include "UrbanEngine/Platform/OpenGL/OpenGLTexture2D.h"

#include <glm/gtc/matrix_transform.hpp>

#define DEFAULT_SCALE glm::vec2 { 1.0f, 1.0f }
#define DEFAULT_ROTATION 0.0f
#define DEFAULT_COLOR { 1.0f, 1.0f, 1.0f, 1.0f }
#define DEFAULT_TEXTURE s_WhiteTexture

static UrbanEngine::Texture2D* s_WhiteTexture;

namespace UrbanEngine
{
	Graphics* Renderer2D::s_Gfx = nullptr;

	void Renderer2D::Initialize(Graphics* gfx)
	{
		s_Gfx = gfx;

		switch (s_Gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			// TODO: Create D3D11 white texture
			//s_WhiteTexture = new D3D11Texture2D();
			D3D11Renderer2D::Initialize(s_Gfx);
			break;
		case Graphics::API::GL460:
			s_WhiteTexture = new OpenGLTexture2D();
			OpenGLRenderer2D::Initialize(s_Gfx);
			break;
		case Graphics::API::GLES30:
			// TODO: Create OpenGL ES 3.0 White Texture
			// TODO: OpenGL ES 3.0 Initialize
			break;
		}
	}

	void Renderer2D::Shutdown()
	{
		delete s_WhiteTexture;

		switch (s_Gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			D3D11Renderer2D::Shutdown();
			break;
		case Graphics::API::GL460:
			OpenGLRenderer2D::Shutdown();
			break;
		case Graphics::API::GLES30:
			// TODO: OpenGL ES 3.0 Shutdown
			break;
		}
	}

	void Renderer2D::BeginFrame(const glm::mat4& viewProject)
	{
		switch (s_Gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			D3D11Renderer2D::BeginFrame(viewProject);
			break;
		case Graphics::API::GL460:
			OpenGLRenderer2D::BeginFrame(viewProject);
			break;
		case Graphics::API::GLES30:
			// TODO: OpenGL ES 3.0 begin frame
			break;
		}
	}

	void Renderer2D::EndFrame()
	{
		switch (s_Gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			D3D11Renderer2D::EndFrame();
			break;
		case Graphics::API::GL460:
			OpenGLRenderer2D::EndFrame();
			break;
		case Graphics::API::GLES30:
			// TODO: OpenGL ES 3.0 end frame
			break;
		}
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		DrawQuad(DEFAULT_TEXTURE, transform, color);
	}
	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& scale, float zRotation, const glm::vec4& color)
	{
		DrawQuad(DEFAULT_TEXTURE, pos, scale, zRotation, color);
	}
	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(DEFAULT_TEXTURE, pos, scale, DEFAULT_ROTATION, color);
	}
	void Renderer2D::DrawQuad(const glm::vec2& pos, float rotation, const glm::vec4& color)
	{
		DrawQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, rotation, color);
	}
	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec4& color)
	{
		DrawQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, DEFAULT_ROTATION, color);
	}

	void Renderer2D::DrawQuad(Texture2D* texture, const glm::mat4& transform, const glm::vec4& color)
	{
		switch (s_Gfx->GetRendererAPI())
		{
		case Graphics::API::D3D11:
			// TODO: Implement the following func
			// D3D11Renderer2D::DrawQuad(reinterpret_cast<D3D11Texture2D*>(texture), transform, color);
			break;
		case Graphics::API::GL460:
			OpenGLRenderer2D::DrawQuad(reinterpret_cast<OpenGLTexture2D*>(texture), transform, color);
			break;
		case Graphics::API::GLES30:
			// TODO: OpenGL ES 3.0 DrawQuad
			break;
		}
	}
	void Renderer2D::DrawQuad(Texture2D* texture, const glm::vec2& pos, const glm::vec2& scale, float zRotation, const glm::vec4& color)
	{
		DrawQuad(
			texture,
			glm::scale(
				glm::rotate(
					glm::translate(
						glm::mat4(1.0f),
						{ pos.x, pos.y, 0.0f }),
					glm::radians(zRotation),
					{ 0.0f, 0.0f, 1.0f }),
				{ scale.x, scale.y, 0.0f }),
			color);
	}
	void Renderer2D::DrawQuad(Texture2D* texture, const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(texture, pos, scale, DEFAULT_ROTATION, color);
	}
	void Renderer2D::DrawQuad(Texture2D* texture, const glm::vec2& pos, float rotation, const glm::vec4& color)
	{
		DrawQuad(texture, pos, DEFAULT_SCALE, rotation, color);
	}
	void Renderer2D::DrawQuad(Texture2D* texture, const glm::vec2& pos, const glm::vec4& color)
	{
		DrawQuad(texture, pos, DEFAULT_SCALE, DEFAULT_ROTATION, color);
	}
}
