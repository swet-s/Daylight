#pragma once
#include <glm/glm.hpp>
#include "../ImGuiUtils/ImGuiUtils.h"

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

	// https://developer.download.nvidia.com/cg/saturate.html
	static float Saturate(float x)
	{
		return std::max(0.0f, std::min(1.0f, x));
	}

	// https://developer.download.nvidia.com/cg/smoothstep.html
	// interpolate smoothly between two input values based on a third
	static float SmoothStep(float a, float b, float x)
	{
		float t = Saturate((x - a) / (b - a));
		return t * t * (3.0f - (2.0f * t));
	}

	// https://developer.download.nvidia.com/cg/lerp.html
	//returns linear interpolation of two scalars or vectors based on a weight
	glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float w)
	{
		return a + w * (b - a);
	}

	// Source: Sabastian Lague - Ray Tracing(20:00)
	static glm::vec3 GetEnviromentLight(Ray ray, Sky sampleSky)
	{
		float skyGradientT = glm::pow(SmoothStep(0.0, 0.4, ray.Direction.y), 0.35f);
		glm::vec3 skyGradient = Lerp(sampleSky.SkyColorHorizon, sampleSky.SkyColorZenith, skyGradientT);

		// Create sun from the directional light
		float sun = glm::pow(std::max(0.0f, glm::dot(ray.Direction, -glm::normalize(sampleSky.SunLightDirection))), sampleSky.SunFocus) * sampleSky.SunIntensity;

		// Combine ground, sky, and sun
		float groundToSkyT = SmoothStep(-0.01f, 0.0f, ray.Direction.y);
		float sunMask = groundToSkyT >= 1;

		return Lerp(sampleSky.GroundColor, skyGradient, groundToSkyT) + sun * sunMask;
	}

}