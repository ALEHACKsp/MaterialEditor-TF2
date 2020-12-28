#include "Editor.h"
#include "../SDK/SDK.h"

bool CEditor::IsOpen()
{
	return m_bOpen;
}

void CEditor::Render(IDirect3DDevice9 *pDevice)
{
	//Init ImGui
	{
		static bool bInitImGui = false;

		if (!bInitImGui) {
			ImGui::CreateContext();
			ImGui_ImplWin32_Init(FindWindowA(0, "Team Fortress 2"));
			ImGui_ImplDX9_Init(pDevice);
			bInitImGui = true;
		}
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		m_bOpen = !m_bOpen;

	if (m_bOpen)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Material Editor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
		{
			//Init the Window
			{
				static bool bInitWindow = false;

				if (!bInitWindow) {
					ImGui::SetWindowPos(ImVec2(static_cast<float>(400), static_cast<float>(200)));
					ImGui::SetWindowSize(ImVec2(static_cast<float>(600), static_cast<float>(500)));
					bInitWindow = true;
				}
			}



			ImGui::End();
		}

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
}