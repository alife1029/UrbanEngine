#include "urbanpch.h"
#include "Window.h"

namespace UrbanEngine
{
	Window::Window(const WindowConfig& winCfg)
		:
		m_Properties(winCfg),
		m_IsOpen(false),
		m_Graphics(nullptr)
	{ }

	Window::~Window() { }
	
	int Window::Width() const noexcept 
	{ 
		return m_Properties.width; 
	}
	int Window::Height() const noexcept 
	{ 
		return m_Properties.height; 
	}
	std::wstring Window::Title() const noexcept 
	{ 
		return m_Properties.title; 
	}
	bool Window::IsFullScreen() const noexcept 
	{ 
		return m_Properties.fullScreen; 
	}
	bool Window::IsOpen() const noexcept
	{
		return m_IsOpen;
	}
	
	void Window::SetWidth(int width) { }
	void Window::SetHeight(int height) { }
	void Window::SetTitle(const std::wstring& title) { }
	void Window::SetFullScreenState(bool fullScreen) { }
	void Window::Show()
	{
		m_IsOpen = true;
	}
	void Window::Hide()
	{
		m_IsOpen = false;
	}
	
	void Window::ProcessEvents() { }
	
	void Window::CreateGraphicContext(Graphics::API api) { }

	Graphics* Window::Gfx() const noexcept
	{
		return m_Graphics;
	}
}
