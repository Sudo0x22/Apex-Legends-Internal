#pragma once
#include"../driver/driver.hpp"
class GetProc
{
public:
	int get_proc_id(const wchar_t* process_name)
	{
		return 0;
	}
};
class Globals : public GetProc
{
public:
	int target_proc_addr = 0;
public:
	__inline bool Initialize()
	{
		target_proc_addr = get_proc_id(L"r5apex.exe");
		return true;
	}
}; inline Globals pGlobals;