#include "urbanpch.h"
#include "Input.h"

namespace UrbanEngine
{
	Window* s_EventWindow = nullptr;

	bool Input::IsKeyPressed(Key key) noexcept
	{
		return s_EventWindow->m_Kbd->IsKeyPressed(static_cast<unsigned char>(key));
	}
	
	bool Input::IsKeyPressed(unsigned char keycode) noexcept
	{
		return s_EventWindow->m_Kbd->IsKeyPressed(keycode);
	}

	std::vector<unsigned char> Input::GetPressedKeys() noexcept
	{
		std::vector<unsigned char> pressedKeys;

		for (unsigned int i = 0; i < s_EventWindow->m_Kbd->KeyCount; i++)
		{
			unsigned int _i = static_cast<unsigned char>(i);

			if (s_EventWindow->m_Kbd->IsKeyPressed(_i))
			{
				pressedKeys.push_back(_i);
			}
		}

		return pressedKeys;
	}
	
	void Input::SetupEventWindow(Window* eventWnd) noexcept
	{
		s_EventWindow = eventWnd;
	}
}
