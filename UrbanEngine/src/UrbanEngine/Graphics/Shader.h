#pragma once

#include "UrbanEngine/UrbanException.h"
#include "Graphics.h"

#include <string>

namespace UrbanEngine
{
	class Shader
	{
	public:
		Shader(Graphics* gfx, const std::string& vsFile, const std::string& psFile);
		virtual ~Shader();
		virtual void Bind();
	};
}
