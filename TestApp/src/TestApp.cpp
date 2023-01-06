#include "TestApp.h"

#include <iostream>

using namespace UrbanEngine;

TestApp::TestApp() : App()
{
}

TestApp::~TestApp()
{
}

void TestApp::Start()
{
	App::Start();
}

void TestApp::Update()
{
	App::Update();
	m_Window->ProcessEvents();
	m_Window->Gfx()->ClearBuffer(1.0f, 0.0f, 0.0f, 1.0f);
	m_Window->Gfx()->EndFrame();
}
