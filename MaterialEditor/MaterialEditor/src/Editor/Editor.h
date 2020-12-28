#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

class CEditor
{
private:
	bool m_bOpen;

public:
	bool IsOpen();
	void Render(IDirect3DDevice9 *pDevice);
};

inline CEditor g_Editor;