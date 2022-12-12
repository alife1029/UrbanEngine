#pragma once

#include "Window.h"

namespace UrbanEngine
{
	class App
	{
	public:
		App();
		
		virtual ~App();
		App(const App&) = delete;
		App& operator=(const App&) = delete;

		virtual void Start();
		virtual void Update();

	protected:
		Window* m_Window;
	};

	// To be defined in client
	App* CreateApplication();
}
