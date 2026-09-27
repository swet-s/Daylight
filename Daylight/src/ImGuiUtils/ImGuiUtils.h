#pragma once
#include "../Scene.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"
#include "imgui.h"

class ImGuiUtils
{
public:
	enum class NodeType
	{
		None,
		Object,
		Material
	};

	static void AddHierarchy(Scene& activeScene);
	// Returns true if the camera was changed from the UI
	static bool AddInspector(Scene& activeScene, Camera& camera, float lastRenderTime);
	static void AddViewPort(Renderer& renderer, uint32_t& viewportWidth, uint32_t& viewportHeight);

	static bool getAccumulationStatus() { return s_AccumulateImage; }
	static int getBounce() { return s_NumberOfBounces; }
private:
	static bool s_AccumulateImage;
	static int s_NumberOfBounces;

	static int s_NodeClicked; 
	static NodeType s_ClickedNodeType;

	static ImGuiTreeNodeFlags s_BaseFlags; 
};

