#pragma once

namespace UrbanEngine
{
	class Time
	{
		friend class App;
	public:
		static float Delta();
		static float Elapsed();
	private:
		static void Update();
	};
}
