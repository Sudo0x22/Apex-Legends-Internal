#pragma once
#include<cassert>
#include<cstdint>
#include<memory>
#include"../../includes/minhook/include/MinHook.h"
#include"../utils/utils.hpp"
static uint64_t* MethodsTable = nullptr;
namespace Hook
{
	class SpoofHook {
	public:
		__inline MH_STATUS Initialize() { return spoof_call_ex(JmpRbx, MH_Initialize); }
		__inline MH_STATUS CreateHook(void* pTarget, void* pDetour, void** pOriginal) { return spoof_call_ex(JmpRbx, MH_CreateHook, pTarget, pDetour, pOriginal); }
		__inline MH_STATUS EnableHook(void* pTarget) { return spoof_call_ex(JmpRbx, MH_EnableHook, pTarget); }
		__inline MH_STATUS DisableHook(void* pTarget) { return spoof_call_ex(JmpRbx, MH_DisableHook, pTarget); }
		__inline MH_STATUS RemoveHook(void* pTarget) { return spoof_call_ex(JmpRbx, MH_RemoveHook, pTarget); }
	};
	class Hooking :public SpoofHook {
	public:
		__inline bool Hook(uint16_t pIndex, void* pDetour, void** pOriginal) {
			assert(pIndex >= 0 && pDetour != NULL && pOriginal != NULL);
			void* pTarget = (void*)MethodsTable[pIndex];
			if (this->CreateHook(pTarget, pDetour, pOriginal) != MH_OK || this->EnableHook(pTarget) != MH_OK) return false;
			return true;
		}
		__inline bool RemoveHook(uint16_t pIndex);
	};
	class Function  : public SpoofHook {
	private:
		void* pOriginal = nullptr;
	public:
		__inline bool Hook(void* pTarget, void* pDetour) {
			return (this->CreateHook(pTarget, pDetour, &pOriginal) == MH_OK);
		}
		template<typename type>
		__inline type Original() const {
			return reinterpret_cast<type>(pOriginal);
		}
	};
	class Table :public SpoofHook {
	private:
		unsigned int** pBase = 0u;
		unsigned int   pSize = 0u;
		std::unique_ptr<void* []> pOriginal = nullptr;
	public:
		__inline bool Initialize(void* pTarget)
		{
			pBase = (unsigned int**)(pTarget);
			while (reinterpret_cast<unsigned int*>(*pBase)[pSize])
				pSize += 1u;
			pOriginal = std::make_unique<void* []>(pSize);
			return (pBase && pSize);
		}
		__inline bool Hook(unsigned int index, void* pDetour)
		{
			if (pBase && pSize)
				return (CreateHook((*reinterpret_cast<void***>(pBase))[pSize], pDetour, &pOriginal[index]) == MH_STATUS::MH_OK);

		}
		template<typename type>
		__inline type Original(unsigned int index) const {
			return reinterpret_cast<type>(pOriginal[index]);
		}
	};
}