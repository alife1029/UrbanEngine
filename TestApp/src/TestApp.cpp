#include "TestApp.h"

#include <iostream>

#include <UrbanEngine/Graphics/Renderer2D.h>

using namespace UrbanEngine;

TestApp::TestApp() : App()
{
	m_Cam = new Camera();
	m_Grass = Texture2D::LoadTexture(m_Window->Gfx(), "data/textures/grass.png", 256);
	m_Rotation = 0.0f;
}

TestApp::~TestApp()
{
	delete m_Grass;
}

void TestApp::Start()
{
	App::Start();

	m_Cam->SetSize(1.0f);
}

void TestApp::Update()
{
	App::Update();

	m_Window->ProcessEvents();

	m_Rotation += 1.4f;
	m_Cam->SetRotation(m_Cam->Rotation() + 0.1f);
	m_Cam->SetPosition({ 0.0f, sin(m_Rotation / 35) / 30, 0.0f });
	m_Cam->Update();
	
	m_Window->Gfx()->ClearBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	
	Renderer2D::BeginFrame(m_Cam->ViewProjMatrix());

	const float width = 0.25f;
	const float height = 0.25f;
	unsigned int counter = 0;
	for (float x = -1.0f; x <= 1.0f; x += width)
	{
		for (float y = -1.0f; y <= 1.0f; y += height)
		{
			glm::vec4 color;

			if (++counter % 2 == 0) color = { 0.2f, 0.2f, 0.2f, 1.0f };
			else color = { 0.1f, 0.1f, 0.1f, 1.0f };

			Renderer2D::DrawQuad({ x, y }, { width, height }, 0.0f, color);
		}
	}

	Renderer2D::DrawQuad(m_Grass, { 0.0f, 0.0f }, m_Rotation);

	Renderer2D::EndFrame();
	
	m_Window->Gfx()->EndFrame();
}
