#include "RaytracingLayer.h"

void RaytracingLayer::OnUIRender()
{
	ImGui::Begin("Settings");

	if (ImGui::Button("Render"))
	{
		Render();
	}

	ImGui::Text("Last render: %.3fms", m_LastRenderTime);

	ImGui::End();

	// Creating Viewport
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");

	m_ViewportWidth = ImGui::GetContentRegionAvail().x;
	m_ViewportHeight = ImGui::GetContentRegionAvail().y; 
	
	auto image = m_Raytracer.GetFinalImage();
	if (image)
	{
		// Deploying the image
		ImVec2 size = { (float)image->GetWidth(), (float)image->GetHeight() };
		ImGui::Image(image->GetDescriptorSet(), size, ImVec2(0, 1), ImVec2(1, 0));
	}

	ImGui::End();
	ImGui::PopStyleVar();

	//Rendering every frame
	Render();
}

void RaytracingLayer::Render()
{
	Walnut::Timer timer;

	m_Raytracer.OnResize(m_ViewportWidth, m_ViewportHeight);
	m_Raytracer.Render();

	m_LastRenderTime = timer.ElapsedMillis();
}
