#pragma once
#include"../../incs/structs.hpp"
#include"../../../utils/vfunc/vfunc.hpp"
#include<Windows.h>

class BaseClientDll
{
public:
	ClientClass_t* GetAllClasses()
	{
		typedef ClientClass_t* (__thiscall* Fn)(PVOID);
		return pFunc.GetVirtualFunction<Fn>(this, 12)(this);
	}
};