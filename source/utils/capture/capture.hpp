#pragma once
#include"../winapi/winapi.hpp"

class Capture
{
public:
	typedef void* (*Interface)();
	struct Interface_t
	{

	};
public:
	template<typename Type>
	__inline Type CaptureInterface(LPCSTR szModule, PCCH szObject)
	{
		Type buffer = {};
		if (const auto hModule = GetImage<HMODULE>(szModule))
		{

		}
		return buffer;
	}
};