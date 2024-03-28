#pragma once
#include"../winapi/winapi.hpp"

#define ioctl_read_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x093286, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_write_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x729823, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_get_module_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x461419, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_protect_virutal_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x433146, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_allocate_virtual_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x523794, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

class Driver
{
public:
	HANDLE driver_handle;
	int target_module_base;
public:
    bool IsDriverRunning(const wchar_t* driver_name)
    {
        driver_handle = pWinApi.MyRtlCreateFileW(driver_name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        if (driver_handle == INVALID_HANDLE_VALUE) return false;
        //pWinApi.MyRtlCloseHandle(driver_handle);
        return true;
    }
    uintptr_t get_base_addr(const wchar_t* module_name)
    {
        if (!driver_handle) return 0;
        k_get_base_module_request request;
        request.pid = GetImage<uintptr_t>(L"r5apex.exe");
        _memset(request.name, 0, sizeof(WCHAR) * 260);
        _wcscpy(request.name, module_name);
        pWinApi.MyRtlDeviceIoControl(driver_handle, ioctl_get_module_base, &request, sizeof(k_get_base_module_request), &request, sizeof(k_get_base_module_request), 0, 0);
        return request.handle;
    }
private:
    typedef struct _k_get_base_module_request {
        ULONG pid;
        ULONGLONG handle;
        WCHAR name[260];
    } k_get_base_module_request, * pk_get_base_module_request;

    typedef struct _k_rw_request {
        ULONG pid;
        ULONGLONG src;
        ULONGLONG dst;
        ULONGLONG size;
    } k_rw_request, * pk_rw_request;

    typedef struct _k_alloc_mem_request {
        ULONG pid, allocation_type, protect;
        PVOID addr;
        SIZE_T size;
    } k_alloc_mem_request, * pk_alloc_mem_request;

    typedef struct _k_protect_mem_request {
        ULONG pid, protect;
        ULONGLONG addr;
        SIZE_T size;
    } k_protect_mem_request, * pk_protect_mem_request;

}; Driver pDriver;