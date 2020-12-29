#include "Hooks.h"

void CHooks::Init()
{
	MH_Initialize();
	{
		Hooks::DrawModelExecute::Init();
		Hooks::EndScene::Init();
		Hooks::Reset::Init();
		Hooks::WndProc::Init();
		Hooks::LockCursor::Init();
	}
	MH_EnableHook(MH_ALL_HOOKS);
}

void CHooks::Exit()
{
	MH_Uninitialize();
	SetWindowLongPtr(Hooks::WndProc::hwWindow, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc::Original);
}