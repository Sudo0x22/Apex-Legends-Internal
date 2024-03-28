#pragma once
#include"../extra/extra.hpp"
#include "../fonts/icons_data.hpp"
#include"../../vars/vars.hpp"

class Fonts
{
public:
	ImFont* TitleFont = nullptr;
	ImFont* IconFont = nullptr;
	ImFont* gameFont = nullptr;
	ImFont* VerdanaSmall = nullptr;
public:
	__inline void Initialize()
	{
		{
			const auto& io = ImGui::GetIO();
			auto fontConfig = ImFontConfig();
			fontConfig.OversampleH = 2;
			constexpr ImWchar fontRange[]{ 0x0020, 0x00FF,0x0400, 0x044F, 0 };
			this->VerdanaSmall = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 12.0f, &fontConfig, fontRange);
			this->TitleFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 20.0f, &fontConfig, fontRange);

			constexpr ImWchar iconRange[]{ ICON_MIN_MD, ICON_MAX_MD, 0 };
			ImFontConfig iconConfig;
			iconConfig.MergeMode = true;
			iconConfig.PixelSnapH = true;
			IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(MaterialFont_compressed_data, MaterialFont_compressed_size, 12.f, &iconConfig, iconRange);

			gameFont = ImGui::GetIO().Fonts->AddFontDefault();

			io.Fonts->Build();
		}
	}
}; inline Fonts pFonts;
class Frames
{
public:
	__inline void AimbotFirstFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		//pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text("Aimbot Settings");
		ImGui::Separator();

		ImGui::Checkbox("Enable Aimbot", &Vars::Aimbot::enable_aimbot);
		ImGui::Spacing();
		ImGui::Checkbox("Draw Fov", &Vars::Aimbot::draw_fov);

		pImGuiChildWindow->EndChildFrame();
		//pImGuiFeatures->PopStyleColor(1);
	}
	__inline void AmbotSecondFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		//pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text("Aimbot Extra Settings");
		ImGui::Separator();

		ImGui::Combo("Aim Method", &infos::aimbot::aim_method, infos::aimbot::aim_select, IM_ARRAYSIZE(infos::aimbot::aim_select));
		ImGui::Spacing();

		ImGui::Combo("Target Bone", &infos::aimbot::hitbox_method, infos::aimbot::hitbox_select, IM_ARRAYSIZE(infos::aimbot::hitbox_select));
		ImGui::Spacing();

		ImGui::SliderFloat("Aim Fov", &Vars::Aimbot::aim_fov, 1, 360);
		ImGui::Spacing();

		ImGui::SliderFloat("Smooth Value", &Vars::Aimbot::smooth_value, 0.5, 10);
		ImGui::Spacing();

		ImGui::SliderFloat("Aim Dist", &Vars::Aimbot::aim_dist, 1, 500);
		ImGui::Spacing();
		
		pImGuiChildWindow->EndChildFrame();
		//pImGuiFeatures->PopStyleColor(1);
	}
	__inline void VisualsFirstFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		//pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text("Visual Settings");
		ImGui::Separator();

		ImGui::Checkbox("Enable Visuals", &Vars::Visuals::enable_visuals);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Outline", &Vars::Visuals::enable_player_outline);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Box", &Vars::Visuals::enable_player_box);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Health", &Vars::Visuals::enable_player_health);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Dist To", &Vars::Visuals::dist_to);
		ImGui::Spacing();

		pImGuiChildWindow->EndChildFrame();
		//pImGuiFeatures->PopStyleColor(1);
	}
	__inline void VisualsSecondFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		//pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text("Visual Extra Settings");
		ImGui::Separator();

		ImGui::Checkbox("Enable Enemy Only", &Vars::Visuals::enable_enemy_only);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Weapon Chams", &Vars::Visuals::enable_weapon_chams);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Loba View", &Vars::Visuals::item_outline);
		ImGui::Spacing();

		ImGui::Combo("Health Style", &infos::visuals::health_method, infos::visuals::health, IM_ARRAYSIZE(infos::visuals::health));
		ImGui::Spacing();

		ImGui::Combo("Box Style", &infos::visuals::box_method, infos::visuals::box_select, IM_ARRAYSIZE(infos::visuals::box_select));
		ImGui::Spacing();

		ImGui::Combo("Outline Style", &infos::visuals::outline_method, infos::visuals::outline_select, IM_ARRAYSIZE(infos::visuals::outline_select));
		ImGui::Spacing();

		ImGui::Combo("Wp Cham Style", &infos::visuals::weapon_method, infos::visuals::weapon_select, IM_ARRAYSIZE(infos::visuals::weapon_select));
		ImGui::Spacing();

		//static std::vector flagNames{ "Invulnerable", "Cloaked", "Dead Ringer", "Friends", "Taunting", "Vaccinator", "Unsimulated Players", "Disguised" };
		//static std::vector flagValues{ 1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7 };
		//Components::MultiFlags(flagNames, flagValues, &Vars::Visuals::item_ignore, "Ignore Items");

		ImGui::SliderFloat("Max Esp Dist", &Vars::Visuals::esp_max_dist , 10, 500);
		pImGuiChildWindow->EndChildFrame();
		//pImGuiFeatures->PopStyleColor(1);
	}
	__inline void MiscFirstFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		//pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text("Misc Settings");
		ImGui::Separator();

		ImGui::Checkbox("Enable Misc", &Vars::Misc::enable_misc);
		ImGui::Spacing();

		ImGui::Checkbox("Enable Free Cam", &Vars::Misc::enable_freecam);
		ImGui::Spacing();

		//ImGui::Checkbox("Enable Auto Grapple", &Vars::Misc::enable_auto_grapple);
		//ImGui::Spacing();

		//ImGui::Checkbox("Enable Auto Super Glide", &Vars::Misc::enable_auto_super_glide);

		pImGuiChildWindow->EndChildFrame();
		//pImGuiFeatures->PopStyleColor(1);
	}
	__inline void MiscSecondFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false)
	{
		//pImGuiFeatures->PushStyleColor(ImGuiCol_Border, ImColor(53, 53, 53, 255).Value);
		pImGuiChildWindow->BeginChildFrame(id, size, border);

		ImGui::SetCursorPosX(115);
		ImGui::Text("Misc Extra Settings");
		ImGui::Separator();

		//ImGui::Checkbox("Lifeline heirloom", &Vars::Misc::enable_heirloom);

		pImGuiChildWindow->EndChildFrame();
		//pImGuiFeatures->PopStyleColor(1);
	}
}; inline Frames pFrames;
class Tabs
{
public:
	void aimbot_tab()
	{
		ImGui::PushFont(pFonts.VerdanaSmall);
		pFrames.AimbotFirstFrame("##Aimbot", ImVec2(318, 409), true);
		ImGui::SameLine();
		pFrames.AmbotSecondFrame("##AimbotMisc", ImVec2(318, 409), true);
		ImGui::PopFont();
	}
	void visuals_tab()
	{
		ImGui::PushFont(pFonts.VerdanaSmall);
		pFrames.VisualsFirstFrame("##Visual", ImVec2(318, 409), true);
		ImGui::SameLine();
		pFrames.VisualsSecondFrame("##VisualMisc", ImVec2(318, 409), true);
		ImGui::PopFont();
	}
	void misc_tab()
	{
		ImGui::PushFont(pFonts.VerdanaSmall);
		pFrames.MiscFirstFrame("##Misc", ImVec2(318, 409), true);
		ImGui::SameLine();
		pFrames.MiscSecondFrame("##MiscMisc", ImVec2(318, 409), true);
		ImGui::PopFont();
	}
}; inline Tabs pTabs;