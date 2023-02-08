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
	UrbanEngine::Texture2D* m_Grass;
	float m_Rotation;
};
