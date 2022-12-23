#pragma once

#include "UrbanEngine/Graphics/Graphics.h"
#include "UrbanEngine/UrbanException.h"
#include "DXGIInfoManager.h"
#include <vector>
#include <string>
#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>

namespace UrbanEngine
{
	class D3D11Graphics : public Graphics
	{
	public:
		class Exception : public UrbanExceptionUnicode
		{
			using UrbanExceptionUnicode::UrbanExceptionUnicode;
		};

		class HrException : public Exception
		{
		public:
			HrException(int line, const wchar_t* file, HRESULT hr, std::vector<std::wstring> infoMessages = {}) noexcept;
			const wchar_t* what_unicode() const noexcept override;
			const wchar_t* GetType() const noexcept override;
			HRESULT GetErrorCode() const noexcept;
			std::wstring GetErrorString() const noexcept;
			std::wstring GetErrorDescription() const noexcept;
			std::wstring GetErrorInfo() const noexcept;
		private:
			HRESULT m_hr;
			std::wstring m_Info;
		};

		class InfoException : public Exception
		{
		public:
			InfoException(int line, const wchar_t* file, std::vector<std::wstring> info);
			const wchar_t* what_unicode() const noexcept override;
			const wchar_t* GetType() const noexcept override;
			std::wstring GetErrorInfo() const noexcept;
		private:
			std::wstring m_Info;
		};

		class DeviceRemovedException : public HrException
		{
			using HrException::HrException;
		public:
			const wchar_t* GetType() const noexcept override;
		private:
			std::wstring m_Reason;
		};

	public:
		D3D11Graphics(Window* window);
		D3D11Graphics(const D3D11Graphics&) = delete;
		D3D11Graphics& operator=(const D3D11Graphics&) = delete;
		~D3D11Graphics() = default;

		void EndFrame() override;
		void ClearBuffer(float red, float green, float blue, float alpha) noexcept override;
		void DrawIndexed(unsigned int count) noexcept(!URBAN_IS_DEBUG) override;

		ID3D11DeviceContext* GetContext() noexcept;
		ID3D11Device* GetDevice() noexcept;
		DXGIInfoManager& GetDXGIInfoManager() noexcept(URBAN_IS_DEBUG);

#if URBAN_IS_DEBUG
	private:
		DXGIInfoManager infoManager;
#endif
	
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swapchain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_Target;
	};
}
