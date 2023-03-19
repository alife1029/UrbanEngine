#pragma once

#include <queue>
#include <bitset>

namespace UrbanEngine
{
	class Keyboard
	{
		friend class Window;
		friend class Win32Window; // TODO: Try to remove this by inheritance
	public:
		class Event
		{
		public:
			enum class Type
			{
				Press,
				Release,
				Invalid
			};
			
		private:
			Type m_Type;
			unsigned char m_Code;

		public:
			Event() noexcept;
			Event(Type type, unsigned char code) noexcept;
			bool IsPress() const noexcept;
			bool IsRelease() const noexcept;
			bool IsValid() const noexcept;
			unsigned char GetCode() const noexcept;
		};

	public:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;

		bool IsKeyPressed(unsigned char keycode) const noexcept;
		char ReadChar() noexcept;

		void EnableAutorepeat() noexcept;
		void DisableAutorepeat() noexcept;
		bool IsAutorepeatEnabled() const noexcept;

	private:
		Event ReadKey() noexcept;
		bool IsEmpty() const noexcept;
		void FlushKey() noexcept;

		bool IsCharEmpty() const noexcept;
		void FlushChar() noexcept;

		void Flush() noexcept;

	private:
		void OnKeyPressed(unsigned char keycode) noexcept;
		void OnKeyReleased(unsigned char keycode) noexcept;
		void OnChar(char character) noexcept;
		void ClearState() noexcept;
		template<typename T>
		inline static void TrimBuffer(std::queue<T>& buffer) noexcept;
	
	private:
		static constexpr unsigned int m_Keys = 256u;
		static constexpr unsigned int m_BufferSize = 16u;
		bool m_AutoRepeatEnabled = false;
		std::bitset<m_Keys> m_Keystates;
		std::queue<Event> m_Keybuffer;
		std::queue<char> m_Charbuffer;
	};
	
	template<typename T>
	inline void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > m_BufferSize)
		{
			buffer.pop();
		}
	}
}
