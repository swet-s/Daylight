#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(Transform transform, glm::vec4 color = glm::vec4(1, 0, 1, 1));
	Sphere(glm::vec3 centre, float radius, glm::vec4 color = glm::vec4(1, 0, 1, 1));

	void SetPosition(glm::vec3 position) { m_Transform.position = position; };
	void SetScale(glm::vec3 scale) { m_Transform.scale = scale;  }
	// Todo SetRotation

	void SetColor(glm::vec4 color) { m_Color = color; }

	glm::vec3 GetPosition() { return m_Transform.position; }
	glm::vec3 GetScale() { return m_Transform.position; }
	// Todo GetRotation

	glm::vec4 GetColor() { return m_Color; }

	void OnRender(Ray ray, glm::vec3 lightDirection, glm::vec4& outColor) override;
};

