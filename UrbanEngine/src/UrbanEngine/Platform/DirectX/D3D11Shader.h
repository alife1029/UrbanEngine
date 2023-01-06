#pragma once

#include "UrbanEngine/Graphics/Shader.h"
#include "D3D11Graphics.h"

#include <d3d11.h>
#include <wrl.h>

namespace UrbanEngine
{
	class D3D11Shader : public Shader
	{
	public:
		D3D11Shader(D3D11Graphics* gfx, const std::string& vsFile, const std::string& psFile);
		~D3D11Shader() = default;
		virtual void Bind() override;

	private:
		D3D11Graphics* m_Gfx;

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_BytecodeBlob;
	};
}
