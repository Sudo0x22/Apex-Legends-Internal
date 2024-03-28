#include"../components/components.hpp"
#include<Windows.h>

#define VK_0              0x30
#define VK_1              0x31
#define VK_2              0x32
#define VK_3              0x33
#define VK_4              0x34
#define VK_5              0x35
#define VK_6              0x36
#define VK_7              0x37
#define VK_8              0x38
#define VK_9              0x39

#define VK_A              0x41
#define VK_B              0x42
#define VK_C              0x43
#define VK_D              0x44
#define VK_E              0x45
#define VK_F              0x46
#define VK_G              0x47
#define VK_H              0x48
#define VK_J              0x49
#define VK_I              0x4A
#define VK_K              0x4B
#define VK_L              0x4C
#define VK_M              0x4D
#define VK_N              0x4E
#define VK_O              0x4F
#define VK_P              0x50
#define VK_Q              0x51
#define VK_R              0x52
#define VK_S              0x53
#define VK_T              0x54
#define VK_U              0x55
#define VK_V              0x56
#define VK_W              0x57
#define VK_X              0x58
#define VK_Y              0x59
#define VK_Z              0x5A

class ImGuiExtra
{
public:
	__forceinline void CheckBox(LPCSTR szFeature, bool* toggle) {   ImGui::Checkbox(szFeature, toggle); }
	__forceinline void Slider(LPCSTR szName, INT* toggle, INT min, INT max, LPCSTR format = "%d") {  ImGui::SliderInt(szName, toggle, min, max, format); }
	__forceinline bool FloatSlider(LPCSTR szName, FLOAT* toggle, FLOAT min, FLOAT max, LPCSTR format = "%i", FLOAT power = (1.0f)) {
		
		return ImGui::SliderFloat(szName, toggle, min, max, format, power);
	}
	__forceinline void WindowSize(ImVec2 Size) {   ImGui::SetWindowSize(Size, ImGuiCond_Once); }
public:
	bool ComboBox(LPCSTR label, INT* current_item, LPCSTR const items[], INT items_count) { 
		
		return ImGui::Combo(label, current_item, items, items_count, 0);
	}
	__declspec() void Columns(int id) {  ImGui::Columns(id); }
	__declspec() void SetColumns(int index, float offset) {  ImGui::SetColumnOffset(index, offset); }
	__declspec() void NextColumns() {  ImGui::NextColumn(); }
public:
	__declspec() void Spacing1() {   ImGui::Spacing(); }
	__declspec() void Spacing3() {   ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); }
public:
	__declspec() void PushStyleColor(ImGuiCol idx, const ImVec4& clr) {  ImGui::PushStyleColor(idx, clr); }
	__declspec() bool Button(LPCSTR name, ImVec2 size) {   return ImGui::Button(name, size); }
	__declspec() void PopStyleColor(INT index) {   ImGui::PopStyleColor(index); }
public:
	__declspec() void Separator() { ImGui::Separator(); }
public:
	__declspec() void PushStyleVar(ImGuiStyleVar idx, const ImVec2& size) {   ImGui::PushStyleVar(idx, size); }
	__declspec() void PopStyleVar(INT index) {  ImGui::PopStyleVar(index); }
public:
	__declspec() void IconButton(LPCSTR icon, ImVec2 size);
	__declspec() void PushFont(ImFont* font) {   ImGui::PushFont(font); }
	__declspec() void PopFont() {  ImGui::PopFont(); }
}; ImGuiExtra* pImGuiFeatures = new ImGuiExtra();

class ImGuiWindowEx
{
public:
	__forceinline void ProcessBackground() {
		
		auto background = ImGui::GetBackgroundDrawList();
		background->AddRectFilled(ImVec2{ 0,0 }, ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImColor(15, 15, 15, 200));
	}
	__forceinline void SetSize(ImVec2 Size) {
		
		pImGuiFeatures->WindowSize(Size);
	}
	__forceinline bool BeginWindow(LPCSTR name, bool* open = (bool*)0, ImGuiWindowFlags flags = 0) {  return ImGui::Begin(name, open, flags); }
	__forceinline void EndWindow() {  ImGui::End(); }
}; ImGuiWindowEx* pImGuiWindow = new ImGuiWindowEx();

class ImGuiChildWindow
{
public:
	bool BeginChildFrame(const char* id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0) {  return ImGui::BeginChild(id, size, border, flags); }
	__declspec() void EndChildFrame() {  ImGui::EndChild(); }
}; ImGuiChildWindow* pImGuiChildWindow = new ImGuiChildWindow();

class ImGuiTabs
{
public:
	bool BeginTabBar(LPCSTR str_id, ImGuiTabBarFlags flags = 0) {   return ImGui::BeginTabBar(str_id, flags); }
	__declspec() void EndTabBar() {   ImGui::EndTabBar(); }
public:
	bool BeginTabItem(LPCSTR name, bool* open = (bool*)0, ImGuiTabItemFlags flags = 0) {   return ImGui::BeginTabItem(name, open, flags); }
	__declspec() void EndTabItem() {   ImGui::EndTabItem(); }
}; ImGuiTabs* pImGuiTabs = new ImGuiTabs();

#include<time.h>
#include"../../../../includes/imgui/imgui_internal.h"
#include <format>
#include <bitset>
class ImGuiTime
{
public:
	/*LPCSTR GetTime(LPCSTR szFormat) {
		
		time_t now = time(0);
		struct tm tstruct;
		char buf[50];
		tstruct = *localtime(&now);
		strftime)(buf, sizeof(buf), szFormat, &tstruct);
		return buf;
	}*/
}; ImGuiTime* pImGuiTime = new ImGuiTime();

class ImGuiImage
{
public:
	__declspec() void RenderImage(LPCSTR str_id, size_t size, bool* show = (bool*)0) {
		// TODO: Later
	}
};

class ImGuiMultiFlags
{
public:
	__inline void MultiFlags(std::vector<const char*> names, const std::vector<int>& value, int* var, const std::string& name)
	{
		if (names.size() != names.size())
			return;

		std::string preview = "<Default>##";
		if (*var == 0) {
			preview = "Diabled##";
		}
		else
		{
			for (size_t index = 0; index < value.size(); index++)
			{
				if (*var & value[index])
				{
					if (preview == "<Default>##") { preview = ""; }
					preview += names[index];
					preview.append(", ");
				}
			}
			preview.pop_back(); preview.pop_back();
		}

		if (ImGui::BeginCombo(name.c_str(), preview.c_str()))
		{
			for (size_t index = 0; index < names.size(); index++)
			{
				const bool active = *var & value[index];
				if (ImGui::Selectable(active ? std::format("+ {}", names[index]).c_str() : names[index], active, ImGuiSelectableFlags_DontClosePopups))
				{
					if (active) { *var &= ~value[index]; }
					else { *var |= value[index]; }
				}
			}
			ImGui::EndCombo();
		}
	}
}; ImGuiMultiFlags pImGuiMultiFlags;
