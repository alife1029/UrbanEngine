#pragma once

#include "App.h"
#include "AppManager.h"

extern UrbanEngine::App* UrbanEngine::CreateApplication();

#ifdef URBAN_PLATFORM_WINDOWS

#include <Windows.h>

#ifdef URBAN_DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
int main(int argc, char** argv)
#elif defined(URBAN_RELEASE)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
int WinMain(	HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPWSTR lpCmdLine,
				int nShowCmd	)
#endif // URBAN_DEBUG
{
	UrbanEngine::App* app = UrbanEngine::CreateApplication();
	UrbanEngine::AppManager::RunApplication(app);
	UrbanEngine::AppManager::QuitApplication();
	delete app;

	return 0;
}

#endif // URBAN_PLATFORM_WINDOWS
