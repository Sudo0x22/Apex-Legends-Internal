#pragma once
#include"../winapi/winapi.hpp"

class Capture
{
public:
	template<typename Type>
	__inline Type CaptureInterface(const wchar_t* szModule, char* szObject)
	{
		auto hModule = GetImage<uintptr_t>(szModule);
		if (!hModule) return nullptr;
		auto hFunction = reinterpret_cast<void*(__cdecl)(const char*, int*)>(GetImageExport(hModule, "CreateInterface"));
		if (!hFunction) return nullptr;
		return reinterpret_cast<Type>(hFunction(szObject, nullptr));
	}
};
