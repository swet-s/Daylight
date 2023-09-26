#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

#include "Objects/Object.h"
#include "Material.h"


struct Sky
{
	float SunFocus=1000.0f;
	float SunIntensity=100.0f;
	

	glm::vec3 SkyColorHorizon = glm::vec3(0.4f, 0.3f, 0.1f);
	glm::vec3 SkyColorZenith = glm::vec3(0.3f, 0.5f, 0.8f);

	glm::vec3 GroundColor = glm::vec3(0.12f, 0.12f, 0.2f);

	glm::vec3 getDirection()
	{
		glm::vec3 forward = { -11.0, 0.0, 0.0 };
		glm::vec3 eularRadian = glm::radians(SunLightRotation);
		glm::quat rotationQuat = glm::quat(eularRadian);

		return glm::normalize(rotationQuat * forward);
	}

	glm::vec3 SunLightRotation = glm::vec3(0.0f, 75.0f, 60.0f);
};


class Scene
{
public:
	Sky SampleSky;
	std::vector<Material> Materials;
	std::vector<std::shared_ptr<Object>> Objects;
};