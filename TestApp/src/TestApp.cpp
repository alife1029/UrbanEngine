#include "TestApp.h"

#include <iostream>

using namespace UrbanEngine;

TestApp::TestApp() : App()
{
	std::cout << "TestApp::TestApp()" << std::endl;
}

TestApp::~TestApp()
{
	std::cout << "TestApp::~TestApp()" << std::endl;
}

void TestApp::Start()
{
	App::Start();
	std::cout << "TestApp::Start()" << std::endl;
}

void TestApp::Update()
{
	App::Update();
	std::cout << "TestApp::Update()" << std::endl;
	//AppManager::QuitApplication();
	m_Window->ProcessEvents();
	m_Window->Gfx()->ClearBuffer(1.0f, 0.0f, 0.0f, 1.0f);
	m_Window->Gfx()->EndFrame();
}
