#include "UrbanEngine/Application/Keyboard.h"

namespace UrbanEngine
{
	class Win32Keyboard : public Keyboard
	{
		friend class Win32Window;
		using Keyboard::Keyboard;
	};
}
