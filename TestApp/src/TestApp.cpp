#include "TestApp.h"

#include <iostream>

TestApp::TestApp()
{
	std::cout << "TestApp::TestApp()" << std::endl;
}

TestApp::~TestApp()
{

	std::cout << "TestApp::~TestApp()" << std::endl;
}

void TestApp::Start()
{
	std::cout << "TestApp::Start()" << std::endl;
}

void TestApp::Update()
{
	std::cout << "TestApp::Update()" << std::endl;
	UrbanEngine::AppManager::QuitApplication();
}
