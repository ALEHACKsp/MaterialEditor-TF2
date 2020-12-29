#pragma once
#include "TextEditor/TextEditor.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

class CMaterial
{
public:
	std::string m_sName;
	std::string m_sVars;
	TextEditor m_Text;
};

class CEditor
{
private:
	bool m_bOpen = false;

private:
	std::vector<CMaterial> m_vecMaterials;

public:
	bool IsOpen();
	void Render(IDirect3DDevice9 *pDevice);
};

inline CEditor g_Editor;