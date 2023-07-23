#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <string>

#include "../Ray.h"

struct Transform
{
	glm::vec3 position;
	glm::vec4 rotation;
	glm::vec3 scale;
};

class Object
{
public:
	Object() :
		m_Name("newObject") {}
	virtual void OnRender(Ray ray, glm::vec3 lightDirection, glm::vec4& outColor) = 0;
public:
	std::string m_Name;
	Transform m_Transform;
	glm::vec4 m_Color;
};

