#include "Editor.h"

IMaterial *CEditor::CreateMaterial(const char *szInput)
{
	static int nCreatedMats = 0;
	char szOut[512];
	sprintf_s(szOut, sizeof(szOut), "mat%i.vmt", nCreatedMats++);

	char szMaterial[512];
	sprintf_s(szMaterial, sizeof(szMaterial), szInput);

	CKeyValues *pVals = new CKeyValues;
	pVals->Initialize((char *)szOut);
	pVals->LoadFromBuffer(szOut, szMaterial);

	IMaterial *pCreated = g_pMaterialSystem->CreateMaterial(szOut, pVals);
	pCreated->IncrementReferenceCount();

	return pCreated;
}

bool CEditor::IsOpen()
{
	return m_bOpen;
}

bool CEditor::IsUnloading()
{
	return m_bUnload;
}

IMaterial *CEditor::GetLoadedMaterial()
{
	return m_pMaterial;
}

void CEditor::Render(IDirect3DDevice9 *pDevice)
{
	static bool bInitImGui = false;

	if (!bInitImGui)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindowA(0, "Team Fortress 2"));
		ImGui_ImplDX9_Init(pDevice);

		ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_::ImGuiConfigFlags_NoMouseCursorChange;

		ImVec4 *colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.14f, 0.16f, 0.11f, 0.52f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.30f, 0.23f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.32f, 0.24f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.30f, 0.22f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.27f, 0.21f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Button] = ImVec4(0.29f, 0.34f, 0.26f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Header] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.42f, 0.31f, 0.6f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.11f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.23f, 0.18f, 0.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.57f, 0.51f, 0.78f);
		colors[ImGuiCol_TabActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.73f, 0.67f, 0.24f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		ImGuiStyle &style = ImGui::GetStyle();
		style.FrameBorderSize = 1.0f;
		style.WindowRounding = 0.0f;
		style.ChildRounding = 0.0f;
		style.FrameRounding = 0.0f;
		style.PopupRounding = 0.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.0f;

		bInitImGui = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		g_pSurface->SetCursorAlwaysVisible(m_bOpen = !m_bOpen);

	if (m_bOpen)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::SetWindowSize(ImVec2(300, 300), ImGuiCond_Once);

			ImGui::PushItemWidth(200);

			if (ImGui::Button("Reset"))
				m_pMaterial = nullptr;

			ImGui::SameLine();

			if (ImGui::Button("Unload"))
				m_bUnload = true;

			char input[20] = { '\0' };

			if (ImGui::InputText("Add", input, 20, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
			{
				std::string input_str = std::string(input);

				auto AlreadyExists = [&]() -> bool
				{
					for (const auto &mat : m_vecMaterials)
					{
						if (!input_str.compare(mat.m_sName))
							return true;
					}

					return false;
				};

				if (input_str.length() > 0 && !AlreadyExists())
					m_vecMaterials.push_back({ input_str });
			}

			if (ImGui::ListBoxHeader("Materials"))
			{
				for (auto &mat : m_vecMaterials)
				{
					if (ImGui::Selectable(mat.m_sName.c_str()))
						mat.m_bOpen = true;
				}

				ImGui::ListBoxFooter();
			}

			ImGui::PopItemWidth();

			ImGui::End();
		}

		for (auto &mat : m_vecMaterials)
		{
			if (!mat.m_bOpen)
				continue;

			if (ImGui::Begin(mat.m_sName.c_str(), nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse))
			{
				if (ImGui::Button("Load"))
					m_pMaterial = CreateMaterial(mat.m_Text.GetText().c_str());
				
				ImGui::SameLine();

				if (ImGui::Button("Close"))
					mat.m_bOpen = false;

				ImGui::SameLine();

				if (ImGui::Button("Remove"))
				{
					for (size_t n = 0; n < m_vecMaterials.size(); n++)
					{
						std::string sName = m_vecMaterials[n].m_sName;

						if (!sName.compare(mat.m_sName)) {
							m_vecMaterials.erase(m_vecMaterials.begin() + n);
							break;
						}
					}
				}

				mat.m_Text.Render("Vars", ImVec2(-1, -1));
				
				ImGui::End();
			}
		}
		
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
}