#pragma once

#include "App.h"
#include "App.h"

namespace UrbanEngine
{
	class AppManager
	{
	public:
		static void RunApplication(App* app);
		static App* GetRunningApplication();
		static void QuitApplication();
	private:
		static App* s_RunningApplication;
		static bool s_IsRunning;
	};
}
