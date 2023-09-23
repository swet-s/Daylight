#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Objects/Object.h"
#include "Material.h"


struct Sky
{
	float SunFocus=100.0f;
	float SunIntensity=1.0f;
	
	glm::vec3 SunLightDirection = glm::vec3(-1.0f);
	glm::vec3 SkyColorHorizon = glm::vec3(0.4f, 0.3f, 0.1f);
	glm::vec3 SkyColorZenith = glm::vec3(0.3f, 0.5f, 0.8f);

	glm::vec3 GroundColor = glm::vec3(0.12f, 0.12f, 0.2f);
};


class Scene
{
public:
	Sky SampleSky;
	std::vector<Material> Materials;
	std::vector<std::shared_ptr<Object>> Objects;
};