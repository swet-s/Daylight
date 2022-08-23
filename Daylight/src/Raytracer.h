#pragma once

#include "Walnut/Image.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Objects/Sphere.h"

class Raytracer
{
public:
	Raytracer() : 
		m_LightDir(glm::vec3(-1, -1, -1)), 
		m_BgColor(glm::vec4(0, 0, 0, 0)), 
		m_Sphere(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1.0f)) {}

	void OnResize(uint32_t width, uint32_t height);
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
private:
	glm::vec4 PerPixel(glm::vec2 coord);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;

	std::shared_ptr<Sphere> m_Sphere;
public:
	glm::vec3 m_LightDir;
	glm::vec4 m_BgColor;
};