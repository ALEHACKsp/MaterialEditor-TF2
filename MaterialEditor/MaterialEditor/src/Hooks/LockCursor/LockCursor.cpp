#include "LockCursor.h"
#include "../../Editor/Editor.h"

void __stdcall Hooks::LockCursor::Func()
{
	g_Editor.IsOpen() ? g_pSurface->UnlockCursor() : Hook.CallOriginal<fn>()(g_pSurface);
}

void Hooks::LockCursor::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(g_pSurface, 62));
	Hook.Create(reinterpret_cast<void *>(FN), reinterpret_cast<void *>(Func));
}