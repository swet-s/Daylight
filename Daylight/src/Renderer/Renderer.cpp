#include "Renderer.h"

#include "Walnut/Random.h"
#include "../Utils/ConvertToRGBA.h"
#include "../ImGuiUtils/ImGuiUtils.h"

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

	delete[] m_ImageData; //deleting nullptr is ok
	m_ImageData = new uint32_t[width * height]; 
	
	delete[] m_AccumulationData;
	m_AccumulationData = new glm::vec4[width * height];	
	ResetFrameIndex();
}


void Renderer::Render(const Scene& scene, const Camera& camera)
{
	m_ActiveScene = &scene;
	m_ActiveCamera = &camera;

	// reset m_AccumalationData to 0
	if (ImGuiUtils::getAccumulationStatus() && m_FrameIndex == 1)
		memset(m_AccumulationData, 0, m_FinalImage->GetWidth() * m_FinalImage->GetHeight() * sizeof(glm::vec4));

	// Iterate for every y for fast rendering
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			//Calculate color for every pixel 
			glm::vec4 color = PerPixel(x, y);

			if (ImGuiUtils::getAccumulationStatus()) {
				// add imageData over different frame
				m_AccumulationData[x + y * m_FinalImage->GetWidth()] += color;

				// get average by dividing with frameIndex
				glm::vec4 accumulatedColor = m_AccumulationData[x + y * m_FinalImage->GetWidth()];
				accumulatedColor /= (float)m_FrameIndex;

				// Clamp and set the color
				accumulatedColor = glm::clamp(accumulatedColor, glm::vec4(0.0f), glm::vec4(1.0f));
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(accumulatedColor);
			}
			else {
				m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
				m_FrameIndex = 0;
			}
			
		}
	}

	m_FinalImage->SetData(m_ImageData);

	m_FrameIndex++;
}

glm::vec4 Renderer::PerPixel(uint32_t x, uint32_t y)
{
	// Generate the ray and link it to the camera
	Ray ray;
	ray.Origin = m_ActiveCamera->GetPosition();
	ray.Direction = m_ActiveCamera->GetRayDirections()[x + y * m_FinalImage->GetWidth()];

	glm::vec3 light(0.0f);
	glm::vec3 throughput(1.0f);

	int bounces = 5;
	for (int i = 0; i < bounces; i++)
	{
		// Trace ray and get the HitPayload
		Renderer::HitPayload payload = TraceRay(ray);

		// We get here from Miss
		if (payload.HitDistance < 0.0f)
		{
			glm::vec3 skyColor = m_ActiveScene->BgColor;
			light += skyColor * throughput;
			//color += skyColor * multiplier;//
			break;
		}

		glm::vec3 lightDir = glm::normalize(m_ActiveScene->LightDir);
		float lightIntensity = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f); // == cos(angle)


		const std::shared_ptr<Object> object = m_ActiveScene->Objects[payload.ObjectIndex];
		const Material& material = m_ActiveScene->Materials[object->m_MaterialIndex];

		//glm::vec3 objectColor = material.Albedo;		
		//objectColor *= lightIntensity;
		//color = objectColor * multiplier; //

		throughput *= material.Albedo;
		light += material.GetEmission();

		//Place reflected ray origin slightly further along the normal from the intersection point.
		ray.Origin = payload.WorldPosition + payload.WorldNormal * 0.0001f;

		ray.Direction = glm::normalize(payload.WorldNormal + Walnut::Random::InUnitSphere());

		//ray.Direction = glm::reflect(ray.Direction, payload.WorldNormal + material.Roughness * Walnut::Random::Vec3(-0.5f, 0.5f));
	}

	return glm::vec4(light, 1.0f);
}


/*
* Below are the functions that returns a hitpayload after casting rays
*/

Renderer::HitPayload Renderer::TraceRay(const Ray& ray)
{
	int closestObjectIndex = -1;
	float hitDistance = std::numeric_limits<float>::max();

	for (size_t i = 0; i < m_ActiveScene->Objects.size(); i++)
	{
		const std::shared_ptr<Object> object = m_ActiveScene->Objects[i];

		float closestHit = object->GetClosestHit(ray);

		//Verify if the ClosestHit is in front of the camera
		if (closestHit > 0.0f && closestHit < hitDistance) 
		{
			hitDistance = closestHit;
			closestObjectIndex = (int)i;
		}
	}

	if (closestObjectIndex < 0)
		return Miss(ray);


	return ClosestHit(ray, hitDistance, closestObjectIndex);
}

Renderer::HitPayload Renderer::ClosestHit(const Ray& ray, float hitDistance, int objectIndex)
{
	Renderer::HitPayload payload;
	payload.HitDistance = hitDistance;
	payload.ObjectIndex = objectIndex;

	const std::shared_ptr<Object> closestObject = m_ActiveScene->Objects[objectIndex];


	// TODO calcutate normal for different object diffrently

	// subract the ray origin by the object position to displace the object 
	glm::vec3 origin = ray.Origin - closestObject->m_Transform.Position;

	payload.WorldPosition = origin + ray.Direction * hitDistance;
	payload.WorldNormal = glm::normalize(payload.WorldPosition);

	// add back the object position to the ray origin after calculating the color
	payload.WorldPosition += closestObject->m_Transform.Position;


	return payload;
}

Renderer::HitPayload Renderer::Miss(const Ray& ray)
{
	Renderer::HitPayload payload;
	payload.HitDistance = -1.0f;
	return payload;
}


