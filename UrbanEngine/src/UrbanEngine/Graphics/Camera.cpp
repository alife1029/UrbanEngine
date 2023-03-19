#include "Camera.h"
#include "BaseViewport.h"

#include <glm/gtc/matrix_transform.hpp>

namespace UrbanEngine
{
	Camera::Camera()
		:
		m_ViewProj(1.0f),
		m_Position(0.0f),
		m_Rotation(0.0f),
		m_Size(5.0f)
	{
	}
	
	void Camera::Update() noexcept
	{
		glm::mat4 view = glm::translate(
				glm::rotate(
					glm::mat4(1.0f), 
					-glm::radians(m_Rotation), 
					{ 0.0f, 0.0f, 1.0f }), 
				-m_Position);

		float left = m_Size * BaseViewport::GetAspectRatio() / -2.0f;
		float top = m_Size / 2.0f;
		glm::mat proj = glm::ortho(left, -left, -top, top);

		m_ViewProj = proj * view;
	}
	
	glm::mat4 Camera::ViewProjMatrix() const noexcept
	{
		return m_ViewProj;
	}
	glm::vec3 Camera::Position() const noexcept
	{
		return m_Position;
	}
	float Camera::Rotation() const noexcept
	{
		return m_Rotation;
	}
	float Camera::Size() const noexcept
	{
		return m_Size;
	}
	
	void Camera::SetPosition(const glm::vec3& pos) noexcept
	{
		m_Position = pos;
	}
	
	void Camera::SetRotation(float rot) noexcept
	{
		m_Rotation = rot;
	}
	void Camera::SetSize(float size) noexcept
	{
		m_Size = size;
	}
}
