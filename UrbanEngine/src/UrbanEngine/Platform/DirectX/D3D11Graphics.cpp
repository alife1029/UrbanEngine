#include "urbanpch.h"
#include "D3D11Graphics.h"
#include "UrbanEngine/Platform/Win32/Win32Window.h"
#include "D3D11GraphicsThrowMacros.h"

#pragma comment(lib, "d3d11.lib")

namespace UrbanEngine
{
	D3D11Graphics::D3D11Graphics(Window* window)
		:
		Graphics(window)
	{
		// Crate swapchain, device and context
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = reinterpret_cast<Win32Window*>(window)->GetHWND();
		sd.Windowed = TRUE; // TODO: Implement fullscreen!
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = NULL;

		UINT swapCreateFlags = 0u;
#if URBAN_IS_DEBUG
		swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// For checking results of D3D functions
		HRESULT hr;

		GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			swapCreateFlags,
			nullptr,
			NULL,
			D3D11_SDK_VERSION,
			&sd,
			&m_Swapchain,
			&m_Device,
			nullptr,
			&m_Context
		));

		// Create initial viewport
		// TODO: Use viewport class here in future
		D3D11_VIEWPORT vp;
		vp.Width = static_cast<float>(window->Width());
		vp.Height = static_cast<float>(window->Height());
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0.0f;
		vp.TopLeftY = 0.0f;
		m_Context->RSSetViewports(1u, &vp);

		// Create render target view
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
		GFX_THROW_INFO(m_Swapchain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
		GFX_THROW_INFO(m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_Target));

		// Set renderer API as Direct3D 11
		m_API = API::D3D11;
	}
	
	void D3D11Graphics::EndFrame()
	{
		// TODO: Implement turning on and off the VSync

		HRESULT hr;
#if URBAN_IS_DEBUG
		infoManager.Set();
#endif

		if (FAILED(hr = m_Swapchain->Present(1u, 0u)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				throw GFX_DEVICE_REMOVED_EXCEPT(m_Device->GetDeviceRemovedReason());
			}
			else
			{
				throw GFX_EXCEPT(hr);
			}
		}
	}
	
	void D3D11Graphics::ClearBuffer(float red, float green, float blue, float alpha) noexcept
	{
		const float color[] = { red, green, blue, alpha };
		m_Context->ClearRenderTargetView(m_Target.Get(), color);
	}
	
	void D3D11Graphics::DrawIndexed(unsigned int count) noexcept(!URBAN_IS_DEBUG)
	{
		GFX_THROW_INFO_ONLY(m_Context->DrawIndexed(count, 0u, 0u));
	}

	ID3D11DeviceContext* D3D11Graphics::GetContext() noexcept
	{
		return m_Context.Get();
	}

	ID3D11Device* D3D11Graphics::GetDevice() noexcept
	{
		return m_Device.Get();
	}

	DXGIInfoManager& D3D11Graphics::GetDXGIInfoManager() noexcept(URBAN_IS_DEBUG)
	{
#if URBAN_IS_DEBUG
		return infoManager;
#else
		throw std::logic_error("You can access DXGI Info Manager only in Debug configuration!");
#endif
	}


#pragma region Exceptions
	
	D3D11Graphics::HrException::HrException(int line, const wchar_t* file, HRESULT hr, std::vector<std::wstring> infoMessages) noexcept
		:
		Exception(line, file),
		m_hr(hr)
	{
		// Join all info messages with newlines into single string
		for (const auto& m : infoMessages)
		{
			m_Info += m;
			m_Info.push_back('\n');
		}

		// Remove final newline if exists
		if (!m_Info.empty())
		{
			m_Info.pop_back();
		}
	}

	const wchar_t* D3D11Graphics::HrException::what_unicode() const noexcept
	{
		std::wostringstream wos;
		
		wos << GetType() << std::endl
			<< L"[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << L" (" << static_cast<unsigned long>(GetErrorCode()) << L")" << std::endl
			<< "[Error String] " << GetErrorString() << std::endl
			<< "[Description] " << GetErrorDescription() << std::endl;

		if (!m_Info.empty())
		{
			wos << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
		}

		wos << GetOriginString();

		m_WhatBuffer = wos.str();
		return m_WhatBuffer.c_str();
	}

	const wchar_t* D3D11Graphics::HrException::GetType() const noexcept
	{
		return L"Urban Engine Direct3D Graphics Exception!";
	}

	HRESULT D3D11Graphics::HrException::GetErrorCode() const noexcept
	{
		return m_hr;
	}
	
	std::wstring D3D11Graphics::HrException::GetErrorString() const noexcept
	{
		return std::wstring();
	}

	std::wstring D3D11Graphics::HrException::GetErrorDescription() const noexcept
	{
		wchar_t* pMsgBuf = nullptr;

		DWORD msgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, GetErrorCode(), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr
		);

		if (msgLen == 0) return L"Unidentified Error Code";

		std::wstring errorString = pMsgBuf;
		LocalFree(pMsgBuf);
		return errorString;
	}
	
	std::wstring D3D11Graphics::HrException::GetErrorInfo() const noexcept
	{
		return m_Info;
	}
	
	
	
	
	D3D11Graphics::InfoException::InfoException(int line, const wchar_t* file, std::vector<std::wstring> info)
		:
		Exception(line, file)
	{
		for (const auto& m : info)
		{
			m_Info += m;
			m_Info.push_back('\n');
		}

		if (!info.empty())
		{
			m_Info.pop_back();
		}
	}
	
	const wchar_t* D3D11Graphics::InfoException::what_unicode() const noexcept
	{
		std::wostringstream wos;
		
		wos << GetType() << std::endl
			<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl
			<< GetOriginString();
		
		m_WhatBuffer = wos.str();
		return m_WhatBuffer.c_str();
	}
	
	const wchar_t* D3D11Graphics::InfoException::GetType() const noexcept
	{
		return L"Urban Engine Direct3D Info Exception";
	}
	
	std::wstring D3D11Graphics::InfoException::GetErrorInfo() const noexcept
	{
		return m_Info;
	}




	
	const wchar_t* D3D11Graphics::DeviceRemovedException::GetType() const noexcept
	{
		return L"Urban Engine Direct3D Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
	}

#pragma endregion
}
