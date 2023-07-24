#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Objects/Object.h"

struct Scene
{
	glm::vec3 LightDir;
	glm::vec4 BgColor;
	std::vector<std::shared_ptr<Object>> Objects;
};