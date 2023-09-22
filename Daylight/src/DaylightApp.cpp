#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"

#include "Renderer/Renderer.h"
#include "Camera/Camera.h"
#include "Scene.h"

#include "Objects/Sphere.h"

#include "ImGuiUtils/ImGuiUtils.h"

using namespace Walnut;

class RendererLayer : public Walnut::Layer
{
public:
	RendererLayer()
		: m_Camera(45.0f, 0.1f, 100.0f), m_Scene(glm::vec3(-1.0f), glm::vec3(0.6f, 0.7f, 0.9f)) {}

	virtual void OnUpdate(float ts) override
	{
		// if camera is moved reset frameIndex
		if (m_Camera.OnUpdate(ts))
			m_Renderer.ResetFrameIndex();
	}

	virtual void OnAttach() override
	{
		m_Scene.Materials.push_back(Material({ "Orange",glm::vec3(0.9, 0.3, 0.0), 1.0f, 1.0f, 1.0f }));
		m_Scene.Materials.push_back(Material({ "Green",glm::vec3(0.1, 0.9, 0.2), 1.0f, 1.0f, 0.2f }));
		m_Scene.Materials.push_back(Material({ "Yellow",glm::vec3(0.9, 0.8, 0.0), 1.0f, 1.0f, 1.0f }));

		Sphere sphere1 = { glm::vec3(1.0, 2.0, 0.0), 0.7f, 0 };
		sphere1.setName("OrangeBall");

		m_Scene.Objects.push_back(std::make_shared<Sphere>(sphere1));
		m_Scene.Objects.push_back(std::make_shared<Sphere>(glm::vec3(-1.0, -1.0, 0.0), 0.7f, 1));
		m_Scene.Objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0, 0.0, -2.0), 0.7f, 2));
	}

	virtual void OnUIRender() override
	{
		ImGuiUtils::AddHierarchy(m_Scene);
		ImGuiUtils::AddInspector(m_Scene, m_LastRenderTime);
		ImGuiUtils::AddAssetsMenu(m_Scene);

		ImGuiUtils::AddViewPort(m_Renderer, m_ViewportWidth, m_ViewportHeight);

		//Rendering every frame
		Render();
	}

	void Render()
	{
		Timer timer;

		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render(m_Scene, m_Camera);

		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	Renderer m_Renderer;
	Camera m_Camera;
	Scene m_Scene;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	float m_LastRenderTime = 0.0f;
	bool m_accumulate = false;
};


Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Daylight";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<RendererLayer>();

	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {}

			if (ImGui::BeginMenu("Open"))
			{
				// 
				ImGui::MenuItem("fish_hat.c");
				ImGui::MenuItem("fish_hat.inl");
				ImGui::MenuItem("fish_hat.h");
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Save", "Ctrl+S")) {}

			if (ImGui::MenuItem("Save As..")) {}

			if (ImGui::MenuItem("Exit", "Alt+F4"))
			{
				app->Close();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
			if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {}
			if (ImGui::MenuItem("Cut", "Ctrl+X")) {}
			if (ImGui::MenuItem("Copy", "Ctrl+C")) {}
			if (ImGui::MenuItem("Paste", "Ctrl+V")) {}
			if (ImGui::MenuItem("Delete", "Del")) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}
	});
	return app;
}