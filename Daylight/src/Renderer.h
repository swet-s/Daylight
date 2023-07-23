#pragma once

#include "Walnut/Image.h"

#include "Objects/Sphere.h"

#include "Camera.h"
#include "Ray.h"

#include <memory>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer():
		m_LightDir(glm::vec3(-1, -1, -1)),
		m_BgColor(glm::vec4(0.1f, 0.2f, 0.3f, 0.4f)) {}

	void OnResize(uint32_t width, uint32_t height);
	void Render(const Camera& camera);

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
private:
	glm::vec4 TraceRay(const Ray& ray);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;

	//------//
public:
	glm::vec3 m_LightDir;
	glm::vec4 m_BgColor;
	std::vector<std::shared_ptr<Object>> m_Objects;
};
