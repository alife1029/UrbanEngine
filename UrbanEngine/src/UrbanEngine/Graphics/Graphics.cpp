#include "urbanpch.h"
#include "Graphics.h"
#include "UrbanEngine/Application/Window.h"

namespace UrbanEngine
{
	Graphics::Graphics(Window* window)
		:
		m_TargetWindow(window),
		m_API(API::NONE)
	{ }

	Graphics::~Graphics() 
	{ }
	
	void Graphics::EndFrame()
	{ }
	
	void Graphics::ClearBuffer(float red, float green, float blue, float alpha) noexcept
	{ }
	
	void Graphics::DrawIndexed(unsigned int count) noexcept(!URBAN_IS_DEBUG)
	{ }
	
	Graphics::API Graphics::GetRendererAPI() const noexcept
	{
		return m_API;
	}
}
