#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <string>

#include "../Ray.h"

struct Transform
{
	glm::vec3 Position;
	glm::vec4 Rotation;
	glm::vec3 Scale;
};

class Object
{
public:
	Object() :
		m_Name("newObject") {}
	virtual float GetClosestHit(const Ray& ray) = 0;
public:
	std::string m_Name;
	Transform m_Transform;
	int m_MaterialIndex = 0;
};

