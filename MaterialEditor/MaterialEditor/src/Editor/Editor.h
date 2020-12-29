#pragma once
#include "TextEditor/TextEditor.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"
#include "../SDK/SDK.h"

class CMaterial
{
public:
	std::string m_sName;
	TextEditor m_Text;
	bool m_bOpen;
};

class CEditor
{
private:
	bool m_bOpen = false;
	bool m_bUnload = false;
	IMaterial *m_pMaterial = nullptr;
	IMaterial *CreateMaterial(const char *szInput);

private:
	std::vector<CMaterial> m_vecMaterials;

public:
	bool IsOpen();
	bool IsUnloading();
	IMaterial *GetLoadedMaterial();
	void Render(IDirect3DDevice9 *pDevice);
};

inline CEditor g_Editor;