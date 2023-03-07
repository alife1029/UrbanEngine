#include "urbanpch.h"
#include "Win32Window.h"
#include "UrbanEngine/Application/AppManager.h"
#include "UrbanEngine/Graphics/BaseViewport.h"
#include "UrbanEngine/Platform/DirectX/D3D11Graphics.h"
#include "UrbanEngine/Platform/OpenGL/OpenGLGraphics.h"

#define URBAN_WIN32WND_EXCEPT(hr) UrbanEngine::Win32Window::HrException(__LINE__, __FILEW__, hr)
#define URBAN_WIN32WND_LASTEXCEPT() UrbanEngine::Win32Window::HrException(__LINE__, __FILEW__, GetLastError())

#pragma region Win32WindowClass
namespace UrbanEngine
{
	class Win32WindowClass
	{
	public:
		static const wchar_t* GetName() noexcept
		{
			return s_WndClassName;
		}
		static HINSTANCE GetInstance() noexcept
		{
			return s_WndClass.m_hInst;
		}

	private:
		Win32WindowClass() noexcept
			:
			m_hInst(GetModuleHandle(nullptr))
		{
			WNDCLASSEX wc = { 0 };
			wc.cbSize = sizeof(wc);
			wc.style = CS_OWNDC;
			wc.lpfnWndProc = Win32Window::HandleMsgSetup;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = GetInstance();
			wc.hIcon = nullptr;
			wc.hIconSm = nullptr;
			wc.hCursor = nullptr;
			wc.hbrBackground = nullptr;
			wc.lpszMenuName = nullptr;
			wc.lpszClassName = GetName();

			RegisterClassEx(&wc);
		}

		~Win32WindowClass()
		{
			UnregisterClass(GetName(), GetInstance());
		}

		Win32WindowClass(const Win32WindowClass&) = delete;
		Win32WindowClass& operator=(const Win32WindowClass&) = delete;
		static constexpr const wchar_t* s_WndClassName = L"Urban Engine Window Class";
		static Win32WindowClass s_WndClass;
		HINSTANCE m_hInst;
	};

	Win32WindowClass Win32WindowClass::s_WndClass = Win32WindowClass();
}
#pragma endregion

namespace UrbanEngine
{
	Win32Window::Win32Window(const WindowConfig& winCfg)
		:
		Window(winCfg)
	{
		// Window style
		constexpr DWORD windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_SYSMENU;

		// Calculate window size based on desired client region size
		RECT wr;
		wr.left = 100;
		wr.right = winCfg.width + wr.left;
		wr.top = 100;
		wr.bottom = winCfg.height + wr.top;

		if (AdjustWindowRect(&wr, windowStyle, FALSE) == 0)
		{
			throw URBAN_WIN32WND_LASTEXCEPT();
		}

		// Create window and get HWND
		hWnd = CreateWindow(
			Win32WindowClass::GetName(),
			winCfg.title.c_str(),
			windowStyle,
			CW_USEDEFAULT, CW_USEDEFAULT,
			wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr,
			Win32WindowClass::GetInstance(),
			this
		);

		if (hWnd == nullptr)
		{
			throw URBAN_WIN32WND_LASTEXCEPT();
		}
	}
	
	Win32Window::~Win32Window()
	{
		delete m_Graphics;
		DestroyWindow(hWnd);
	}

	void Win32Window::SetWidth(int width)
	{
	}

	void Win32Window::SetHeight(int height)
	{
	}
	
	void Win32Window::SetTitle(const std::wstring& title)
	{
		if (SetWindowText(hWnd, title.c_str()) == 0)
		{
			throw URBAN_WIN32WND_LASTEXCEPT();
		}
	}

	void Win32Window::SetFullScreenState(bool fullScreen)
	{
		// IMPORTANT: Implement Fullscreen
	}
	
	void Win32Window::Show()
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);

		m_IsOpen = true;
	}
	
	void Win32Window::Hide()
	{
		if (ShowWindow(hWnd, SW_HIDE) == 0)
		{
			throw URBAN_WIN32WND_LASTEXCEPT();
		}

		m_IsOpen = false;
	}

	HWND Win32Window::GetHWND() const noexcept
	{
		return hWnd;
	}

	void Win32Window::ProcessEvents()
	{
		MSG msg;

		while (PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				AppManager::QuitApplication(static_cast<int>(msg.wParam));
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Win32Window::CreateGraphicContext(Graphics::API api)
	{
		switch (api)
		{
		case UrbanEngine::Graphics::API::NONE:
			break;
		case UrbanEngine::Graphics::API::D3D11:
			m_Graphics = new D3D11Graphics(this);
			break;
		case UrbanEngine::Graphics::API::GL460:
			m_Graphics = new OpenGLGraphics(this);
			break;
		case UrbanEngine::Graphics::API::GLES30:
			// TODO: Implement OpenGL ES 3.0 graphics
			break;
		default:
			break;
		}
	}

	LRESULT Win32Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		if (msg == WM_NCCREATE)
		{
			const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			Win32Window* const pWnd = static_cast<Win32Window*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32Window::HandleMsgThunk));
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT Win32Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		Win32Window* const pWnd = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT Win32Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (msg)
		{
		case WM_CLOSE:
			m_IsOpen = false;
			AppManager::QuitApplication(0);
			break;

		case WM_SIZE:	// Window resized
			RECT wndRect;
			GetWindowRect(hWnd, &wndRect);
			this->m_Properties.width = wndRect.right - wndRect.left;
			this->m_Properties.height = wndRect.bottom - wndRect.top;
			BaseViewport::UpdateAsFillViewport(this);
			break;

		default:
			break;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}




	// Win32 window exceptions
	std::wstring Win32Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
	{
		wchar_t* pMsgBuf = nullptr;
		DWORD msgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, hr, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr
		);

		if (msgLen == 0) return L"Unidentified Error Code";

		std::wstring errorString = pMsgBuf;
		LocalFree(pMsgBuf);
		return errorString;
	}

	Win32Window::HrException::HrException(int line, const wchar_t* file, HRESULT hr) noexcept
		:
		Exception(line, file),
		m_hr(hr)
	{ }

	const wchar_t* Win32Window::HrException::what_unicode() const noexcept
	{
		std::wostringstream wos;
		wos << GetType() << std::endl
			<< L"[Error Code]: " << GetErrorCode() << std::endl
			<< L"[Description] " << GetErrorDescription() << std::endl
			<< GetOriginString();
		m_WhatBuffer = wos.str();
		return m_WhatBuffer.c_str();
	}

	const wchar_t* Win32Window::HrException::GetType() const noexcept
	{
		return L"Urban Engine Win32 Window Exception";
	}

	HRESULT Win32Window::HrException::GetErrorCode() const noexcept
	{
		return m_hr;
	}

	std::wstring Win32Window::HrException::GetErrorDescription() const noexcept
	{
		return TranslateErrorCode(m_hr);
	}
}
