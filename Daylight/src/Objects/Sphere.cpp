#include "Sphere.h"

#include <iostream>

Sphere::Sphere(Transform transform)
{
	m_Transform = transform;
}

Sphere::Sphere(glm::vec3 centre, float radius, uint32_t materialIndex)
{
	m_Transform.Position = centre;
	m_Transform.Scale = glm::vec3(radius);
	m_MaterialIndex = materialIndex;
}

float Sphere::GetClosestHit(const Ray& ray)
{
	float radius = glm::dot(m_Transform.Scale, m_Transform.Scale);

	// P(t) = A + tB
	// (P-C)�(P-C) = r�
	// B�t� + 2�B�(A-C)t + (A-C)�(A-C) - r� = 0
	// where
	// A = ray origin
	// B = ray direction
	// C = centre of sphere
	// r = radius
	// t = hit distance
	
	glm::vec3 origin = ray.Origin - m_Transform.Position;

	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(origin, ray.Direction);
	float c = glm::dot(origin, origin) - radius * radius; //TODO deal with scale

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f) return std::numeric_limits<float>::max();

	float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
	float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)

	return closestT;


	//glm::vec3 hitPoint = origin + ray.Direction * closestT;
	//glm::vec3 normal = glm::normalize(hitPoint);



	//float lightIntensity = glm::max(glm::dot(normal, -scene.LightDir), 0.0f); // == cos(angle)

	//outColor = m_Color * lightIntensity;
}

