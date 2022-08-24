#pragma once

#include "Walnut/Image.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Objects/Object.h"

class Raytracer
{
public:
	Raytracer() : 
		m_LightDir(glm::vec3(-1, -1, -1)), 
		m_BgColor(glm::vec4(0, 0, 0, 0)) {}

	void OnResize(uint32_t width, uint32_t height);
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
private:
	glm::vec4 PerPixel(glm::vec2 coord);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;

public:
	glm::vec3 m_LightDir;
	glm::vec4 m_BgColor;
	std::vector<std::shared_ptr<Object>> m_Objects;
};