#include "ImGuiUtils.h"

#include "imgui.h"
#include "../Objects/Sphere.h"

#include <glm/gtc/type_ptr.hpp>

bool ImGuiUtils::s_AccumulateImage = false;
int ImGuiUtils::s_NodeClicked = -1; 
ImGuiUtils::NodeType ImGuiUtils::s_ClickedNodeType = ImGuiUtils::NodeType::None;
ImGuiTreeNodeFlags ImGuiUtils::s_BaseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

void ImGuiUtils::AddHierarchy(Scene& activeScene)
{
	ImGui::Begin("Hierarchy");

	ImGui::SameLine(ImGui::GetWindowWidth() - 20.0f);
	if (ImGui::BeginMenu("+"))
	{
		if (ImGui::BeginMenu("NewObject"))
		{
			if (ImGui::MenuItem("Sphere"))
			{
				activeScene.Objects.push_back(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 0.3f));
			}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("NewMaterial"))
		{
			activeScene.Materials.push_back({ "NewMaterial",glm::vec3(1.0, 0.0, 1.0), 1.0f, 0.0f, 0.0f });
		}
		ImGui::EndMenu();
	}

	ImGui::Separator();

	ImGui::TextColored(ImVec4(0.3f, 0.6f, 1.0f, 1.0f), "Objects");

	for (size_t i = 0; i < activeScene.Objects.size(); i++)
	{
		auto& object = activeScene.Objects[i];

		ImGuiTreeNodeFlags node_flags = s_BaseFlags;
		const bool is_selected = (s_NodeClicked == i);
		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		// TODO: some check for unique name
		ImGui::TreeNodeEx(&i, node_flags, "%s[%d]", object->getName(), i);
		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			s_NodeClicked = i;
			s_ClickedNodeType = NodeType::Object;
		}
	}

	ImGui::Separator();

	ImGui::TextColored(ImVec4(0.3f, 0.6f, 1.0f, 1.0f), "Materials");

	for (size_t i = 0; i < activeScene.Materials.size(); i++)
	{
		auto& material = activeScene.Materials[i];

		ImGuiTreeNodeFlags node_flags = s_BaseFlags;
		const bool is_selected = (s_NodeClicked == i);
		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		// TODO: some check for unique name
		ImGui::TreeNodeEx(&i, node_flags, "%s[%d]", material.Name.c_str(), i);
		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			s_NodeClicked = i;
			s_ClickedNodeType = NodeType::Material;
		}
	}
	ImGui::End();
}


void ImGuiUtils::AddInspector(Scene& activeScene, float lastRenderTime)
{
	ImGui::Begin("Inspector");


	ImGui::DragFloat3("Light Direction", glm::value_ptr(activeScene.LightDir), 0.03f);
	ImGui::ColorEdit3("Sky Color", glm::value_ptr(activeScene.BgColor), 0.03f);

	ImGui::Separator();


	if (s_ClickedNodeType == NodeType::Object &&  s_NodeClicked != -1)
	{
		auto activeObject = activeScene.Objects[s_NodeClicked];

		ImGui::Separator();

		char nameBuffer[256]; // Assuming a maximum name length of 255 characters
		strcpy(nameBuffer, activeObject->getName().c_str());
		ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_EnterReturnsTrue);
		activeObject->setName(nameBuffer);

		ImGui::DragFloat3("Position", glm::value_ptr(activeObject->m_Transform.Position), 0.1f);
		ImGui::DragFloat3("Radius", glm::value_ptr(activeObject->m_Transform.Scale), 0.1f);

		if (ImGui::BeginCombo("Material", activeScene.Materials[activeObject->m_MaterialIndex].Name.c_str()))
		{
			for (int i = 0; i < activeScene.Materials.size(); ++i)
			{
				bool isSelected = (activeObject->m_MaterialIndex == i);
				if (ImGui::Selectable(activeScene.Materials[i].Name.c_str(), isSelected))
					activeObject->m_MaterialIndex = i;

				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::Separator();
	}
	else if (s_ClickedNodeType == NodeType::Material && s_NodeClicked != -1)
	{
		auto& activeMaterial = activeScene.Materials[s_NodeClicked];

		ImGui::Separator();
		
		char nameBuffer[256]; // Assuming a maximum name length of 255 characters
		strcpy(nameBuffer, activeMaterial.Name.c_str());
		ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_EnterReturnsTrue);
		activeMaterial.Name = nameBuffer;

		ImGui::ColorEdit3("Albedo", glm::value_ptr(activeMaterial.Albedo), 0.1f);
		ImGui::DragFloat("Roughness", &activeMaterial.Roughness, 0.1f);
		ImGui::DragFloat("Metallic", &activeMaterial.Metallic, 0.1f);
		ImGui::DragFloat("EmissionPower", &activeMaterial.EmissionPower, 0.1f);

		ImGui::Separator();
	}

	ImGui::Checkbox("Accumulate", &s_AccumulateImage);

	ImGui::Text("Last render: %.3fms", lastRenderTime);

	ImGui::End();
}

void ImGuiUtils::AddAssetsMenu(Scene& activeScene)
{
	ImGui::Begin("Asset");

	if (ImGui::BeginMenu("Create New Material"))
	{
		if (ImGui::MenuItem("Default Material"))
		{
			activeScene.Materials.push_back(Material({ "new", glm::vec3(1.0f, 0.0f, 1.0f), 1.0f, 1.0f, 1.0f}));
		}
		ImGui::EndMenu();
	}

	ImGui::End();
}

void ImGuiUtils::AddViewPort(Renderer& renderer, uint32_t& viewportWidth, uint32_t& viewportHeight)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));// Set Viewport Padding to 0
	ImGui::Begin("Viewport");

	viewportWidth = ImGui::GetContentRegionAvail().x;
	viewportHeight = ImGui::GetContentRegionAvail().y;

	// Get the finalImage from the renderer and upload it to ImGui
	auto image = renderer.GetFinalImage();
	if (image)
	{
		// Deploying the image
		ImVec2 size = { (float)image->GetWidth(), (float)image->GetHeight() };
		ImGui::Image(image->GetDescriptorSet(), size, ImVec2(0, 1), ImVec2(1, 0));
	}

	ImGui::End();
	ImGui::PopStyleVar();
}
