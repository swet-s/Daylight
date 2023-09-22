#pragma once
#include "../Scene.h"
#include "../Renderer/Renderer.h"
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
	static void AddInspector(Scene& activeScene, float lastRenderTime);
	static void AddAssetsMenu(Scene& activeScene);
	static void AddViewPort(Renderer& renderer, uint32_t& viewportWidth, uint32_t& viewportHeight);

	static bool getAccumulationStatus() { return s_AccumulateImage; }
private:
	static bool s_AccumulateImage;

	static int s_NodeClicked; 
	static NodeType s_ClickedNodeType;

	static ImGuiTreeNodeFlags s_BaseFlags; 
};

