#pragma once

#include "Walnut/Application.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"

class RaytracingLayer : public Walnut::Layer
{
public:

	virtual void OnUIRender() override
	{

		ImGui::Begin("Settings");

		ImGui::Text("Last render: %.3fms", m_LastRenderTime);

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		ImGui::End();
		ImGui::PopStyleVar();

		//Walnut::Timer timer;


		//m_LastRenderTime = timer.ElapsedMillis();
	}

private:
	//Renderer m_Renderer;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	float m_LastRenderTime = 0.0f;
};

