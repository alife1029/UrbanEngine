#include <UrbanEngine/Application/EntryPoint.h>
#include "TestApp.h"

UrbanEngine::App* UrbanEngine::CreateApplication()
{
	return new TestApp();
}
