#include "urbanpch.h"
#include "D3D11Shader.h"
#include "D3D11GraphicsThrowMacros.h"

#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

std::wstring ToUTF8(const std::string ascii)
{
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, ascii.c_str(), -1, nullptr, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, ascii.c_str(), -1, wstr, wchars_num);
	std::wstring ret(wstr);
	delete[] wstr;
	return ret;
}

namespace UrbanEngine
{
	D3D11Shader::D3D11Shader(D3D11Graphics* gfx, const std::string& vsFile, const std::string& psFile)
		:
		Shader(gfx, vsFile, psFile),
		m_Gfx(gfx)
	{
		INFO_MANAGER(gfx);

		// Convert ASCII string to UTF-8 string
		std::wstring vsFileW = ToUTF8(vsFile);
		std::wstring psFileW = ToUTF8(psFile);

		// Load vertex shader
		GFX_THROW_INFO(D3DReadFileToBlob(vsFileW.c_str(), &m_BytecodeBlob));
		GFX_THROW_INFO(gfx->GetDevice()->CreateVertexShader(
			m_BytecodeBlob->GetBufferPointer(),
			m_BytecodeBlob->GetBufferSize(),
			nullptr,
			&m_VertexShader
		));

		// Load pixel shader
		ID3DBlob* psBlob;
		GFX_THROW_INFO(D3DReadFileToBlob(psFileW.c_str(), &psBlob));
		GFX_THROW_INFO(gfx->GetDevice()->CreatePixelShader(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&m_PixelShader
		));
		psBlob->Release();
	}
	
	void D3D11Shader::Bind()
	{
		m_Gfx->GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0u);
		m_Gfx->GetContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
	}
}
