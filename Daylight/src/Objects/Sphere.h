#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(Transform transform, glm::vec3 color = glm::vec3(1, 0, 1));
	Sphere(glm::vec3 centre, float radius, glm::vec3 color = glm::vec3(1, 0, 1));

	void SetPosition(glm::vec3 position) { m_Transform.Position = position; };
	void SetScale(glm::vec3 scale) { m_Transform.Scale = scale;  }
	// Todo SetRotation

	void SetColor(glm::vec4 color) { m_Color = color; }

	glm::vec3 GetPosition() { return m_Transform.Position; }
	glm::vec3 GetScale() { return m_Transform.Position; }
	// Todo GetRotation

	glm::vec3 GetColor() { return m_Color; }

	float GetClosestHit(const Ray& ray) override;
	//void OnRender(const Scene& scene, const Ray& ray, glm::vec4& outColor) override;
};

