#pragma once
#include"../winapi/winapi.hpp"
#include <vector>
#define INRANGE(x,a,b)	(x >= a && x <= b)
#define GetBits(x)		(INRANGE((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetBytes(x)		(GetBits(x[0]) << 4 | GetBits(x[1]))

class Pattern
{
public:
	uintptr_t Find(const wchar_t* szModule, const wchar_t* szPattern)
	{
		if (const auto dwMod = GetImage<uintptr_t>(szModule))
		{
			if (const auto& ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS64>(dwMod + reinterpret_cast<PIMAGE_DOS_HEADER>(dwMod)->e_lfanew))
				return FindPattern(dwMod + ntHeaders->OptionalHeader.BaseOfCode, dwMod + ntHeaders->OptionalHeader.SizeOfCode, szPattern);
		}
	}
private:
	uintptr_t FindPattern(uintptr_t addr, uintptr_t len, const wchar_t* szPattern)
	{
        auto  szPatt = szPattern;
        uintptr_t dwFirstMatch = 0x0;

        uintptr_t dwCur;
        for (dwCur = addr; dwCur < len; dwCur++)
        {
            if (!szPatt)
                return dwFirstMatch;

            const auto& pCurByte = *(BYTE*)dwCur;
            const auto& pBytePatt = *(BYTE*)szPatt;

            if (pBytePatt == '\?' || pCurByte == GetBytes(szPatt))
            {
                if (!dwFirstMatch)
                    dwFirstMatch = dwCur;

                if (!szPatt[2])
                    return dwFirstMatch;

                szPatt += (pBytePatt == '\?\?' || pBytePatt != '\?') ? 3 : 2;
            }
            else
            {
                szPatt = szPattern;
                dwFirstMatch = 0x0;
            }
        }

        return 0x0;
	}
}; inline Pattern pPattern;

class Scanner
{
public:
    uintptr_t find_pattern(uintptr_t module_base, const char* signature)
    {
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);
			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
			};

		auto dosHeader = (PIMAGE_DOS_HEADER)module_base;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)module_base + dosHeader->e_lfanew);

		auto size_of_image = ntHeaders->OptionalHeader.SizeOfImage;
		auto pattern_bytes = pattern_to_byte(signature);
		auto module_bytes = reinterpret_cast<uint8_t*>(module_base);

		auto s = pattern_bytes.size();
		auto d = pattern_bytes.data();
		auto CurrentSig = 0;
		int TimesFound = 0;
		for (auto i = 0ul; i < size_of_image - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (module_bytes[i + j] != d[j] && d[j] != -1) {
					found = false; // if not found keep scanning
					break;
				}
			}
			if (found) {


				return (uintptr_t)&module_bytes[i];
			}
		}
		return NULL;
    }
}; inline Scanner pScanner;