#include "urbanpch.h"
#include "D3D11Renderer2D.h"
#include "D3D11Shader.h"
#include "D3D11GraphicsThrowMacros.h"

#include <cstdint>
#include <wrl.h>
#include <d3d11.h>

// IMPORTANT: Implement Dynamic Direct3D Batch Renderer

#define QUAD_PER_BATCH 1000

namespace wrl = Microsoft::WRL;

namespace UrbanEngine
{
	struct Vertex
	{
		glm::vec2 Position;
		glm::vec4 Color;
	};

	struct RendererData
	{
		D3D11Graphics* Gfx;

		wrl::ComPtr<ID3D11Buffer> VertexBuffer;
		wrl::ComPtr<ID3D11Buffer> IndexBuffer;

		Vertex* VBuffer = nullptr;
		Vertex* VBufferPtr = nullptr;

		uint32_t IndexCount = 0;

		D3D11Shader* ShaderProgram = nullptr;
	};

	static RendererData s_Data;

	void D3D11Renderer2D::Initialize(Graphics* gfx)
	{
		s_Data.Gfx = reinterpret_cast<D3D11Graphics*>(gfx);

		s_Data.ShaderProgram = new D3D11Shader(reinterpret_cast<D3D11Graphics*>(gfx), "shaders/Solid2DVS.cso", "shaders/Solid2DPS.cso");
		s_Data.VBuffer = new Vertex[QUAD_PER_BATCH];

		// Calculate indices
		const size_t indexCount = QUAD_PER_BATCH * 6;
		const size_t indicesArrSizeOf = sizeof(uint16_t) * indexCount;
		uint16_t* indices = (uint16_t*)malloc(indicesArrSizeOf);
		uint16_t offset = 0;
		for (size_t i = 0; i < indexCount; i += 6)
		{
			indices[i    ] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;
			offset += 4;
		}

		// Create D3D11 buffers
		INFO_MANAGER(s_Data.Gfx);

		D3D11_BUFFER_DESC bd	= {};
		bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
		bd.Usage				= D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags			= 0;
		bd.StructureByteStride	= 0;

	}
	void D3D11Renderer2D::Shutdown()
	{
	}
	void D3D11Renderer2D::BeginFrame(const glm::mat4& viewProject)
	{
	}
	void D3D11Renderer2D::EndFrame()
	{
	}
	void D3D11Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
	}
}
