#pragma once
#include"../wndproc/wndproc.h"
namespace Detours {
	namespace Present {
		constexpr uint16_t pIndex = 8;
		HRESULT __stdcall Detour(IDXGISwapChain* pSwapChain, UINT uInt, UINT uFlags) 
		{
			if (!pMenu.InitImGui) 
			{
				if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (LPVOID*)&pD3D11.pDevice))) 
				{
					ImGui::CreateContext();

					pD3D11.pDevice->GetImmediateContext(&pD3D11.pContext);
					DXGI_SWAP_CHAIN_DESC desc;

					pSwapChain->GetDesc(&desc);
					pD3D11.hWindow = desc.OutputWindow;

					ID3D11Texture2D* pBackBuffer;
					pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

					D3D11_RENDER_TARGET_VIEW_DESC RenderTarget = {};
					_memset(&RenderTarget, 0, sizeof(RenderTarget));

					RenderTarget.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					RenderTarget.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

					pD3D11.pDevice->CreateRenderTargetView(pBackBuffer, &RenderTarget, &pD3D11.pRenderTargetView);
					pBackBuffer->Release();

					ImGui::GetIO().ImeWindowHandle = pD3D11.hWindow;
					ImGui_ImplDX11_CreateDeviceObjects();

					pD3D11.oWndProc = (WndProc_t)pWinApi.MyRtlSetWindowLongPtr(pD3D11.hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc::Detour);
					pMenu.Initialize();
					pMenu.Style();
					pMenu.InitImGui = true;
				}
				else
					return pD3D11.oPresent(pSwapChain, uInt, uFlags);
			}
			ImGui_ImplWin32_NewFrame();
			ImGui_ImplDX11_NewFrame();
			ImGui::NewFrame();
			pMenu.Run();
			pAimbot.Run();
			pVisuals.Run();
			pMisc.Run();
			ImGui::EndFrame();
			ImGui::Render();
			pD3D11.pContext->OMSetRenderTargets(1, &pD3D11.pRenderTargetView, NULL);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			return pD3D11.oPresent(pSwapChain, uInt, uFlags);
		}
	}

	namespace Resize {
		constexpr uint16_t pIndex = 13;
		HRESULT __stdcall Detour(IDXGISwapChain* pSwapChain, UINT uInt, UINT width, UINT height, DXGI_FORMAT format, UINT oInt) {
			ImGui_ImplDX11_Shutdown();
			pSwapChain->Release();
			pD3D11.pRenderTargetView->Release();
			pD3D11.pContext->Release();
			pD3D11.pDevice->Release();
			pD3D11.pDevice = NULL;
			return pD3D11.oResize(pSwapChain, uInt, width, height, format, oInt);
		}
	}
}