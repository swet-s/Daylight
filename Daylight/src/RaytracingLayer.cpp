#include "RaytracingLayer.h"

void RaytracingLayer::OnAttach()
{
	//m_Raytracer->m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1.0f));
}

void RaytracingLayer::OnUIRender()
{

    ImGui::Begin("Hierarchy");



#if 0
    if (ImGui::TreeNode("Trees"))
    {
        if (ImGui::TreeNode("Advanced, with Selectable nodes"))
        {
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
            static bool test_drag_and_drop = true;


            // 'selection_mask' is dumb representation of what may be user-side selection state.
            //  You may retain selection state inside or outside your objects in whatever format you see fit.
            // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
            // of the loop. May be a pointer to your own node type, etc.
            static int selection_mask = (1 << 2);
            int node_clicked = -1;
            for (int i = 0; i < 6; i++)
            {
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
                ImGuiTreeNodeFlags node_flags = base_flags;
                const bool is_selected = (selection_mask & (1 << i)) != 0;
                if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;
                if (i < 3)
                {
                    // Items 0..2 are Tree Node
                    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                    if (test_drag_and_drop && ImGui::BeginDragDropSource())
                    {
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text("This is a drag and drop source");
                        ImGui::EndDragDropSource();
                    }
                    if (node_open)
                    {
                        ImGui::BulletText("Blah blah\nBlah Blah");
                        ImGui::TreePop();
                    }
                }
                else
                {
                    // Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                    // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                    ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                    if (test_drag_and_drop && ImGui::BeginDragDropSource())
                    {
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text("This is a drag and drop source");
                        ImGui::EndDragDropSource();
                    }
                }
            }
            if (node_clicked != -1)
            {
                // Update selection state
                // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
#endif

    if (ImGui::BeginMenu("Create New Object"))
    {
        if (ImGui::MenuItem("Sphere"))
        {
            m_Raytracer->m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(0, 0, 0), 1.0f));
        }
        ImGui::EndMenu();
    }

    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

    static int node_clicked = -1; //todo make array of object a RaytracingLayer obj;

    for (size_t i = 0; i < m_Raytracer->m_Objects.size(); i++)
    {
        auto& object = m_Raytracer->m_Objects[i];

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


    ImGui::DragFloat3("Light Direction", &m_Raytracer->m_LightDir.x, 0.03f);

    // todo make active object and custumise it

    if (node_clicked != -1)
    {
        auto activeObject = m_Raytracer->m_Objects[node_clicked];
        ImGui::ColorEdit4("Color", &activeObject->m_Color.r);
        ImGui::DragFloat3("Position", &activeObject->m_Transform.position.x, 0.03f);
        //ImGui::InputText("Name", &);
    }


    ImGui::Text("Last render: %.3fms", m_LastRenderTime);

    ImGui::End();

    // Creating Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    m_ViewportWidth = ImGui::GetContentRegionAvail().x;
    m_ViewportHeight = ImGui::GetContentRegionAvail().y;

    auto image = m_Raytracer->GetFinalImage();
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

	m_Raytracer->OnResize(m_ViewportWidth, m_ViewportHeight);
	m_Raytracer->Render();

	m_LastRenderTime = timer.ElapsedMillis();
}
