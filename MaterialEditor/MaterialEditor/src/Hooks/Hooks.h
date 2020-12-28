#pragma once
#include "DrawModelExecute/DrawModelExecute.h"
#include "EndScene/EndScene.h"
#include "Reset/Reset.h"
#include "WndProc/WndProc.h"

class CHooks
{
public:
	void Init();
	void Exit();
};

inline CHooks g_Hooks;