#pragma once
#include"../vars/vars.hpp"
#include"../../sdk/sdk.hpp"

Vector oldPunch;
Vector old_aimpunch;

namespace utils
{
	bool CheckInFov(Vector2D screen_body, float FOVMax)
	{
		float dist = GetCrossDistance(screen_body.x, screen_body.y, (ImGui::GetIO().DisplaySize.x / 2), (ImGui::GetIO().DisplaySize.y / 2));
		if (dist < FOVMax)
		{
			float Radius = Vars::Aimbot::aim_fov;
			if (screen_body.x <= ((ImGui::GetIO().DisplaySize.x / 2) + Radius) &&
				screen_body.x >= ((ImGui::GetIO().DisplaySize.x / 2) - Radius) &&
				screen_body.y <= ((ImGui::GetIO().DisplaySize.y / 2) + Radius) &&
				screen_body.y >= ((ImGui::GetIO().DisplaySize.y / 2) - Radius))
			{
				FOVMax = dist;
				return true;
			}
			return false;
		}
	}

	Vector CalcAngle(Vector Src, Vector Dst)
	{
		Vector Angle = Vector();
		SVector delta = SVector((Src.x - Dst.x), (Src.y - Dst.y), (Src.z - Dst.z));
		double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
		Angle.x = atan(delta.z / hyp) * (180.0f / M_PI);
		Angle.y = atan(delta.y / delta.x) * (180.0f / M_PI);
		if (delta.x >= 0.0) Angle.y += 180.0f;
		return Angle;
	}
}

Vector GetBestBone(Entity* from, Entity* to)
{
	auto calculated_angle = utils::CalcAngle(from->m_vCameraPos(), to->BonePos(5));
	Vector ViewAngles = from->m_iViewAngles();
	Vector SwayAngles = from->m_iSwayAngles();
	calculated_angle.Normalize();
	Vector Delta = calculated_angle - ViewAngles;
	Delta.Normalize();
	Vector SmoothedAngle = ViewAngles + Delta / Vars::Aimbot::smooth_value;
	return SmoothedAngle;
}

int GetHitbox()
{
	switch (infos::aimbot::hitbox_method)
	{
	case 0: return 8;
	case 1: return 10;
	case 2: return 5;
	}
	return 8;
}

class Aimbot
{
private:
	__inline void MemoryAim(int index, Entity* pLocal, Entity* pEntity, Vector2D EntityPos) 
	{
		if (pEntity->IsVisible(index) && utils::CheckInFov(EntityPos, 9999.f) && pWinApi.MyRtlGetAsyncKeyState(VK_RBUTTON))
		{
			pLocal->m_vSetViewAngles(GetBestBone(pLocal, pEntity));
		}
	}
	__inline void SmoothAim(int index, Vector2D EntityPos, Entity* pLocal, Entity* pEntity)
	{
		if (pEntity->IsVisible(index) && utils::CheckInFov(EntityPos, 9999.f) && pWinApi.MyRtlGetAsyncKeyState(VK_RBUTTON))
		{
			pLocal->m_vSetViewAngles(GetBestBone(pLocal, pEntity));
		}
	}
private:
	__inline void Init(int index, Entity* pLocal, Entity* pEntity)
	{
		Vector PosBase = pEntity->BasePos();
		Vector MyBase = pLocal->BasePos();

		Vector PosHead = pEntity->BonePos(8);
		Vector PosBody = pEntity->BonePos(5);
		Vector TargetBone = pEntity->BonePos(GetHitbox());

		Vector2D ScreenBase; Engine::world_to_screen(ScreenBase, PosBase.x, PosBase.y, PosBase.z);
		Vector2D ScreenHead; Engine::world_to_screen(ScreenHead, PosHead.x, PosHead.y, PosHead.z);
		Vector2D ScreenBody; Engine::world_to_screen(ScreenBody, PosBody.x, PosBody.y, PosBody.z);
		Vector2D ScreenBone; Engine::world_to_screen(ScreenBone, TargetBone.x, TargetBone.y, TargetBone.z);
	}
public:
	__inline void Run()
	{
		if (!Vars::Aimbot::enable_aimbot)
			return;

		Entity* pLocal = GetLocalPlayer();
		if (!pLocal) return;

		for (int index = 0; index < 64; index++)
		{
			Entity* pEntity = GetEntityFromList(index);
			if (!pEntity || pEntity == pLocal) continue;
			if (pEntity->m_iTeamNum() == pLocal->m_iTeamNum()) continue;
			if (pEntity->m_iHealth() == 0 && pLocal->m_iHealth() == 0) continue;
			this->Init(index, pLocal, pEntity);
		}
	}
}; inline Aimbot pAimbot;