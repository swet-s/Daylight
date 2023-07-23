#include "Sphere.h"

#include <iostream>

Sphere::Sphere(Transform transform, glm::vec4 color)
{
	m_Transform = transform;
	m_Color = color;
}

Sphere::Sphere(glm::vec3 centre, float radius, glm::vec4 color)
{
	m_Transform.position = centre;
	m_Transform.scale = glm::vec3(radius);
	m_Color = color;
}

void Sphere::OnRender(Ray ray, glm::vec3 lightDirection, glm::vec4& outColor)
{
	float radius = 0.3f;

	// P(t) = A + tB
	// (P-C)�(P-C) = r�
	// B�t� + 2�B�(A-C)t + (A-C)�(A-C) - r� = 0
	// where
	// A = ray origin
	// B = ray direction
	// C = centre of sphere
	// r = radius
	// t = hit distance

	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(ray.Direction, ray.Origin - m_Transform.position);
	float c = glm::dot(ray.Origin - m_Transform.position, ray.Origin - m_Transform.position) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f) return;

	float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
	float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)

	glm::vec3 origin = ray.Origin - m_Transform.position; // for uniform lighting
	glm::vec3 hitPoint = origin + ray.Direction * closestT;
	glm::vec3 normal = glm::normalize(hitPoint);

	float lightIntensity = glm::max(glm::dot(normal, -lightDirection), 0.0f); // == cos(angle)

	outColor = m_Color * lightIntensity;
}