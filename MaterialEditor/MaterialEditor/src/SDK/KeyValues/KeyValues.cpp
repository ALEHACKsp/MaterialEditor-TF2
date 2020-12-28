#include "KeyValues.h"
#include "../../Utils/Pattern/Pattern.h"

bool CKeyValues::LoadFromBuffer(char const *resource_name, const char *buffer, void *file_system, const char *path_id)
{
	using fn = int(__thiscall *)(CKeyValues *, char const *, const char *, void *, const char *);
	static fn FN = reinterpret_cast<fn>(g_Pattern.Find(L"engine.dll", L"55 8B EC 83 EC 38 53 8B 5D 0C"));
	return FN(this, resource_name, buffer, file_system, path_id);
}

void CKeyValues::Initialize(char *name)
{
	using fn = CKeyValues *(__thiscall *)(CKeyValues *, char *);
	static fn FN = reinterpret_cast<fn>(g_Pattern.Find(L"engine.dll", L"FF 15 ? ? ? ? 83 C4 08 89 06 8B C6") - 0x42);
	FN(this, name);
}