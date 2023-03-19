#pragma once

#include "Key.h"
#include "Window.h"

#include <vector>

namespace UrbanEngine
{
	class Input
	{
		friend class App;
	public:
		static bool IsKeyPressed(Key key) noexcept;
		static bool IsKeyPressed(unsigned char key) noexcept;
	private:
		static void SetupEventWindow(Window* eventWnd) noexcept;
	};
}
