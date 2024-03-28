#pragma once
#include<cstdint>
#include"crt.hpp"
#include"xorstr.hpp"
#include"../../../includes/spoofer/spoofer.hpp"
#pragma section(".text")
__declspec(allocate(".text")) unsigned const char JmpRbx[] = { 0xff, 0x23 };
typedef struct SysMem
{
	DWORD64 dwEP;
	LPVOID dwParam;
} SysMem, * pSysMem;
typedef DWORD(*InitMem)(LPVOID Param);
 void* _memcpy(void* p, const void* d, size_t size)
{
	return spoof_call_ex(JmpRbx, memcpy, p, d, size);
}
 void* _memset(void* p, int d, size_t size)
{
	return spoof_call_ex(JmpRbx, memset, p, d, size);
}
 void* __cdecl _calloc(size_t count, size_t size)
{
	return spoof_call_ex(JmpRbx, calloc, count, size);
}
 wchar_t* _wcscpy(wchar_t* dest, const wchar_t* source) {
	return spoof_call_ex(JmpRbx, wcscpy, dest, source);
}
class WinApi
{
public:
	typedef __int64(__stdcall* _RtlGetAsyncKeyState)(int);
	typedef BOOL(__stdcall* _RtlDestroyWindow)(HWND);
	typedef ATOM(__stdcall* _RtlRegisterWndClass)(const WNDCLASSEX*);
	typedef ATOM(__stdcall* _RtlUnRegisterWndClass)(LPCWSTR, HINSTANCE);
	typedef HWND(__stdcall* _RtlCreateWindow)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
	typedef LRESULT(__stdcall* _RtlCallWindowProc)(WNDPROC, HWND, UINT, WPARAM, LPARAM);
	typedef int(__stdcall* _RtlGetSystemMetrics)(int);
	typedef int(__stdcall* _RtlMultiByteToWideChar)(UINT, DWORD, LPCCH, int, LPWSTR, int);
	typedef int(__stdcall* _RtlWideCharToMultiByte)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL);
	typedef LONG_PTR(__stdcall* _RtlSetWindowLongPtr)(HWND, int, LONG_PTR);
	typedef BOOL(__stdcall* _RtlSetCursorPos)(int, int);
	typedef BOOL(__stdcall* _RtlVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
	typedef LPVOID(__stdcall* _RtlVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
	typedef HANDLE(__stdcall* _RtlCreateThread)(HANDLE, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
	typedef HANDLE(__stdcall* _RtlCurrentProces)();
	typedef BOOL(__stdcall* _RtlCloseHandle)(HANDLE);
	typedef void(__stdcall* _RtlSleep)(DWORD);
	typedef HANDLE(__stdcall* _RtlCreateFile)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
	typedef BOOL(__stdcall* _RtlDeviceIoControl)(HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
public:
	HANDLE __stdcall MyRtlCreateFileW(LPCWSTR name, DWORD flags, DWORD protect, LPSECURITY_ATTRIBUTES attr, DWORD old, DWORD oldold, HANDLE handle)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlCreateFile RtlCreateFile = (_RtlCreateFile)(GetImageExport(hModule, xorstr_("CreateFileW")));
		return RtlCreateFile(name, flags, protect, attr, old, oldold, handle);
	}
	BOOL __stdcall MyRtlDeviceIoControl(HANDLE driver, DWORD first, LPVOID second, DWORD third, LPVOID fourth, DWORD five, LPDWORD thread, LPOVERLAPPED over)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"kernel32.dll"));
		_RtlDeviceIoControl Rtl = (_RtlDeviceIoControl)(GetImageExport(hModule, xorstr_("DeviceIoControl")));
		return Rtl(driver, first, second, third, fourth, five, thread, over);
	}
	LONG_PTR __stdcall MyRtlSetWindowLongPtr(HWND hWindow, int index, LONG_PTR ptr)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlSetWindowLongPtr RtlSetLong = (_RtlSetWindowLongPtr)(GetImageExport(hModule, xorstr_("SetWindowLongPtrW")));
		return RtlSetLong(hWindow, index, ptr);
	}
	BOOL __stdcall MyRtlCloseHandle(HANDLE handle)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"kernel32.dll"));
		_RtlCloseHandle Rtl = (_RtlCloseHandle)(GetImageExport(hModule, xorstr_("CloseHandle")));
		return Rtl(handle);
	}
	HANDLE __stdcall MyRtlCurrentProcess()
	{
		auto hModule = GetImage<uintptr_t>(L"kernel32.dll");
		_RtlCurrentProces Rtl = (_RtlCurrentProces)(GetImageExport(hModule, "GetCurrentProcess"));
		return Rtl();
	}
	HANDLE __stdcall MyRtlCreateThread(HANDLE Proc, LPSECURITY_ATTRIBUTES Attr, SIZE_T Size, LPTHREAD_START_ROUTINE Routine, LPVOID Buffer, DWORD Flags, LPDWORD ThreadId)
	{
		auto hModule = GetImage<uintptr_t>(L"kernel32.dll");
		_RtlCreateThread Rtl = (_RtlCreateThread)(GetImageExport(hModule, "CreateRemoteThread"));
		return Rtl(Proc, Attr, Size, Routine, Buffer, Flags, ThreadId);
	}
	BOOL __stdcall MyRtlVirtualProtect(LPVOID addr, SIZE_T size, DWORD newProtect, PDWORD oldProtect) 
	{
		auto hModule = GetImage<uintptr_t>(L"kernel32.dll");
		_RtlVirtualProtect Rtl = (_RtlVirtualProtect)(GetImageExport(hModule, "VirtualProtect"));
		return Rtl(addr, size, newProtect, oldProtect);
	}
	LPVOID __stdcall MyRtlVirtualAlloc(LPVOID addr, SIZE_T size, DWORD alloc, DWORD protect)
	{
		auto hModule = GetImage<uintptr_t>(L"kernel32.dll");
		_RtlVirtualAlloc Rtl = (_RtlVirtualAlloc)(GetImageExport(hModule, "VirtualAlloc"));
		return Rtl(addr, size, alloc, protect);
	}
public:
	int __stdcall MyRtlMultiByteToWideChar(UINT uInt, DWORD oWord, LPCCH oP, int oInt, LPWSTR oPc, int oWorld)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"kernel32.dll"));
		_RtlMultiByteToWideChar RltMultiByte = (_RtlMultiByteToWideChar)(GetImageExport(hModule, xorstr_("MultiByteToWideChar")));
		return RltMultiByte(uInt, oWord, oP, oInt, oPc, oWorld);
	}
	int __stdcall MyRtlWideToMultiByteChar(UINT oInt, DWORD oWord, LPCWCH oPc, int o, LPSTR oT, int oN, LPCCH oA, LPBOOL oB)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"kernel32.dll"));
		_RtlWideCharToMultiByte Rtl = (_RtlWideCharToMultiByte)
			(GetImageExport(hModule, xorstr_("WideCharToMultiByte")));
		return Rtl(oInt, oWord, oPc, o, oT, oN, oA, oB);
	}
	int __stdcall MyRtlGetSystemMetrics(int index)
	{
		auto hModule = GetImage<uintptr_t>(L"user32.dll");
		_RtlGetSystemMetrics RtlGetSystemMetrics = (_RtlGetSystemMetrics)
			(GetImageExport(hModule, "GetSystemMetrics"));
		return RtlGetSystemMetrics(index);
	}
	__int64 __stdcall MyRtlGetAsyncKeyState(int code)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlGetAsyncKeyState RtlGetAsyncKeyState = (_RtlGetAsyncKeyState)
			(GetImageExport(hModule, xorstr_("GetAsyncKeyState")));
		return RtlGetAsyncKeyState(code);
	}
	__inline LRESULT __stdcall MyRtlCallWndProc(WNDPROC oWnd, HWND oHwnd, UINT oInt, WPARAM oParam, LPARAM oLaram)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlCallWindowProc RtlCallWndProc = (_RtlCallWindowProc)
			(GetImageExport(hModule, xorstr_("CallWindowProcW")));
		return RtlCallWndProc(oWnd, oHwnd, oInt, oParam, oLaram);
	}
	__inline HWND MyRtlCreateWindow(DWORD oExit, LPCWSTR oClass, LPCWSTR oName, DWORD oStyle, int x, int y, int w, int h, HWND oWnd, HMENU oMenu, HINSTANCE oInst, LPVOID oParam)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlCreateWindow RtlCreateWindow = (_RtlCreateWindow)
			(GetImageExport(hModule, xorstr_("CreateWindowExW")));
		return RtlCreateWindow(oExit, oClass, oName, oStyle, x, y, w, h, oWnd, oMenu, oInst, oParam);
	}
	__inline BOOL MyRtlDestroyWindow(HWND hWindow)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlDestroyWindow RtlDestroyWindow = (_RtlDestroyWindow)
			(GetImageExport(hModule, xorstr_("DestroyWindow")));
		return RtlDestroyWindow(hWindow);
	}
	__inline ATOM MyRtlRegisterWndClass(const WNDCLASSEX* oWndClass)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlRegisterWndClass RtlRegisterWndClass = (_RtlRegisterWndClass)
			(GetImageExport(hModule, xorstr_("RegisterClassExW")));
		return RtlRegisterWndClass(oWndClass);
	}
	__inline ATOM MyRtlUnregisterWndClass(LPCWSTR oClass, HINSTANCE oInst)
	{
		auto hModule = GetImage<uintptr_t>(xorstr_(L"user32.dll"));
		_RtlUnRegisterWndClass RtlUnregisterWndClass = (_RtlUnRegisterWndClass)
			(GetImageExport(hModule, xorstr_("UnregisterClassW")));
		return RtlUnregisterWndClass(oClass, oInst);
	}
}; inline WinApi pWinApi;