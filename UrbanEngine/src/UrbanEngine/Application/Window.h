#pragma once

#include "WindowConfig.h"
#include "Keyboard.h"
#include "UrbanEngine/Graphics/Graphics.h"

namespace UrbanEngine
{
	class Window
	{
		friend class Input;
	public:
		Window(const WindowConfig& winCfg);
		virtual ~Window();
		
		int Width() const noexcept;
		int Height() const noexcept;
		std::wstring Title() const noexcept;
		bool IsFullScreen() const noexcept;
		bool IsOpen() const noexcept;

		virtual void SetWidth(int width);
		virtual void SetHeight(int height);
		virtual void SetTitle(const std::wstring& title);
		virtual void SetFullScreenState(bool fullScreen);
		virtual void Show();
		virtual void Hide();

		virtual void ProcessEvents();
		virtual void CreateGraphicContext(Graphics::API api);

		Graphics* Gfx() const noexcept;
	protected:
		WindowConfig m_Properties;
		bool m_IsOpen;
		Keyboard m_Kbd;
		Graphics* m_Graphics;
	};
}
