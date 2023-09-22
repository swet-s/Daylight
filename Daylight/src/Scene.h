#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Objects/Object.h"
#include "Material.h"

class Scene
{
public:
	glm::vec3 LightDir;
	glm::vec3 BgColor;
	std::vector<Material> Materials;
	std::vector<std::shared_ptr<Object>> Objects;

	Scene(const glm::vec3& LightDir, const glm::vec3& BgColor)
		: LightDir(LightDir), BgColor(BgColor) {}
};