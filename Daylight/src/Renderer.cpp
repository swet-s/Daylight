#include "Renderer.h"

namespace Utils {

	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
		return result;
	}

}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		// No resize necessary
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;

		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}





void Renderer::Render(const Scene& scene, const Camera& camera)
{
	Ray ray;
	ray.Origin = camera.GetPosition();

	// Iterate for every y for fast rendering
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			ray.Direction = camera.GetRayDirections()[x + y * m_FinalImage->GetWidth()];
			glm::vec4 color = TraceRay(scene, ray);

			color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
			m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

glm::vec4 Renderer::TraceRay(const Scene& scene, const Ray& ray)
{
	glm::vec4 outColor = scene.BgColor;

	if (scene.Objects.size() == 0)
		return glm::vec4(0, 0, 0, 1);

	std::shared_ptr<Object> closestObject = nullptr; //Is it the correct way?
	float hitDistance = std::numeric_limits<float>::max();


	for (std::shared_ptr<Object> object : scene.Objects)
	{
		float closestHit = object->GetClosestHit(ray); 
		if (closestHit < hitDistance)
		{
			hitDistance = closestHit;
			closestObject = object;
		}
		//object->OnRender(scene, ray, outColor);
	}
	
	if (closestObject == nullptr)
		return scene.BgColor;

	// TODO calcutate normal for different object diffrently
	glm::vec3 origin = ray.Origin - closestObject->m_Transform.Position;
	glm::vec3 hitPoint = origin + ray.Direction * hitDistance;
	glm::vec3 normal = glm::normalize(hitPoint);

	float lightIntensity = glm::max(glm::dot(normal, -glm::normalize(scene.LightDir)), 0.0f); // == cos(angle)

	return closestObject->m_Color * lightIntensity;
}