#pragma once
#include"../../sdk/sdk.hpp"
#include"../vars/vars.hpp"
#include<chrono>
#include<thread>
class Misc
{
private:
	__inline void FreeCam(Entity* pLocal)
	{
		static bool bIsInFreeCam = false;
		if (Vars::Misc::enable_freecam)
		{
			*(int*)(pLocal + pNetVars.m_iObserverMode) = 7;
			bIsInFreeCam = true;
		}
		else
		{
			if (bIsInFreeCam) { *(int*)(pLocal + pNetVars.m_iObserverMode) = 0; bIsInFreeCam = false; }
		}
	}
	__inline void AutoGrapple(Entity* pLocal)
	{
		if (!Vars::Misc::enable_auto_grapple)
			return;

		unsigned long millseconds = 1000;
		int Attach = *(int*)(pLocal + pOffsets.m_bGrapple + pOffsets.m_bGrappleAttached);
		if (Attach == 1)
		{
			*(int*)(pOffsets.module_base + pButtons.in_jump + 0x8) = 5;
			*(int*)(pOffsets.module_base + pButtons.in_jump + 0x8) = 4;
		}
	}
	__inline void BHop(Entity* pLocal)
	{

	}
	__inline void AutoSuperGlide(Entity* pLocal)
	{
		if (!Vars::Misc::enable_auto_super_glide)
			return;

		static float startJumpTime = 0;
		static bool startSig = false;

		float WorldTime = *(float*)(pLocal + pOffsets.m_iTimeBase);
		float m_traversalStartTime = *(float*)(pLocal + pOffsets.m_traversalStartTime);
		float m_traversalProgess = *(float*)(pLocal + pOffsets.m_traversalProgess);

		auto HangOnWall = -(m_traversalStartTime - WorldTime);
		if (m_traversalProgess > 0.87f && !startSig && HangOnWall > 0.05f && HangOnWall < 1.5f)
		{
			startJumpTime = WorldTime;
			startSig = true;
		}

		if (!HangOnWall)
			return;

		if (startSig)
		{
			*(int*)(pOffsets.module_base + pButtons.in_jump + 0x8) = 7;
			if ((WorldTime - startJumpTime) > 0.007f)
			{
				*(int*)(pOffsets.module_base + pButtons.in_duck + 0x8) = 6;
			}
		}

		if ((WorldTime - startJumpTime) > 1.5f && startSig)
		{
			*(int*)(pOffsets.module_base + pButtons.in_jump + 0x8) = 4;
			*(int*)(pOffsets.module_base + pButtons.in_duck + 0x8) = 4;
			startSig = false;
		}

	}
	__inline void SpeedHack(Entity* pLocal)
	{
		if (!Vars::Misc::enable_speed_hack)
			return;

		if (pWinApi.MyRtlGetAsyncKeyState(VK_LSHIFT))
		{
			*(float*)(pOffsets.module_base + pOffsets.m_iTimeScale + 0x68) = 5.f;
		}
		else
		{
			*(float*)(pOffsets.module_base + pOffsets.m_iTimeScale + 0x68) = 1;
		}
	}
public:
	__inline void Run()
	{
		if (!Vars::Misc::enable_misc)
			return;
		Entity* pLocal = GetLocalPlayer();
		if (!pLocal || pLocal->m_iHealth()==0 || pLocal->m_bKnocked())
			return;
		this->FreeCam(pLocal);
	}
}; inline Misc pMisc;