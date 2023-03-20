#include "urbanpch.h"
#include "AppManager.h"

namespace UrbanEngine
{
	App* AppManager::s_RunningApplication = nullptr;
	bool AppManager::s_IsRunning = false;
	int AppManager::s_ReturnValue = 0;

	void AppManager::RunApplication(App* app)
	{
		assert(!s_IsRunning);

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

		// Quit application with default return value (0)
		QuitApplication();
	}

	App* AppManager::GetRunningApplication()
	{
		return s_RunningApplication;
	}

	void AppManager::QuitApplication(int returnValue)
	{
		if (s_IsRunning)
		{
			s_RunningApplication = nullptr;
			s_IsRunning = false;
			s_ReturnValue = returnValue;
		}
	}
	
	int AppManager::GetReturnValue()
	{
		assert(!s_IsRunning);
		return s_ReturnValue;
	}
}
