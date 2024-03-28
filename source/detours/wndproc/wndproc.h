#pragma once
#include"../../features/menu/menu.hpp"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
namespace WndProc
{
	LRESULT __stdcall Detour(HWND hWindow, UINT uInt, WPARAM wParam, LPARAM lParam)
	{
		if (pMenu.RenderMenu) { ImGui_ImplWin32_WndProcHandler(hWindow, uInt, wParam, lParam);  return TRUE; }
		return pWinApi.MyRtlCallWndProc(pD3D11.oWndProc, hWindow, uInt, wParam, lParam);
	}
}