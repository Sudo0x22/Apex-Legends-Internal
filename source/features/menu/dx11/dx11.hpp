#pragma once
#include<d3d11.h>
#include<dxgi.h>
#include"../../../utils/utils.hpp"
#include"../../../hooking/hooking.hpp"
typedef HRESULT(__stdcall* Present_t)(void*, UINT, UINT);
typedef LRESULT(__stdcall* WndProc_t)(HWND, UINT, WPARAM, LPARAM);
typedef HRESULT(__stdcall* Resize_t)(void*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
typedef BOOL(__stdcall* Cursor_t)(bool);
class D3D11 {
public:
	Present_t oPresent = 0;
	WndProc_t oWndProc = 0;
	Resize_t oResize = 0;
	Cursor_t oCursor = 0;
public:
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
public:
	HWND hWindow = 0;
	HWND WindowHandle = 0;
	WNDCLASSEX WindowClass;
}; inline D3D11 pD3D11;
class DX11 {
public:
	__inline bool InitWindow()
	{
		pD3D11.WindowClass.cbSize = sizeof(WNDCLASSEX);
		pD3D11.WindowClass.lpfnWndProc = DefWindowProc;
		pD3D11.WindowClass.hInstance = GetImage<HMODULE>(L"");
		pD3D11.WindowClass.lpszClassName = L"Sync";
		pD3D11.WindowClass.hCursor = 0;
		pD3D11.WindowClass.cbClsExtra = NULL;
		pD3D11.WindowClass.cbWndExtra = NULL;
		pWinApi.MyRtlRegisterWndClass(&pD3D11.WindowClass);
		pD3D11.WindowHandle = pWinApi.MyRtlCreateWindow(NULL, pD3D11.WindowClass.lpszClassName, L"Apex", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, pD3D11.WindowClass.hInstance, NULL);
		if (pD3D11.WindowHandle == NULL) return false;
		return true;
	}
	__inline bool DeleteWindow()
	{
		pWinApi.MyRtlDestroyWindow(pD3D11.WindowHandle);
		pWinApi.MyRtlUnregisterWndClass(pD3D11.WindowClass.lpszClassName, pD3D11.WindowClass.hInstance);
		if (pD3D11.WindowHandle != NULL) return false;
		return true;
	}
	__inline bool Initialize()
	{
		if (InitWindow() == false) { DeleteWindow(); return false; }
		auto hModule = GetImage<uintptr_t>(xorstr_(L"d3d11.dll"));
		auto D3D11CreateDeviceSwapChain = GetImageExport(hModule, xorstr_("D3D11CreateDeviceAndSwapChain"));

		if (!hModule) { MessageBoxA(NULL, "Error", "Module", NULL); }
		if (!D3D11CreateDeviceSwapChain) { MessageBoxA(NULL, "Error", "Error", NULL); }

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = pD3D11.WindowHandle;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* context;

		if (((long(__stdcall*)(
			IDXGIAdapter*,
			D3D_DRIVER_TYPE,
			HMODULE,
			UINT,
			const D3D_FEATURE_LEVEL*,
			UINT,
			UINT,
			const DXGI_SWAP_CHAIN_DESC*,
			IDXGISwapChain**,
			ID3D11Device**,
			D3D_FEATURE_LEVEL*,
			ID3D11DeviceContext**))(D3D11CreateDeviceSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context) < 0)
		{
			DeleteWindow();
			return false;
		}

		MethodsTable = (uint64_t*)::_calloc(205, sizeof(uint64_t));
		_memcpy(MethodsTable, *(uint64_t**)swapChain, 18 * sizeof(uint64_t));
		_memcpy(MethodsTable + 18, *(uint64_t**)device, 43 * sizeof(uint64_t));
		_memcpy(MethodsTable + 18 + 43, *(uint64_t**)context, 144 * sizeof(uint64_t));
		
		Hook::SpoofHook spHook;
		spHook.Initialize();
		swapChain->Release();
		swapChain = NULL;
		device->Release();
		device = NULL;
		context->Release();
		context = NULL;
		DeleteWindow();
		return true;
	}
}; inline DX11 pDX11;