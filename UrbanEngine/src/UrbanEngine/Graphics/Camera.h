#pragma once

#include <glm/glm.hpp>

namespace UrbanEngine
{
	class Camera
	{
	public:
		Camera();

		void Update() noexcept;

		glm::mat4 ViewProjMatrix() const noexcept;
		glm::vec3 Position() const noexcept;
		float Rotation() const noexcept;
		float Size() const noexcept;
		
		void SetPosition(const glm::vec3& pos) noexcept;
		void SetRotation(float rot) noexcept;
		void SetSize(float size) noexcept;

	private:
		glm::mat4 m_ViewProj;
		glm::vec3 m_Position;
		float m_Rotation;
		float m_Size;
	};
}
