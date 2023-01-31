#include "urbanpch.h"
#include "Graphics.h"
#include "UrbanEngine/Application/Window.h"

namespace UrbanEngine
{
	Graphics::Graphics(Window* window)
		:
		m_TargetWindow(window),
		m_Projection(glm::mat4(1.0f)),
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
	
	void Graphics::SetProjection(const glm::mat4& projectionMatrix) noexcept
	{
		m_Projection = projectionMatrix;
	}

	glm::mat4 Graphics::Projection() const noexcept
	{
		return m_Projection;
	}
	
	Graphics::API Graphics::GetRendererAPI() const noexcept
	{
		return m_API;
	}
}
