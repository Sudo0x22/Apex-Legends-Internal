#pragma once
#include"../../../utils/offsets/offsets.hpp"
#include"../engine/engine.hpp"
#include"../../../utils/netvars/netvar.hpp"
class Entity
{
public:
	inline int m_iHealth()
	{
		return *(int*)(this + pNetVars.m_iHealth);
	}
	inline int m_iMaxHealth() {
		return *(int*)(this + pNetVars.m_iMaxHealth);
	}
	inline int m_iShield()
	{
		return *(int*)(this + pNetVars.m_iShield);
	}
	inline int m_iMaxShield() {
		return *(int*)(this + pNetVars.m_iMaxShield);
	}
	inline int m_iTeamNum()
	{
		return *(int*)(this + pNetVars.m_iTeamNum);
	}
	inline int m_iArmorType()
	{
		return *(int*)(this + pNetVars.m_iArmorType);
	}
	inline uint8_t m_clrRender()
	{
		return *(uint8_t*)(this + pNetVars.m_clrRender);
	}
	inline float m_iVisibleTime() { return *(float*)(this + pNetVars.m_iVisableTime); }
	inline int m_iObserverMode() { return *(int*)(this + pNetVars.m_iObserverMode); }
	inline int m_iObserverTarget() { return *(int*)(this + pNetVars.m_iObserverTarget); }
	bool IsVisible(int i)
	{
		const auto visCheck = m_iVisibleTime();
		const auto IsVis = visCheck > oVisTime[i] || visCheck < 0.f && oVisTime[i] > 0.f;
		oVisTime[i] = visCheck;
		return IsVis;
	}
	inline bool m_bIsPlayer() { return *(uint64_t*)(this + pNetVars.m_iName) = 0x0; }
	inline bool m_bIsAlive() 
	{
		if (this->m_iHealth() != 0)
			return true;
		return false;
	}
	inline bool m_bKnocked() 
	{
		return *(int*)(this + pNetVars.m_iBleedOutState) > 0;
	}
	inline float m_fFlags() 
	{
		return *(float*)(this + pNetVars.m_fFlags);
	}
	float m_fUsableFov() {
		return *(float*)(this + pNetVars.m_fUsableFov);
	}
	int m_bThirdPerson() { return *(int*)(this + pNetVars.m_bThirdPerson); }
public:
	Vector BasePos() {
		return *(Vector*)(this + pNetVars.m_vLocalOrigin);
	}
	uintptr_t GetEntityBoneArray() { return *(uintptr_t*)(this + pNetVars.m_vBones); }
	Vector GetEntityBonePos(uint32_t id, Vector basePos)
	{
		uintptr_t pBoneArray = GetEntityBoneArray();
		Vector EntityHead = Vector();
		EntityHead.x = *(float*)(pBoneArray + 0xCC + (id * 0x30)) + basePos.x;
		EntityHead.y = *(float*)(pBoneArray + 0xDC + (id * 0x30)) + basePos.y;
		EntityHead.z = *(float*)(pBoneArray + 0xEC + (id * 0x30)) + basePos.z;
		return EntityHead;
	}
	Vector BonePos(int index)
	{
		Vector Pos = *(Vector*)(this + pNetVars.m_vLocalOrigin);
		uintptr_t boneArray = *(uintptr_t*)(this + pNetVars.m_vBones);
		Vector bone = Vector();
		uint32_t boneloc = (index * 0x30);
		Bone_t bo = {};
		bo = *(Bone_t*)(boneArray + boneloc);
		bone.x = bo.x + Pos.x;
		bone.y = bo.y + Pos.y;
		bone.z = bo.z + Pos.z;
		return bone;
	}
	Vector m_iViewAngles() { return *(Vector*)(this + pNetVars.m_vViewAngles); }
	QAngle m_qViewAngles() { return *(QAngle*)(this + pNetVars.m_vViewAngles); }
	void m_vSetViewAngles(Vector Angle) { *(Vector*)(this + pNetVars.m_vViewAngles) = Angle; }
	void m_qSetViewAngles(QAngle Angle) { *(QAngle*)(this + pNetVars.m_vViewAngles) = Angle; }
	Vector m_iAimPunch() { return *(Vector*)(this + pNetVars.m_vecPunchWeaponAngle); }
	Vector m_vCameraPos() { return *(Vector*)(this + pOffsets.m_vCameraPos); }
	Vector m_iSwayAngles() { return *(Vector*)(this + pNetVars.m_vSwayAngles); }
public:
	std::string EntityName()
	{
		uintptr_t nameIndex = *(uintptr_t*)(this + 0x0449);
		uintptr_t nameOffset = *(uintptr_t*)(pOffsets.module_base + pNetVars.m_iName + ((nameIndex - 1) << 4));
		std::string playerName = utils::ReadString64(nameOffset);
		return playerName;
	}
};

Entity* GetLocalPlayer() { return *(Entity**)(pOffsets.module_base + pOffsets.local_player); }
Entity* GetEntityFromList(uintptr_t index)
{
	return *(Entity**)(pOffsets.module_base + pOffsets.cl_entitylist + (index << 5));
}
