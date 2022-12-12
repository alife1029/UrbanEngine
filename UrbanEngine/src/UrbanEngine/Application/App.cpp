#include "urbanpch.h"
#include "App.h"

#ifdef URBAN_PLATFORM_WINDOWS
#include "UrbanEngine/Platform/Win32/Win32Window.h"
#endif

namespace UrbanEngine
{
	App::App() 
	{
#ifdef URBAN_PLATFORM_WINDOWS
		WindowConfig wndCfg;
		m_Window = new Win32Window(wndCfg);
#endif
	}
	
	App::~App() 
	{
		delete m_Window;
	}
	
	void App::Start() 
	{
		m_Window->Show();
	}
	
	void App::Update() 
	{
		m_Window->ProcessEvents();
	}
}
