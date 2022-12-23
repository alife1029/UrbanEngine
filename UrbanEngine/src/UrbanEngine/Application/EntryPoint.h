#pragma once

#include "App.h"
#include "AppManager.h"
#include "UrbanEngine/UrbanException.h"

extern UrbanEngine::App* UrbanEngine::CreateApplication();

#ifdef URBAN_PLATFORM_WINDOWS

#include <Windows.h>

#if URBAN_IS_DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
int main(int argc, char** argv)
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nShowCmd	)
#endif // URBAN_IS_DEBUG
{
	try
	{
		UrbanEngine::App* app = UrbanEngine::CreateApplication();
		UrbanEngine::AppManager::RunApplication(app);
		delete app;

		return UrbanEngine::AppManager::GetReturnValue();
	}
	catch (const UrbanEngine::UrbanException& ex)
	{
		MessageBoxA(nullptr, ex.what(), "Urban Engine Exception", MB_ICONERROR);
	}
	catch (const UrbanEngine::UrbanExceptionUnicode& ex)
	{
		MessageBoxW(nullptr, ex.what_unicode(), L"Urban Engine Exception", MB_ICONERROR);
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(nullptr, ex.what(), "An Error Occured!", MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxW(nullptr, L"There is no description about the error!", L"Unknown Error", MB_ICONERROR);
	}

	return -1;
}

#endif // URBAN_PLATFORM_WINDOWS
