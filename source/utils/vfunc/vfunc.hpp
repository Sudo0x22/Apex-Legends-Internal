#pragma once
#include<cstdint>
class VFunc
{
public:
	__inline void**& GetVirtualTable(void* ptr, size_t offset = 0) {
		return *reinterpret_cast<void***>(reinterpret_cast<size_t>(ptr) + offset);
	}
	__inline const void** GetVirtualTable(const void* ptr, size_t offset = 0) {
		return *reinterpret_cast<const void***>(reinterpret_cast<size_t>(ptr) + offset);
	}
public:
	template<typename Type>
	__inline Type GetVirtualFunction(void* ptr, size_t index, size_t offset = 0) {
		return reinterpret_cast<Type>(GetVirtualTable(ptr, offset)[index]);
	}
	template<typename Type>
	__inline Type GetVirtualFunction(const void* ptr, size_t index, size_t offset = 0) {
		return reinterpret_cast<Type>(GetVirtualFunction(ptr, offset)[index]);
	}
public:
	__inline uintptr_t GetVirtualFunctionPtr(void* ptr, unsigned int index) {
		return static_cast<uintptr_t>((*static_cast<int**>(ptr))[index]);
	}
}; inline VFunc pFunc;