#include "urbanpch.h"
#include "Keyboard.h"

namespace UrbanEngine
{
	Keyboard::Event::Event() noexcept
		:
		m_Type(Type::Invalid),
		m_Code(0u)
	{ }

	Keyboard::Event::Event(Type type, unsigned char code) noexcept
		:
		m_Type(type),
		m_Code(code)
	{ }
	
	bool Keyboard::Event::IsPress() const noexcept
	{
		return m_Type == Type::Press;
	}
	bool Keyboard::Event::IsRelease() const noexcept
	{
		return m_Type == Type::Release;
	}
	bool Keyboard::Event::IsValid() const noexcept
	{
		return m_Type != Type::Invalid;
	}
	unsigned char Keyboard::Event::GetCode() const noexcept
	{
		return m_Code;
	}
	




	bool Keyboard::IsKeyPressed(unsigned char keycode) const noexcept
	{
		return m_Keystates[keycode];
	}
	Keyboard::Event Keyboard::ReadKey() noexcept
	{
		if (m_Keybuffer.size() > 0u)
		{
			Keyboard::Event e = m_Keybuffer.front();
			m_Keybuffer.pop();
			return e;
		}

		return Event();
	}
	bool Keyboard::IsEmpty() const noexcept
	{
		return m_Keybuffer.empty();
	}
	void Keyboard::FlushKey() noexcept
	{
		m_Keybuffer = std::queue<Event>();
	}
	
	char Keyboard::ReadChar() noexcept
	{
		if (m_Charbuffer.size() > 0)
		{
			unsigned char charcode = m_Charbuffer.front();
			m_Charbuffer.pop();
			return charcode;
		}

		return 0;
	}
	bool Keyboard::IsCharEmpty() const noexcept
	{
		return m_Charbuffer.empty();
	}
	void Keyboard::FlushChar() noexcept
	{
		m_Charbuffer = std::queue<char>();
	}
	
	void Keyboard::Flush() noexcept
	{
		FlushKey();
		FlushChar();
	}
	
	void Keyboard::EnableAutorepeat() noexcept
	{
		m_AutoRepeatEnabled = true;
	}
	void Keyboard::DisableAutorepeat() noexcept
	{
		m_AutoRepeatEnabled = false;
	}
	bool Keyboard::IsAutorepeatEnabled() const noexcept
	{
		return m_AutoRepeatEnabled;
	}
	
	void Keyboard::OnKeyPressed(unsigned char keycode) noexcept
	{
		m_Keystates[keycode] = true;
		m_Keybuffer.push(Event(Event::Type::Press, keycode));
		TrimBuffer(m_Keybuffer);
	}
	void Keyboard::OnKeyReleased(unsigned char keycode) noexcept
	{
		m_Keystates[keycode] = false;
		m_Keybuffer.push(Event(Event::Type::Release, keycode));
		TrimBuffer(m_Keybuffer);
	}
	void Keyboard::OnChar(char character) noexcept
	{
		m_Charbuffer.push(character);
		TrimBuffer(m_Charbuffer);
	}
	
	void Keyboard::ClearState() noexcept
	{
		m_Keystates.reset();
	}
}
