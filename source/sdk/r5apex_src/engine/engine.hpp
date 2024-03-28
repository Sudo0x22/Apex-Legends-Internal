#pragma once
#include"../../incs/classes.hpp"
#include"../../incs/structs.hpp"
#include"../../../utils/winapi/winapi.hpp"
#include"../../../utils/offsets/offsets.hpp"
#include"../../../utils/offsets_src/offsets_src.hpp"

float oVisTime[100];
namespace Engine
{
	inline Matrix_t GetViewMatrix()
	{
		uint64_t viewRenderer = *(uint64_t*)(pOffsets.module_base + pOffsets.m_vViewRender);
		uint64_t viewMatrix = *(uint64_t*)(viewRenderer + pOffsets.m_vViewMatrix);

		return *(Matrix_t*)(viewMatrix);
	}
	int ret_system(int index) {
		return pWinApi.MyRtlGetSystemMetrics(index);
	}
	bool world_to_screen(Vector2D& screen, float x, float y, float z)
	{
		float* m_vMatrix = GetViewMatrix().matrix;
		float w = m_vMatrix[12] * x + m_vMatrix[13] * y + m_vMatrix[14] * z + m_vMatrix[15];
		if (w < 0.01f)
			return false;
		screen.x = m_vMatrix[0] * x + m_vMatrix[1] * y + m_vMatrix[2] * z + m_vMatrix[3];
		screen.y = m_vMatrix[4] * x + m_vMatrix[5] * y + m_vMatrix[6] * z + m_vMatrix[7];

		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;

		float xx = ImGui::GetIO().DisplaySize.x / 2;
		float xy = ImGui::GetIO().DisplaySize.y / 2;

		xx += 0.5 * screen.x * ImGui::GetIO().DisplaySize.x + 0.5;
		xy -= 0.5 * screen.y * ImGui::GetIO().DisplaySize.y + 0.5;

		screen.x = xx;
		screen.y = xy;

		if (screen.x > ImGui::GetIO().DisplaySize.x || screen.x < 0 || screen.y > ImGui::GetIO().DisplaySize.y || screen.y < 0)
			return false;

		return true;
	}
	bool WorldToScreen(Vector in, Vector2D& out)
	{
		float* m_vMatrix = GetViewMatrix().matrix;
		float w = m_vMatrix[12] * in.x + m_vMatrix[13] * in.y + m_vMatrix[14] * in.z + m_vMatrix[15];

		if (w < 0.01f)
			return false;

		out.x = m_vMatrix[0] * in.x + m_vMatrix[1] * in.y + m_vMatrix[2] * in.z + m_vMatrix[3];
		out.y = m_vMatrix[4] * in.x + m_vMatrix[5] * in.y + m_vMatrix[6] * in.z + m_vMatrix[7];

		float invw = 1.0f / w;
		out.x *= invw;
		out.y *= invw;

		float xx = ImGui::GetIO().DisplaySize.x / 2;
		float xy = ImGui::GetIO().DisplaySize.y / 2;

		xx += 0.5 * out.x * ImGui::GetIO().DisplaySize.x + 0.5;
		xy -= 0.5 * out.y * ImGui::GetIO().DisplaySize.y + 0.5;

		out.x = xx;
		out.y = xy;

		if (out.x > ImGui::GetIO().DisplaySize.x || out.x < 0 || out.y >  ImGui::GetIO().DisplaySize.y || out.y < 0)
			return false;

		return true;
	}
	__inline float ToMeters(float x) { return x / 39.62f; }
}