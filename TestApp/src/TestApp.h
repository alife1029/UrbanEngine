#pragma once

#include "UrbanEngine.h"

class TestApp : public UrbanEngine::App
{
public:
	TestApp();
	virtual ~TestApp();
	TestApp(const TestApp&) = delete;
	TestApp& operator=(const TestApp&) = delete;
	void Start();
	void Update();

private:
	UrbanEngine::Camera* m_Cam;
	glm::vec2 m_CamPos = glm::vec2{ 0.0f };
	float m_CamRotation = 0.0f;
	float m_CamMovementSpeed = 2.7f;
	float m_CamRotationSpeed = 45.0f;
	UrbanEngine::Texture2D* m_Grass;
	float m_Rotation = 0.0f;
};
