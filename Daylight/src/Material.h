#pragma once
#include <string>
#include <glm/glm.hpp>

struct Material
{
	std::string Name;
public:
	glm::vec3 Albedo{ 1.0f };
	float Roughness = 1.0f;
	float Metallic = 0.0f;

	float EmissionPower = 0.0f;

	// Emission Color is kept same as Albedo for now
	glm::vec3 GetEmission() const { return Albedo * EmissionPower; }
};