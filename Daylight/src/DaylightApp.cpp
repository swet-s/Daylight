#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"

#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"

#include "Objects/Sphere.h"

#include <glm/gtc/type_ptr.hpp>

using namespace Walnut;

class RendererLayer : public Walnut::Layer
{
public:
	
	RendererLayer()
		: m_Camera(45.0f, 0.1f, 100.0f)
	{
		m_Scene.LightDir = { -1.0f, -1.0f, -1.0f };
		m_Scene.BgColor = { 0.1f, 0.2f, 0.3f, 1.0f };
	}

	virtual void OnUpdate(float ts) override
	{
		m_Camera.OnUpdate(ts);
}

	virtual void OnAttach() override
	{
		m_Scene.Objects.push_back(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 0.3f));
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Hierarchy");
		
		if (ImGui::BeginMenu("Create New Object"))
		{
		    if (ImGui::MenuItem("Sphere"))
		    {
		        m_Scene.Objects.push_back(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 0.3f));
		    }
		    ImGui::EndMenu();
		}
		
		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		
		static int node_clicked = -1; //todo make array of object a Renderer obj;
		
		for (size_t i = 0; i < m_Scene.Objects.size(); i++)
		{
		    auto& object = m_Scene.Objects[i];
		
		    ImGuiTreeNodeFlags node_flags = base_flags;
		    const bool is_selected = (node_clicked == i);
		    if (is_selected)
		        node_flags |= ImGuiTreeNodeFlags_Selected;
		
		    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		    ImGui::TreeNodeEx(&i, node_flags, "%s %d", object->m_Name.c_str(), i);
		    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		        node_clicked = i;
		}
		
		ImGui::End();

		// Inspector begins here
		ImGui::Begin("Inspector");


		ImGui::DragFloat3("Light Direction", glm::value_ptr(m_Scene.LightDir), 0.03f);

		// todo make active object and custumise it

		if (node_clicked != -1)
		{
			auto activeObject = m_Scene.Objects[node_clicked];

			ImGui::Separator();

			//ImGui::InputText("Name", activeObject->m_Name.c_str());

			ImGui::DragFloat3("Position", glm::value_ptr(activeObject->m_Transform.Position), 0.1f);
			ImGui::DragFloat3("Radius", glm::value_ptr(activeObject->m_Transform.Scale), 0.1f);
			ImGui::ColorEdit3("Albedo", glm::value_ptr(activeObject->m_Color));
			
			ImGui::Separator();
		}


		ImGui::Text("Last render: %.3fms", m_LastRenderTime);

		ImGui::End();

		// Creating Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));// Set Viewport Padding to 0
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;
	
		// Get the finalImage from the renderer and upload it to ImGui
		auto image = m_Renderer.GetFinalImage();
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
};


Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Daylight";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<RendererLayer>();
	//app->PushLayer<Renderer>();
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