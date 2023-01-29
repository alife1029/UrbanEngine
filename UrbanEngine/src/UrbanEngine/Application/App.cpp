#include "urbanpch.h"
#include "App.h"
#include "UrbanEngine/Graphics/Renderer2D.h"

#ifdef URBAN_PLATFORM_WINDOWS
#include "UrbanEngine/Platform/Win32/Win32Window.h"
#include "UrbanEngine/Graphics/Graphics.h"
#endif

namespace UrbanEngine
{
	App::App() 
	{
#ifdef URBAN_PLATFORM_WINDOWS
		WindowConfig wndCfg;
		m_Window = new Win32Window(wndCfg);
		m_Window->CreateGraphicContext(UrbanEngine::Graphics::API::GL460);
		
		// Initialize batch renderer
		Renderer2D::Initialize(m_Window->Gfx());
#endif
	}
	
	App::~App() 
	{
		// Terminate batch renderer
		Renderer2D::Shutdown();

		delete m_Window;
	}
	
	void App::Start() 
	{
		m_Window->Show();
	}
	
	void App::Update() 
	{
		
	}
	
	Window* App::GetWindow() const noexcept
	{
		return m_Window;
	}
}
