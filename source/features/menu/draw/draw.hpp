#pragma once
#include<string>
#include"../../../../includes/imgui/imgui.h"
#include"../../../../includes/imgui/imgui_impl_dx11.h"
#include"../../../../includes/imgui/imgui_impl_win32.h"
#include"../../../utils/utils.hpp"
struct RGBA { unsigned long r, g, b, a; };
class Color {
public:
	RGBA White = { 255,255,255,255 };
	RGBA Blue = { 0,0,255,255 };
	RGBA Red = { 255,0,0,255 };
	RGBA Purple = { 255,0,255,255 };
}; Color pColor;
class CDraw {
private:
	__inline std::string string_to_utf8(const std::string& string)
	{
		int nwLen =  pWinApi.MyRtlMultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		pWinApi.MyRtlMultiByteToWideChar(CP_ACP, 0, string.c_str(), string.length(), pwBuf, nwLen);
		int nLen = pWinApi.MyRtlWideToMultiByteChar(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		pWinApi.MyRtlWideToMultiByteChar(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}
public:
	__inline void DrawBackground(int w, int h, int x, int y, ImColor clr)
	{
		auto list = ImGui::GetBackgroundDrawList();
		list->AddRectFilled(ImVec2(w, y), ImVec2(x, y), clr);
	}
	__inline void DrawRect(int x, int h, int w, int y, RGBA* color, int thickness)
	{
        ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), 0, 0, thickness);
	}
	__inline void DrawRectFilled(int x, int y, int w, int h, RGBA* color)
	{
        ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), 0, 0);
	}
	void DrawRectBox(int x, int y, int w, int h, RGBA* color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), 0, 0, thickness);
	}
    void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color)
    {
        DrawRectFilled(x + borderPx, y, w / 3, borderPx, color); //top 
        DrawRectFilled(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
        DrawRectFilled(x, y, borderPx, h / 3, color); //left 
        DrawRectFilled(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
        DrawRectFilled(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
        DrawRectFilled(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
        DrawRectFilled(x + w + borderPx, y, borderPx, h / 3, color);//right 
        DrawRectFilled(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
    }
	void DrawBoxFilled(int x, int y, int w, int h, RGBA* color)
	{
		DrawRectFilled(x - w / 2, y, w, h, color);
		DrawRect((x - w / 2) + 1, y, w, h, color, 1.5);
		DrawRect((x - w / 2) - 1,y, w, h, color, 1.5);
		DrawRect((x - w / 2), y + 1, w, h, color, 1.5);
		DrawRect((x - w / 2), y - 1, w, h, color, 1.5);
		DrawRect((x - w / 2), y, w, h, color , 1.5);
	}
	__inline void DrawCircle(int x, int y, float size, ImColor clr)
	{
		auto list = ImGui::GetOverlayDrawList();
		list->AddCircle(ImVec2(x, y), size, clr);
	}
	__inline void DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor clr)
	{
		ImGui::GetOverlayDrawList()->AddQuadFilled(p1, p2, p3, p4, clr);
	}
	__inline void DrawHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
	{
		ImGui::GetOverlayDrawList()->AddHexagon(p1, p2, p3, p4, p5, p6, col, thickness);
	}
	__inline void DrawHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
	{
		ImGui::GetOverlayDrawList()->AddHexagonFilled(p1, p2, p2, p4, p5, p6, col);
	}
	__inline void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color, float thickness)
	{
		ImGui::GetOverlayDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0,
			color->b / 255.0, color->a / 255.0)), thickness);
	}
	__inline void DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddTriangleFilled(ImVec2(x1, x2), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0,
			color->b / 255.0, color->a / 255.0)));
	}
public:
	__inline void DrawSeerHealth(float x, float y, int shield, int max_shield, int armorType, int health)
	{
		int bg_offset = 3;
		int bar_width = 83;
		float max_health = 100.0f;
		float shield_step = 25.0f;

		int shield_25 = 15;
		int steps = 5;

		ImVec2 bg1(x - bar_width / 2 - bg_offset, y);
		ImVec2 bg2(bg1.x - 10, bg1.y - 16);
		ImVec2 bg3(bg2.x + 5, bg2.y - 7);
		ImVec2 bg4(bg3.x + bar_width + bg_offset, bg3.y);
		ImVec2 bg5(bg4.x + 11, bg4.y + 18);
		ImVec2 bg6(x + bar_width / 2 + bg_offset, y);


		ImVec2 h1(bg1.x + 3, bg1.y - 4);
		ImVec2 h2(h1.x - 5, h1.y - 8);
		ImVec2 h3(h2.x + (float)health / max_health * bar_width, h2.y);
		ImVec2 h4(h1.x + (float)health / max_health * bar_width, h1.y);
		ImVec2 h3m(h2.x + bar_width, h2.y);
		ImVec2 h4m(h1.x + bar_width, h1.y);
		DrawQuadFilled(h1, h2, h3m, h4m, ImColor(10, 10, 30, 60));
		DrawQuadFilled(h1, h2, h3, h4, ImColor(255, 255, 255, 255));


		ImColor shieldCracked(97, 97, 97);
		ImColor shieldCrackedDark(67, 67, 67);

		ImColor shieldCol;
		ImColor shieldColDark; //not used, but the real seer q has shadow inside
		if (armorType == 1) { //white
			shieldCol = ImColor(247, 247, 247);
			shieldColDark = ImColor(164, 164, 164);
		}
		else if (armorType == 2) { //blue
			shieldCol = ImColor(39, 178, 255);
			shieldColDark = ImColor(27, 120, 210);
		}
		else if (armorType == 3) { //purple
			shieldCol = ImColor(206, 59, 255);
			shieldColDark = ImColor(136, 36, 220);
		}
		else if (armorType == 4) { //gold
			shieldCol = ImColor(255, 255, 79);
			shieldColDark = ImColor(218, 175, 49);
		}
		else if (armorType == 5) { //red
			shieldCol = ImColor(219, 2, 2);
			shieldColDark = ImColor(219, 2, 2);
		}
		else {
			shieldCol = ImColor(247, 247, 247);
			shieldColDark = ImColor(164, 164, 164);
		}
		int shield_tmp = shield;
		int shield1 = 0;
		int shield2 = 0;
		int shield3 = 0;
		int shield4 = 0;
		int shield5 = 0;
		if (shield_tmp > 25) {
			shield1 = 25;
			shield_tmp -= 25;
			if (shield_tmp > 25) {
				shield2 = 25;
				shield_tmp -= 25;
				if (shield_tmp > 25) {
					shield3 = 25;
					shield_tmp -= 25;
					if (shield_tmp > 25) {
						shield4 = 25;
						shield_tmp -= 25;
						shield5 = shield_tmp;
					}
					else {
						shield4 = shield_tmp;
					}
				}
				else {
					shield3 = shield_tmp;
				}
			}
			else {
				shield2 = shield_tmp;
			}
		}
		else {
			shield1 = shield_tmp;
		}
		ImVec2 s1(h2.x - 1, h2.y - 2);
		ImVec2 s2(s1.x - 3, s1.y - 5);
		ImVec2 s3(s2.x + shield1 / shield_step * shield_25, s2.y);
		ImVec2 s4(s1.x + shield1 / shield_step * shield_25, s1.y);
		ImVec2 s3m(s2.x + shield_25, s2.y);
		ImVec2 s4m(s1.x + shield_25, s1.y);

		ImVec2 ss1(s4m.x + 2, s1.y);
		ImVec2 ss2(s3m.x + 2, s2.y);
		ImVec2 ss3(ss2.x + shield2 / shield_step * shield_25, s2.y);
		ImVec2 ss4(ss1.x + shield2 / shield_step * shield_25, s1.y);
		ImVec2 ss3m(ss2.x + shield_25, s2.y);
		ImVec2 ss4m(ss1.x + shield_25, s1.y);

		ImVec2 sss1(ss4m.x + 2, s1.y);
		ImVec2 sss2(ss3m.x + 2, s2.y);
		ImVec2 sss3(sss2.x + shield3 / shield_step * shield_25, s2.y);
		ImVec2 sss4(sss1.x + shield3 / shield_step * shield_25, s1.y);
		ImVec2 sss3m(sss2.x + shield_25, s2.y);
		ImVec2 sss4m(sss1.x + shield_25, s1.y);

		ImVec2 ssss1(sss4m.x + 2, s1.y);
		ImVec2 ssss2(sss3m.x + 2, s2.y);
		ImVec2 ssss3(ssss2.x + shield4 / shield_step * shield_25, s2.y);
		ImVec2 ssss4(ssss1.x + shield4 / shield_step * shield_25, s1.y);
		ImVec2 ssss3m(ssss2.x + shield_25, s2.y);
		ImVec2 ssss4m(ssss1.x + shield_25, s1.y);

		ImVec2 sssss1(ssss4m.x + 2, s1.y);
		ImVec2 sssss2(ssss3m.x + 2, s2.y);
		ImVec2 sssss3(sssss2.x + shield5 / shield_step * shield_25, s2.y);
		ImVec2 sssss4(sssss1.x + shield5 / shield_step * shield_25, s1.y);
		ImVec2 sssss3m(sssss2.x + shield_25, s2.y);
		ImVec2 sssss4m(sssss1.x + shield_25, s1.y);
		if (max_shield == 50) {
			if (shield <= 25) {
				if (shield < 25) {
					DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(s1, s2, s3, s4, shieldCol);

			}
			else if (shield <= 50) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				if (shield != 50) {
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			}
		}
		else if (max_shield == 75) {
			if (shield <= 25) {
				if (shield < 25) {
					DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(s1, s2, s3, s4, shieldCol);

			}
			else if (shield <= 50) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				if (shield < 50) {
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			}
			else if (shield <= 75) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
				if (shield < 75) {
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			}
		}
		else if (max_shield == 100) {
			if (shield <= 25) {
				if (shield < 25) {
					DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(s1, s2, s3, s4, shieldCol);

			}
			else if (shield <= 50) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				if (shield < 50) {
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			}
			else if (shield <= 75) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
				if (shield < 75) {
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			}
			else if (shield <= 100) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
				if (shield < 100) {
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
			}
		}
		else if (max_shield == 125) {
			if (shield <= 25) {
				if (shield < 25) {
					DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
					DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(s1, s2, s3, s4, shieldCol);

			}
			else if (shield <= 50) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				if (shield < 50) {
					DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
					DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			}
			else if (shield <= 75) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
				if (shield < 75) {
					DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
					DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			}
			else if (shield <= 100) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
				if (shield < 100) {
					DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
					DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
			}
			else if (shield <= 125) {
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
				DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
				if (shield < 125) {
					DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
				}
				if (shield != 0)
					DrawQuadFilled(sssss1, sssss2, sssss3, sssss4, shieldCol);
			}
		}
	}
	__inline void DrawHealthBar(float x, float y, float w, float h, int health)
	{
		auto list = ImGui::GetOverlayDrawList();
		int healthValue = max(0, min(health, 100));
		int barColor = ImColor(min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255), 25, 255);
		list->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0));
		list->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + (((float)h / 100.0f) * (float)health)), barColor, 0.0f, 0);
	}
	__inline void DrawShieldBar(float x, float y, float w, float h, int shield)
	{
		auto list = ImGui::GetOverlayDrawList();
		int healthValue = max(0, min(shield, 100));
		int barColor = ImColor(min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255), 25, 255);
		list->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0));
		list->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + (((float)h / 100.0f) * (float)shield)), barColor, 0.0f, 0);
	}
	__inline void ApexDrawText(int x, int y, RGBA* color, const char* str, ...)
	{
		va_list(args);
		va_start(args, str);
		CHAR buffer[256] = {};
		vsprintf_s(buffer, str, args);
		va_end(args);
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_to_utf8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0f, color->g / 255.0f, color->b / 255.0f, color->a / 255.0f)), buffer);
	}
	void DrawLineButBetter(ImVec2 point1, ImVec2 point2, ImColor color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(point1.x, point1.y), ImVec2(point2.x, point2.y), color, thickness);
	}
	void DrawCircleFilled(int x, int y, int radius, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, color);
	}
}; inline CDraw pDraw;