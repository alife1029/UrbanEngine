#pragma once

#include "Graphics.h"
#include "UrbanEngine/Application/Window.h"

namespace UrbanEngine
{
	class BaseViewport
	{
	public:
		static void UpdateAsFillViewport(Window* target);
		static void UpdateAsFitViewport(Window* target, float aspectRatio);

		static int GetX();
		static int GetY();
		static int GetWidth();
		static int GetHeight();
		static float GetAspectRatio();

	private:
		static void Update(Graphics* gfx);

	private:
		static int s_X;
		static int s_Y;
		static int s_Width;
		static int s_Height;
		static float s_AspectRatio;
	};
}
