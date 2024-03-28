#pragma once
#include"present/present.hpp"
class Hooks
{
public:
	__inline bool Initialize()
	{
		if (pDX11.Initialize() == false) return false;

		Hook::Hooking Hook;
		Hook.Hook(8, Detours::Present::Detour, (void**)&pD3D11.oPresent);
		Hook.Hook(13, Detours::Resize::Detour, (void**)&pD3D11.oResize);

		return true;
	}
}; inline Hooks pHooks;