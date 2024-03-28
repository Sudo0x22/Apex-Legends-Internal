#pragma once
#include"../detours/detours.hpp"
class Core
{
public:
	__inline void Initialize()
	{
		pOffsets.Initialize();
		pNetVars.Initialize();
		pButtons.Initialize();
		pHooks.Initialize();
	}
}; inline Core pCore;