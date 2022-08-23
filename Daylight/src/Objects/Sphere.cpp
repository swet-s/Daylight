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

void Sphere::OnRender(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 lightDirection, glm::vec4& outColor)
{
	float radius = 0.3f;
	//rayDirection = glm::normalize(rayDirection);

	// P(t) = A + tB
	// (P-C)•(P-C) = r²
	// B²t² + 2•B•(A-C)t + (A-C)•(A-C) - r² = 0
	// where
	// A = ray origin
	// B = ray direction
	// C = centre of sphere
	// r = radius
	// t = hit distance

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayDirection, rayOrigin - m_Transform.position);
	float c = glm::dot(rayOrigin - m_Transform.position, rayOrigin - m_Transform.position) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f) return;

	float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
	float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a); // Second hit distance (currently unused)

	glm::vec3 hitPoint = rayOrigin + rayDirection * closestT;
	glm::vec3 normal = glm::normalize(hitPoint);

	float lightIntensity = glm::max(glm::dot(normal, -lightDirection), 0.0f); // == cos(angle)

	outColor = m_Color * lightIntensity;
}