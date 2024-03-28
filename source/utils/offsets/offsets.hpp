#pragma once
#include<cstdint>
#include"../pattern/pattern.hpp"
#include "../winapi/winapi.hpp"
#include "../winapi/crt.hpp"
#include"../globals/globals.hpp"

#define OFFSET_HIGHLIGHTSETTINGS 0xB944E30
#define OFFSET_HIGHLIGHTSERVERACTIVESTATES  0x298      //OFF_GLOW_HIGHLIGHT_ID 
#define OFFSET_HIGHLIGHTCURRENTCONID  0x28C       // OFF_GLOW_ENABLE 
#define OFFSET_HIGHLIGHTVISIBILITYTYPE  0x26c       //OFF_GLOW_THROUGH_WALL
#define HIGHLIGHT_TYPE_SIZE 0x34 //? updated 01/10/2024
#define OFFSET_GLOW_COLOR 0x1d0    + 0x30                // m_highlightParams + 0x18
#define OFFSET_GLOW_TYPE 0x29c                // m_highlightParams + 0x18

class NetVars 
{
public:
	uintptr_t m_iHealth = 0x0;
	uintptr_t m_iTeamNum = 0x0;
	uintptr_t m_clrRender = 0x0;
	uintptr_t m_vLocalOrigin = 0x0;
	uintptr_t m_iMaxShield = 0x0;
	uintptr_t m_iMaxHealth = 0x0;
	uintptr_t m_iArmorType = 0x0;
	uintptr_t m_iVisableTime = 0x0;
	uintptr_t m_vecAbsOrigin = 0x0;
	uintptr_t m_iName = 0x0;
	uintptr_t m_localAngles = 0x0;
	uintptr_t m_iShield = 0x0;
	uintptr_t m_iLifeState = 0x0;
	uintptr_t m_iBleedOutState = 0x0;
	uintptr_t m_vecAbsVelocity = 0x0;
	uintptr_t m_vBones = 0x0;
	uintptr_t m_fFlags = 0x0;
	uintptr_t m_fUsableFov = 0x0;
	uintptr_t m_bThirdPerson = 0x0;
	uintptr_t punch_angle = 0x0;
	uintptr_t time_base = 0x0;
	uintptr_t studiohdr = 0x0;
	uintptr_t third_person = 0x0;
	uintptr_t saver_mode = 0x0;
	uintptr_t m_nSkin = 0x0;
	uintptr_t m_wWeapon = 0x0;
	uintptr_t m_wWeaponName = 0x0;
	uintptr_t m_wWeaponIndex = 0x0;
	uintptr_t m_vViewAngles = 0x0;
	uintptr_t m_ViewModel = 0x0;
	uintptr_t m_ModelName = 0x0;
	uintptr_t m_vecPunchWeaponAngle = 0x0;
	uintptr_t m_iObserverMode = 0x0;
	uintptr_t m_iObserverTarget = 0x0;
	uintptr_t m_vSwayAngles = 0x0;
public:
	__inline bool Initialize() { 
		m_iHealth = 0x0318;
		m_iTeamNum = 0x0328;
		m_bThirdPerson = 0x36f4;
		
		m_vViewAngles = 0x2534 - 0x14;
		m_vSwayAngles = m_vViewAngles - 0x10;
		m_ModelName = 0x0030;

		m_clrRender = 0x0080;
		m_vLocalOrigin = 0x017c;
		m_vecAbsOrigin = 0x017c;

		m_iMaxHealth = 0x0460;
		m_iArmorType = 0x4604;
		m_iMaxShield = 0x01a0;

		m_iName = 0x0471;
		m_localAngles = 0x0378;
		m_vecAbsVelocity = 0x0170;

		m_iLifeState = 0x0680;
		m_fFlags = 0x00c8;
		m_iMaxHealth = 0x0460;
		m_iBleedOutState = 0x26c0;

		m_iShield = 0x01a0;
		m_fUsableFov = 0x080c;
		punch_angle = 0x2438; // 0x2418 0x0040
		
		m_iName = 0x0468;
		m_bThirdPerson = 0x01d00750;
		third_person = 0x3724;
		
		m_iVisableTime = 0x1970 + 0x3;
		m_vBones = 0x0da0 + 0x48; // 0x0e50 + 0x48 0x0da0
		time_base = 0x2068;

		studiohdr = 0xfd0;
		saver_mode = 0x347c;
		m_nSkin = 0x0d38;

		m_wWeapon = 0x1934;
		m_wWeaponIndex = 0x1564;
		m_ViewModel = 0x2d18; // m_hViewModels
		m_vecPunchWeaponAngle = 0x2418;

		m_iObserverMode = 0x34a4;
		m_iObserverTarget = 0x3488;
		
		return true; 
	}
}; inline NetVars pNetVars;
class Buttons
{
public:
	uintptr_t in_attack = 0x0;
	uintptr_t in_jump = 0x0;
	uintptr_t in_duck = 0x0;
public:
	__inline bool Initialize()
	{
		in_attack = 0x073e0bd8;
		in_jump = 0x073e0cf0;
		in_duck = 0x073e0dd8;
		return true;
	}
}; inline Buttons pButtons;
class Offsets
{
public:
	uintptr_t module_base = 0x0;
	uintptr_t local_player = 0x0;
	uintptr_t cl_entitylist = 0x0;
	uintptr_t m_vViewRender = 0x0;
	uintptr_t m_vViewMatrix = 0x0;
	uintptr_t m_gGlobalVars = 0x0;
	uintptr_t m_bGlowThroughWalls = 0x0;
	uintptr_t m_bGlowEnable = 0x0;
	uintptr_t m_bGlowActive = 0x0;
	uintptr_t m_vCameraPos = 0x0;
	uintptr_t m_bGrapple = 0x0;
	uintptr_t m_bGrappleAttached = 0x0;
	uintptr_t m_iTimeScale = 0x0;
	uintptr_t m_iTimeBase = 0x0;
	uintptr_t m_traversalStartTime = 0x0;
	uintptr_t m_traversalProgess = 0x0;
public:
	__inline bool Initialize() { 
		module_base = GetImage<uintptr_t>(L"r5apex.exe");
		local_player = 0x2182bf0;
		cl_entitylist = 0x1dd40f8;
		m_gGlobalVars = 0x16f8b90;
		m_vViewRender = 0x73f1578;
		m_vViewMatrix = 0x11a350;
		m_bGlowThroughWalls = 0x026c;
		m_bGlowEnable = 0x28C;
		m_bGlowActive = 0x268;
		m_vCameraPos = 0x1eb0;
		m_bGrapple = 0x2c20; // m_grapple
		m_bGrappleAttached = 0x0048; // m_grappleAtached
		m_iTimeScale = 0x0174da70; // host_timescale
		m_iTimeBase = 0x2068; // m_currentFramePlayer.timeBase
		m_traversalStartTime = 0x2af0; // m_traversalStartTime
		m_traversalProgess = 0x2aec; // m_traversalProgress
		return true; 
	}
}; inline Offsets pOffsets;

class Sigs
{
public:
	uintptr_t player_fov = 0x0;
	uintptr_t set_cursor_always_visible = 0x0;
public:
	__inline bool Initialize()
	{
		set_cursor_always_visible = pPattern.Find(L"r5apex.exe", L"0F B6 D1 48 8B 0D ? ? ? ? 48 8B 01 48 FF A0 38 01 00 00");
		return true;
	}
}; inline Sigs pSigs;