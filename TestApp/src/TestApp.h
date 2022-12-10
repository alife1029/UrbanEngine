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
};
