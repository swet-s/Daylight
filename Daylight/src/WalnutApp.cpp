#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "RaytracingLayer.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<RaytracingLayer>();
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