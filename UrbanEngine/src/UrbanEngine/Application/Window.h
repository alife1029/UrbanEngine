#pragma once

#include "WindowConfig.h"

namespace UrbanEngine
{
	class Window
	{
	public:
		Window(const WindowConfig& winCfg);
		virtual ~Window();
		
		int Width() const noexcept;
		int Height() const noexcept;
		std::wstring Title() const noexcept;
		bool IsFullScreen() const noexcept;
		bool IsOpen() const noexcept;
		bool IsAlive() const noexcept;

		virtual void SetWidth(int width);
		virtual void SetHeight(int height);
		virtual void SetTitle(const std::wstring& title);
		virtual void SetFullScreenState(bool fullScreen);
		virtual void Show();
		virtual void Hide();

		virtual void ProcessEvents();
	protected:
		WindowConfig m_Properties;
		bool m_IsOpen;
		bool m_IsAlive;
	};
}
