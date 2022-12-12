#pragma once

#include "App.h"
#include "App.h"

namespace UrbanEngine
{
	class AppManager
	{
	public:
		// Starts the lifecycle of the given application. (You can run only one application in the same time!)
		static void RunApplication(App* app);
		// Returns the pointer of the current running application.
		static App* GetRunningApplication();
		// Ends up the lifecycle of the currently running application with the return value that given in parameter.
		static void QuitApplication(int returnValue = 0);
		// Returns the return value of last ran application. (You can call it only if no application running currently!)
		static int GetReturnValue();
	private:
		static App* s_RunningApplication;
		static bool s_IsRunning;
		static int s_ReturnValue;
	};
}
