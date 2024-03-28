#pragma once
#include<string>
#include"tabs/tabs.hpp"
#include"dx11/dx11.hpp"
#include"../visuals/visuals.hpp"
#include"../misc/Misc.hpp"
#include"image/image.hpp"
#include <D3DX11tex.h>
#include"../../detours/cursor/cursor.hpp"
#pragma comment(lib, "D3DX11.lib")
using namespace Components;
ID3D11ShaderResourceView* Image = nullptr;
class CSnow
{
public:
	__inline void DrawSnow(int x, int y)
	{
		struct SnowFlake_t { int X, Y; };
		static std::vector<SnowFlake_t> vSnowFlakes;
		constexpr int snowCount = 150;
		static bool bInit = false;
		while (!bInit) { for (int index = 0; index < snowCount; index++) { vSnowFlakes.emplace_back(utils::RandIntSimple(0, x), utils::RandIntSimple(0, y / 2.f)); } bInit = true; }
		for (auto& flake : vSnowFlakes)
		{
			constexpr int drift = 1;
			flake.X += utils::RandIntSimple(-drift, drift);
			flake.Y += drift;
			const float alpha = utils::MapFloat(flake.Y, 0.0f, y / 2.f, 0.5f, 0.0f);
			if (alpha <= 0.f || flake.X >= x || flake.X <= 0) { flake.X = utils::RandIntSimple(0, x); flake.Y = utils::RandIntSimple(0, 150); }
			pDraw.ApexDrawText(flake.X, flake.Y, &pColor.White, "*");
		}
	}
};
class CMenu : public CSnow
{
private:
	std::string szMenuTitle = "smokehook";
	int MenuWidth = 795;
	int MenuHeight = 465;
public:
	bool RenderMenu = false;
	bool InitImGui = false;
	bool CaptureCursor = false;
	bool RenderCursor = false;
private:
	bool close_button = false;
	unsigned long window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	enum class MenuTabs
	{
		Aimbot,
		Visuals,
		Misc,
		Configs
	};
	ImFont* TitleFont = nullptr;
	ImFont* IconFont = nullptr;
	ImFont* gameFont = nullptr;
	ImFont* VerdanaSmall = nullptr;
public:
	__inline void Style()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::StyleColorsDark();

		style.WindowRounding = 4;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.GrabRounding = 3;
		style.TabRounding = 3;
		style.ScrollbarRounding = 3;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.FramePadding = { 6.0f, 6.0f };
		style.ItemSpacing = { 9.0f, 9.0f };
		style.WindowPadding = { 9.0f, 9.0f };
		style.ItemInnerSpacing = { 8.0f, 4.0f };
		style.WindowBorderSize = 1;
		style.FrameBorderSize = 1;
		style.ScrollbarSize = 12.f;
		style.GrabMinSize = 8.f;

		style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
		style.Colors[ImGuiCol_Border] = ImColor(13, 47, 90, 255);
		style.Colors[ImGuiCol_TitleBg] = ImColor(15, 15, 15, 255);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(15, 15, 15, 255);

		style.Colors[ImGuiCol_ButtonActive] = ImColor(13, 47, 90, 255);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(13, 47, 90, 255);

		style.Colors[ImGuiCol_Separator] = ImColor(13, 47, 90, 255);
		style.Colors[ImGuiCol_SeparatorActive] = ImColor(13, 47, 90, 255);
		style.Colors[ImGuiCol_SeparatorHovered] = ImColor(13, 47, 90, 255);

		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);

		style.Colors[ImGuiCol_FrameBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = Hex(0x111111, 0.9f);
		style.Colors[ImGuiCol_FrameBgActive] = Hex(0x111111, 0.8f);

		style.Colors[ImGuiCol_SliderGrab] = ImColor(13, 47, 90, 255);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(13, 47, 90, 255);
		
		pFonts.Initialize();

	}
	__inline void Initialize()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		
		D3DX11_IMAGE_LOAD_INFO info;
		ID3DX11ThreadPump* pump{ nullptr };

		D3DX11CreateShaderResourceViewFromMemory(pD3D11.pDevice, rawData, sizeof(rawData), &info, pump, &Image, 0);

		ImGui_ImplWin32_Init(pD3D11.hWindow);
		ImGui_ImplDX11_Init(pD3D11.pDevice, pD3D11.pContext);
	}
	std::string add_strings(std::string icon, std::string str) { return icon + str; }
	__inline void Tabs()
	{
		int height = 40;
		int width = 100;

		pImGuiFeatures->Columns(2);
		pImGuiFeatures->SetColumns(1, width + 30);
		
		static MenuTabs Tab = MenuTabs::Aimbot;
		{
			static ImVec4 InActive = ImVec4(0.09f, 0.09, 0.09f, 0.88f);
			static ImVec4 Active = ImVec4(0.0f, 0.5f, 0.5f, 0.9f);
			static ImVec4 NewActive = ImColor(13, 47, 90, 255).Value;

			ImGui::SetCursorPosX(5);
			ImGui::Image((LPVOID)Image, ImVec2(135, 170));

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::PushFont(pFonts.IconFont);

			ImGui::PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Aimbot ? NewActive : InActive);
			if (ImGui::Button(add_strings(ICON_MD_SCORE, " Aimbot").c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Aimbot;

			ImGui::PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Visuals ? NewActive : InActive);
			if (ImGui::Button(add_strings(ICON_MD_BRUSH, " Visuals").c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Visuals;

			ImGui::PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Misc ? NewActive : InActive);
			if (ImGui::Button(add_strings(ICON_MD_MISCELLANEOUS_SERVICES, " Misc  ").c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Misc;

			ImGui::PopFont();
			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar(1);
		}
		pImGuiFeatures->NextColumns();
		{
			switch (Tab)
			{
			case MenuTabs::Aimbot:
				pTabs.aimbot_tab();
				break;
			case MenuTabs::Visuals:
				pTabs.visuals_tab();
				break;
			case MenuTabs::Misc:
				pTabs.misc_tab();
				break;
			case MenuTabs::Configs:
				break;
			}
		}
	}
	__inline void Render() 
	{
		ImGui::Begin(szMenuTitle.c_str(), &close_button, window_flags);
		ImGui::SetWindowSize(ImVec2(MenuWidth, MenuHeight));
		this->Tabs();
		ImGui::End();
	}
	__inline void Run()
	{
		if (pWinApi.MyRtlGetAsyncKeyState(VK_INSERT) & 0x1) { RenderMenu = !RenderMenu; }
		if (RenderMenu) { this->Render(); }
		if (Vars::Aimbot::draw_fov)
		{
			pDraw.DrawCircle(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2, Vars::Aimbot::aim_fov, ImColor(13, 47, 90, 255));
		}
	}
}; inline CMenu pMenu;
