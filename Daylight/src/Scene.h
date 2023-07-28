#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Objects/Object.h"

struct Material
{
	glm::vec3 Albedo{ 1.0f };
	float Roughness = 1.0f;
	float Metallic = 0.0f;
	float Emission = 0.0f;
};

struct Scene
{
	glm::vec3 LightDir;
	glm::vec3 BgColor;
	std::vector<Material> Materials;
	std::vector<std::shared_ptr<Object>> Objects;
};