#include "WndProc.h"
#include "../../Editor/Editor.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LONG __stdcall Hooks::WndProc::Func(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (g_Editor.IsOpen()) {
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		g_pInputSystem->ResetInputState();
		return 1;
	}
	
	return CallWindowProc(Original, hWnd, uMsg, wParam, lParam);
}

void Hooks::WndProc::Init()
{
	while (!hwWindow)
		hwWindow = FindWindowW(0, L"Team Fortress 2");

	Original = (WNDPROC)SetWindowLongPtr(hwWindow, GWL_WNDPROC, (LONG_PTR)Func);
}