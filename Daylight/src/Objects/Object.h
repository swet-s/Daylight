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
	std::string getName() { return m_Name; }
	void setName(std::string name) { m_Name = name; }

	virtual float GetClosestHit(const Ray& ray) = 0;
public:
	Transform m_Transform;
	int m_MaterialIndex = 0;
private:
	std::string m_Name;
};

