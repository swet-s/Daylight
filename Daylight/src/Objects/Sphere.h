#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(Transform transform);
	Sphere(glm::vec3 centre, float radius, uint32_t materialIndex = 0);

	void SetPosition(glm::vec3 position) { m_Transform.Position = position; };
	void SetScale(glm::vec3 scale) { m_Transform.Scale = scale; }
	// Todo SetRotation


	glm::vec3 GetPosition() const { return m_Transform.Position; }
	glm::vec3 GetScale() const { return m_Transform.Position; }
	// Todo GetRotation


	float GetClosestHit(const Ray& ray) override;
};

