#include "TestApp.h"

#include <iostream>

#include <UrbanEngine/Graphics/Renderer2D.h>

using namespace UrbanEngine;

TestApp::TestApp() : App()
{
	m_Cam = new Camera();
	m_Grass = Texture2D::LoadTexture(m_Window->Gfx(), "data/textures/grass.png", 256);
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
	
	// Update game logic
	{
		if (Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left))
			m_CamPos.x -= m_CamMovementSpeed * Time::Delta();
		if (Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right))
			m_CamPos.x += m_CamMovementSpeed * Time::Delta();
		if (Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up))
			m_CamPos.y += m_CamMovementSpeed * Time::Delta();
		if (Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down))
			m_CamPos.y -= m_CamMovementSpeed * Time::Delta();

		if (Input::IsKeyPressed(Key::E))
			m_CamRotation -= m_CamRotationSpeed * Time::Delta();
		if (Input::IsKeyPressed(Key::Q))
			m_CamRotation += m_CamRotationSpeed * Time::Delta();

		m_Cam->SetPosition({ m_CamPos, 0.0f });
		m_Cam->SetRotation(m_CamRotation);
	}
	
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

	Renderer2D::DrawQuad(m_Grass, { 0.0f, 0.0f }, m_Rotation += Time::Delta() * 15.0f);

	Renderer2D::EndFrame();
	
	m_Window->Gfx()->EndFrame();
}
