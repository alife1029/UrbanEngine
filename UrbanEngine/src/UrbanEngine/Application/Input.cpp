#include "Input.h"

namespace UrbanEngine
{
	Window* s_EventWindow = nullptr;

	bool Input::IsKeyPressed(Key key) noexcept
	{
		return s_EventWindow->m_Kbd.IsKeyPressed(static_cast<unsigned char>(key));
	}
	
	bool Input::IsKeyPressed(unsigned char keycode) noexcept
	{
		return s_EventWindow->m_Kbd.IsKeyPressed(keycode);
	}
	
	void Input::SetupEventWindow(Window* eventWnd) noexcept
	{
		s_EventWindow = eventWnd;
	}
}
