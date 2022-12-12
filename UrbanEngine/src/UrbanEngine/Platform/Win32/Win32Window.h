#pragma once

#include "UrbanEngine/Application/Window.h"
#include "UrbanEngine/UrbanException.h"

namespace UrbanEngine
{
	class Win32Window : public Window
	{
		friend class Win32WindowClass;
	
	public:
		class Exception : public UrbanExceptionUnicode
		{
			using UrbanExceptionUnicode::UrbanExceptionUnicode;
		public:
			static std::wstring TranslateErrorCode(HRESULT hr) noexcept;
		};
		
		class HrException : public Exception
		{
		public:
			HrException(int line, const wchar_t* file, HRESULT hr) noexcept;
			virtual const wchar_t* what_unicode() const noexcept override;
			virtual const wchar_t* GetType() const noexcept override;
			HRESULT GetErrorCode() const noexcept;
			std::wstring GetErrorDescription() const noexcept;
		private:
			HRESULT m_hr;
		};
	
	public:
		Win32Window(const WindowConfig& winCfg);
		virtual ~Win32Window();

		virtual void SetWidth(int width) override;
		virtual void SetHeight(int height) override;
		virtual void SetTitle(const std::wstring& title) override;
		virtual void SetFullScreenState(bool fullScreen) override;
		virtual void Show() override;
		virtual void Hide() override;

		virtual void ProcessEvents() override;

	private:
		HWND hWnd;

	private:
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT CALLBACK HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	};
}
