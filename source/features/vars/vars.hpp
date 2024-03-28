#pragma once
template<class type>
class CVar
{
public:
	const char* szLabel;
	type szVar;
};
namespace infos
{
	namespace aimbot
	{
		const char* aim_select[3] = { "memory", "smooth", "Slient" };
		static int aim_method = 0;

		const char* hitbox_select[3] = { "head", "cheat", "body" };
		static int hitbox_method = 0;
	}

	namespace visuals
	{
		const char* box_select[2] = { "normal", "corned"};
		static int box_method = 0;

		const char* health[2] = { "normal", "seers" };
		static int health_method = 0;

		const char* weapon_select[8] = { "Disabled", "Pulsing Red", "Pulsing Cyan", "Fast Pulsing White",
		"Cyan Outline", "Light Red Outline", "Solid Purple", "Red Outline"};
		static int weapon_method = 0;

		const char* outline_select[8] = { "Disabled", "Pulsing Red", "Pulsing Cyan", "Fast Pulsing White",
		"Cyan Outline", "Light Red Outline", "Solid Purple", "Red Outline" };
		static int outline_method = 0;

		const char* vm_select[3] = { "Outline", "Material", "Yellow Flash" };
		static int vm_method = 0;
	}

	namespace heirlooms
	{
		const char* heirloom_select[3] = { "None", "LifeLine", "PathFinder" };
		static int heirloom_method = 0;
	}
}
namespace Vars
{
	namespace Aimbot 
	{
		static bool enable_aimbot = false;
		static bool draw_fov = false;
		static float aim_fov= 1.0f;
		static float aim_dist= 250.0f;
		static float smooth_value = 5;
	}
	namespace Visuals
	{
		static bool enable_visuals = false;
		static bool enable_player_outline = false;
		static bool enable_player_box = false;
		static bool enable_player_health = false;
		static bool enable_seer_info = false;
		static bool enable_enemy_only = false;
		static bool enable_weapon_chams = false;
		static float esp_max_dist= 250;
		static bool  enable_warning_sign = false;
		static bool dist_to = false;
		static bool Glow = false;
		static bool item_outline = false;
		static int item_ignore = 0;
		static bool Weapon_Id = false;
	}
	namespace Misc
	{
		static bool enable_misc = false;
		static bool enable_bhop = false;
		static bool enable_freecam = false;
		static bool enable_auto_grapple = false;
		static bool enable_speed_hack = false;
		static bool enable_auto_super_glide = false;
		static float speed_hack_value = 5.f;
		static bool enable_heirloom = false;
	}
}