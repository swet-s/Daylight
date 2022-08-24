#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <string>

struct Transform
{
	glm::vec3 position;
	glm::vec4 rotation;
	glm::vec3 scale;
};

class Object
{
public:
	virtual ~Object() = default;

	virtual void OnRender(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 lightDirection, glm::vec4& outColor) = 0;
public:
	std::string m_Name="newObj";
	Transform m_Transform;
	glm::vec4 m_Color;
};

