#pragma once

#include "Walnut/Application.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"

#include "Raytracer.h"
#include "Objects/Sphere.h"

class RaytracingLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnUIRender() override;

	void Render();
private:
	std::shared_ptr<Raytracer> m_Raytracer = std::make_shared<Raytracer>();
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	float m_LastRenderTime = 0.0f;
};

