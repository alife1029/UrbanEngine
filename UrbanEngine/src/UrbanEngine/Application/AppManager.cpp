#include "urbanpch.h"
#include "AppManager.h"

namespace UrbanEngine
{
	App* AppManager::s_RunningApplication = nullptr;
	bool AppManager::s_IsRunning = false;

	void AppManager::RunApplication(App* app)
	{
		s_RunningApplication = app;
		s_IsRunning = true;

		// App running lifecycle,
		// Call start method before first frame
		app->Start();
		while (s_IsRunning)
		{
			// Call update method per frame
			app->Update();
		}
	}

	App* AppManager::GetRunningApplication()
	{
		return s_RunningApplication;
	}

	void AppManager::QuitApplication()
	{
		s_RunningApplication = nullptr;
		s_IsRunning = false;
	}
}
