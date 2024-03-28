#pragma once
#include"../../sdk/sdk.hpp"
#include"../vars/vars.hpp"
#include"../aimbot/aimbot.hpp"
#include<map>
#include"../../utils/utils.hpp"
ImColor black = ImColor(0, 0, 0, 255);
int skelThikness = 1;
namespace utils
{
	inline float DistanceU(Vector myPos, Vector enPos)
	{
		return sqrt((myPos.x - enPos.x) * (myPos.x - enPos.x) + (myPos.y - enPos.y) * (myPos.y - enPos.y) + (myPos.z - enPos.z) * (myPos.z - enPos.z));
	}
	inline float DistanceM(Vector myPos, Vector enPos)
	{
		auto f = DistanceU(myPos, enPos); f *= 0.0254f; return f;
	}
	inline std::string GetLegendName(Entity* pLocal)
	{
		if (!pLocal) return "";
		uintptr_t name_ptr = *(uintptr_t*)(pLocal + 0x0);
		char name[256];
		ReadStringEx(name_ptr, name, sizeof(name));
		return std::string(name);
	}
	inline std::string GetWeaponName(Entity* pLocal)
	{
		uint64_t primary_weapon_latest = *(uint64_t*)(pLocal + pNetVars.m_wWeapon) & 0xFFFF;
		uint64_t primary_weapon_list = *(uint64_t*)(pOffsets.module_base + pOffsets.cl_entitylist + (primary_weapon_latest << 5));
		int weapon_index = *(int*)(primary_weapon_list + pNetVars.m_wWeaponName);
		switch (weapon_index)
		{
		case 0:
			return ("R301");
			break;
		case 2:
			return ("Bocek");
			break;
		case 86:
			return ("Havoc");
			break;
		case 84:
			return ("Devotion");
			break;
		case 94:
			return ("L-Star");
			break;
		case 108:
			return ("Triple Take");
			break;
		case 111:
			return ("Volt");
			break;
		case 114:
			return ("Nemesis");
			break;
		case 89:
			return ("Flatline");
			break;
		case 91:
			return ("Hemlock");
			break;
		case 112:
			return ("30-30 rifle");
			break;
		case 21:
			return ("Rampage");
			break;
		case 113:
			return ("C.A.R");
			break;
		case 106:
			return ("P2020");
			break;
		case 81:
			return ("RE45");
			break;
		case 80:
			return ("Alternator");
			break;
		case 105:
			return ("R99");
			break;
		case 107:
			return ("Spitfire");
			break;
		case 90:
			return ("G7 scout");
			break;
		case 97:
			return ("Mozambique");
			break;
		case 88:
			return ("eva8 auto");
			break;
		case 104:
			return ("PeaceKeeper");
			break;
		case 1:
			return ("Sentinel");
			break;
		case 83:
			return ("Charge Rifle");
			break;
		case 85:
			return ("LongBow");
			break;
		case 96:
			return ("Mastiff");
			break;
		case 102:
			return ("Prowler");
			break;
		case 110:
			return ("Wingman");
			break;
		case 93:
			return ("Kraber");
			break;
		case 166:
			return ("Knife");
			break;
		}
		return "";
	}
	inline std::string GetPlayerModelName(Entity* pEntity)
	{
		uintptr_t modelOffset = *(uintptr_t*)(pOffsets.module_base + pNetVars.m_ModelName);
		std::string modelName = ReadString32(modelOffset);
		if (modelName.find("dummie") != std::string::npos) modelName = "Dummie";
		else if (modelName.find("ash") != std::string::npos) modelName = "Ash";
		return modelName;
	}
}
class Visuals
{
private:
	__inline void BetterPlayerOutline(int index, Entity* pEntity, INT contextId, uint8_t settingIndex, HighlightFuncBits setting, HighlightParam color)
	{
		if (Vars::Visuals::Glow == false)
			setting = { 0,0,64,64 };

		*(int*)(pEntity + OFFSET_HIGHLIGHTVISIBILITYTYPE) = 2;
		*(int*)(pEntity + OFFSET_HIGHLIGHTCURRENTCONID) = contextId;
		*(uint8_t*)(pEntity + contextId + OFFSET_HIGHLIGHTSERVERACTIVESTATES) = settingIndex;
		uint64_t HighlightSettings = *(uint64_t*)(pOffsets.module_base + OFFSET_HIGHLIGHTSETTINGS);

		*(HighlightFuncBits*)(HighlightSettings + 0x34 * uint64_t(settingIndex) + 0) = setting;;
		*(HighlightParam*)(HighlightSettings + 0x34 * uint64_t(settingIndex) + 4) = color;

		*(int*)(pEntity + 0x268, 2);
	}
	__inline void ItemOutline()
	{
		static bool m_bItemsGlowing = false;
		if (Vars::Visuals::item_outline)
		{
			uint64_t ptr = *(uint64_t*)(pOffsets.module_base + OFFSET_HIGHLIGHTSETTINGS);
			// *(HighlightMode*)(ptr + 0x34 * uint64_t(34)) = { 137,138,64,64 };
			//*(HighlightMode*)(ptr + 0x34 * uint64_t(35)) = { 137,138,64,64 };
			*(HighlightMode*)(ptr + 0x34 * uint64_t(36)) = { 137,138,64,64 };
			*(HighlightMode*)(ptr + 0x34 * uint64_t(37)) = { 137,138,64,64 };
			//*(HighlightMode*)(ptr + 0x34 * uint64_t(38)) = { 137,138,64,64 };
			m_bItemsGlowing = true;
		}
		else
		{
			if (m_bItemsGlowing)
			{
				uint64_t ptr = *(uint64_t*)(pOffsets.module_base + OFFSET_HIGHLIGHTSETTINGS);
				//*(HighlightMode*)(ptr + 0x34 * uint64_t(34)) = { 0 };
				//*(HighlightMode*)(ptr + 0x34 * uint64_t(35)) = { 0 };
				*(HighlightMode*)(ptr + 0x34 * uint64_t(36)) = { 0 };
				*(HighlightMode*)(ptr + 0x34 * uint64_t(37)) = { 0 };
				//*(HighlightMode*)(ptr + 0x34 * uint64_t(38)) = { 0 };
				m_bItemsGlowing = false;
			}
		}
	}
	__inline void PlayerOutline(int index, Entity* pEntity, Entity* pLocal, INT contextId, uint8_t settingIndex, HighlightFuncBits setting, HighlightParam color)
	{
		static bool m_bGlowing = false;
		static bool m_bTeamGlowing = false;
		if (Vars::Visuals::enable_player_outline)
		{
			if (Vars::Visuals::enable_enemy_only && pEntity->m_iTeamNum() == pLocal->m_iTeamNum())
			{
				*(int*)(pEntity + pOffsets.m_bGlowThroughWalls) = 5;
				*(uint8_t*)(pEntity + pOffsets.m_bGlowEnable) = 0;
				m_bTeamGlowing = false;
			}

			auto return_value = [&]() -> uint8_t
				{
					switch (infos::visuals::outline_method) {
					case 0:
						return 0;
						break;
					case 1:
						return 1;
						break;
					case 2:
						return 3;
						break;
					case 3:
						return 4;
						break;
					case 4:
						return 13;
						break;
					case 5:
						return 15;
						break;
					case 6:
						return 30;
						break;
					case 7:
						return 50;
						break;
					}
				};

			*(int*)(pEntity + pOffsets.m_bGlowThroughWalls) = 2;
			*(uint8_t*)(pEntity + pOffsets.m_bGlowEnable) = return_value();
			m_bGlowing = true;
			m_bTeamGlowing = true;
		}
		else
		{
			if (m_bGlowing && m_bTeamGlowing)
			{
				*(int*)(pEntity + pOffsets.m_bGlowThroughWalls) = 5;
				*(uint8_t*)(pEntity + pOffsets.m_bGlowEnable) = 0;
				m_bGlowing = false;
				m_bTeamGlowing = false;
			}
		}
	}
	__inline void WeaponChams(Entity* pLocal)
	{
		static bool enabled = false;
		if (Vars::Visuals::enable_weapon_chams)
		{
			uint64_t actWeaponid = *(uint64_t*)(pLocal + pNetVars.m_ViewModel) & 0xFFFF;
			uint64_t currentWeapon = *(uint64_t*)(pOffsets.module_base + pOffsets.cl_entitylist + (actWeaponid << 5));
			auto return_value = [&]()
			{
				switch (infos::visuals::weapon_method)
				{
				case 0:
					return 0;
					break;
				case 1:
					return 1;
					break;
				case 2:
					return 3;
					break;
				case 3:
					return 4;
					break;
				case 4:
					return 13;
					break;
				case 5:
					return 15;
					break;
				case 6:
					return 30;
					break;
				case 7:
					return 50;
					break;
				}
			};
			*(uint8_t*)(currentWeapon + pOffsets.m_bGlowEnable) = return_value();
			enabled = true;
		}
		else
		{
			if (enabled)
			{
				uint64_t actWeaponId = *(uint64_t*)(pLocal + pNetVars.m_ViewModel) & 0xFFFF;
				uint64_t currentWeapon = *(uint64_t*)(pOffsets.module_base + pOffsets.cl_entitylist + (actWeaponId << 5));
				*(uint8_t*)(currentWeapon + pOffsets.m_bGlowEnable) = 0;
			}
		}
	}
	__inline void SkinChanger(Entity* pLocal, bool isPlayer, int index)
	{
		if (!pLocal)
			return;

		uint64_t weaponHandle = *(uint64_t*)(pLocal + pNetVars.m_wWeapon);
		weaponHandle &= 0xffff;
		uint64_t WeaponEntity = *(uint64_t*)(pOffsets.module_base + pOffsets.cl_entitylist + (weaponHandle << 5));
		float curTime = *(float*)(pLocal + pNetVars.time_base);
		float endTime = curTime * 0.5;
		std::map<int, std::vector<int>> weaponSkinMap;

		weaponSkinMap[103] = { 11,9 };   //R99  
		weaponSkinMap[0] = { 7 };     //R301   
		weaponSkinMap[79] = { 9 };    //转换者  
		weaponSkinMap[89] = { 16 };   //赫姆洛克  
		weaponSkinMap[87] = { 17 };    //平行  
		weaponSkinMap[110] = { 11 };      //3030  
		weaponSkinMap[111] = { 10,11 };   //car   
		weaponSkinMap[20] = { 10 };       //暴走   
		weaponSkinMap[89] = { 12 }; //哈沃克
		weaponSkinMap[83] = { 10 };     //专注  
		weaponSkinMap[109] = { 13 };     //电冲  
		weaponSkinMap[112] = { 8 };     //复仇女神  

		weaponSkinMap[86] = { 11 };     //ev8  
		weaponSkinMap[102] = { 15 };     //heping  
		weaponSkinMap[94] = { 11 };     //aoquan  

		if (isPlayer == false)
		{
			int WeaponIndex = *(int*)(WeaponEntity + pNetVars.m_wWeaponIndex);
			if (weaponSkinMap.count(WeaponIndex) == 0)
				return;
			index = weaponSkinMap[WeaponIndex][0];
		}
		while (curTime < endTime)
		{
			if (isPlayer == true)
				*(int*)(pLocal + pNetVars.m_nSkin) = index;
			else
				*(int*)(WeaponEntity + pNetVars.m_nSkin) = index;
			curTime = *(float*)(pLocal + pNetVars.time_base);
		}
	}
	__inline void HeirloomChanger(int index, Entity* pLocal)
	{
		if (Vars::Misc::enable_heirloom)
		{
			auto handle = *(uint64_t*)(pLocal + pNetVars.m_ViewModel);
			handle &= 0xFFFF;
			auto ptr = *(uint64_t*)(pOffsets.module_base + pOffsets.cl_entitylist + (handle << 5));
			if (!ptr) return;
			char modelName[200] = { 0 };
			auto name_ptr = *(uint64_t*)(ptr + pNetVars.m_ModelName);
			utils::ReadStringEx(name_ptr, modelName, 200);
			std::string model_name = std::string(modelName);
			int cur_seq, index;
			if (model_name.find("mdl/weapons/empty_handed/ptpov_emptyhand.rmdl") != std::string::npos)
			{
				*(const char**)(name_ptr) = "mdl/Weapons/drumstick/ptpov_baton_lifeline.rmdl";
				*(int*)(ptr + 0x00d8) = 3605;
			}
			else if (model_name.find("") != std::string::npos)
			{
				cur_seq = *(int*)(ptr + 0x0e14);
				index = *(int*)(ptr + 0x0e08);
				if (cur_seq == 0 && index == 3605) { *(int*)(ptr + 0x0e14) = 30; }
			}
		}
	}
public:
	__inline void Render(int index, Entity* pLocal, Entity* pEntity)
	{
		{
			Vector localOrigen = pLocal->BasePos();
			int shild = pEntity->m_iShield();
			int health = pEntity->m_iHealth();
			int totallENThealth = health + shild;
			int totalEntityShield = pEntity->m_iMaxShield();

			Vector entityOrigen = pEntity->BasePos();
			Vector entityHead = pEntity->GetEntityBonePos(8, entityOrigen);

			Vector2D S_localOrigen;

			Vector2D S_entityHead;
			Vector2D S_entityOrigen;

			Engine::WorldToScreen(localOrigen, S_localOrigen);
			Engine::WorldToScreen(entityHead, S_entityHead);
			Engine::WorldToScreen(entityOrigen, S_entityOrigen);

			float hight = S_entityHead.DistTo(S_entityOrigen);
			float width = hight / 2.f;

			int distance = Engine::ToMeters(localOrigen.DistTo(entityOrigen));
			auto dist_from = utils::DistanceM(pLocal->BasePos(), entityOrigen);

			if (dist_from >= Vars::Visuals::esp_max_dist) return;

			//bool is_visiable = entity->is_visible(5);
			//float newEntVisTime = *(float*)(pEntity + pNetVars.m_iVisableTime);
			//bool isVisable = newEntVisTime > -1 || (newEntVisTime != -1 && newEntVisTime > 0.f);

			Vector2D topLeft = Vector2D(S_entityHead.x - width / 2, S_entityHead.y - hight);
			Vector2D bottomRight = Vector2D(S_entityHead.x + width / 2, S_entityHead.y);
			float boxMiddle = S_entityOrigen.x - (width / 2.0f);

			ImColor cesp_color;
			RGBA* esp_color;

			if (pEntity->IsVisible(index))
			{
				esp_color = &pColor.Purple;
			}
			else
			{
				esp_color = &pColor.White;
			}

			if (Vars::Visuals::enable_player_box)
			{
				switch (infos::visuals::box_method)
				{
				case 0:
					pDraw.DrawRectBox((S_entityHead.x - width / 2), S_entityHead.y, width, hight, esp_color, 1.5);
					break;
				case 1:
					pDraw.DrawCornerBox(S_entityHead.x - (width / 2), S_entityHead.y, width, hight, 3, esp_color);
					break;
				}
			}

			if (Vars::Visuals::enable_player_health)
			{
				switch (infos::visuals::health_method)
				{
				case 0:
					pDraw.DrawHealthBar((S_entityHead.x - (width / 2)) - 3, S_entityHead.y, 2, hight, health);
					pDraw.DrawShieldBar((S_entityHead.x - (width / 2)) - 6, S_entityHead.y, 2, hight, shild);
					break;
				case 1:
					pDraw.DrawSeerHealth(S_entityHead.x, S_entityHead.y - 15, shild, pEntity->m_iMaxShield(), pEntity->m_iArmorType(), health);
					break;
				}
			}

			if (Vars::Visuals::dist_to)
			{
				pDraw.ApexDrawText(S_entityHead.x, S_entityHead.y + 25,  esp_color, "[%0.fm]", dist_from);
			}
		}
	}
	__inline void Run()
	{
		if (Vars::Visuals::enable_visuals)
		{
			Entity* pLocal = GetLocalPlayer();
			if (!pLocal) return;
			for (int index = 0; index < 64; index++)
			{
				Entity* pEntity = GetEntityFromList(index);
				if (!pEntity || pEntity == pLocal) continue;
				if (pEntity->m_iHealth() == 0) continue;
				if (Vars::Visuals::enable_enemy_only && pEntity->m_iTeamNum() == pLocal->m_iTeamNum()) continue;

				/*this->Render(index, pLocal, pEntity);
				this->WeaponChams(pLocal);
				this->PlayerOutline(index, pEntity, pLocal, 5, 80, { 0,125,64,64 }, { 0,255,255 });
				this->ItemOutline();
				this->HeirloomChanger(index, pLocal);*/
			}
		}
	}
}; inline Visuals pVisuals;