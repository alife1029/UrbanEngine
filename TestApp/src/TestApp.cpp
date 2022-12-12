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
}
