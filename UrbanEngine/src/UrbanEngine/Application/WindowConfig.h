#pragma once

#include <string>

namespace UrbanEngine
{
	struct WindowConfig
	{
		int				width			= 800;
		int				height			= 600;
		std::wstring	title			= L"Urban Engine";
		bool			fullScreen		= false;
	};
}
