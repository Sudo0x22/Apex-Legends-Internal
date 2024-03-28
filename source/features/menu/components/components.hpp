#pragma once
#include"../draw/draw.hpp"
#include<format>
namespace Components
{
	ImVec4 Hex(int value, float alpha)
	{
		float r = (value >> 16) & 0xFF;
		float g = (value >> 8) & 0xFF;
		float b = value & 0xFF;
		return ImVec4(r / 255, g / 255, b / 255, alpha);
	}
	__inline std::string icon_string(std::string icon, std::string text)
	{
		return icon + text;
	}
	__inline void MultiFlags(std::vector<const char*> flagNames, const std::vector<int>& flagValues, int* flagVar, const std::string& comboName)
	{
		if (flagNames.size() != flagValues.size()) { return; }

		std::string preview = "<Default>##";
		if (*flagVar == 0)
		{
			preview = "<None>##";
		}
		else
		{
			for (size_t i = 0; i < flagValues.size(); i++)
			{
				if (*flagVar & flagValues[i])
				{
					if (preview == "<Default>##") { preview = ""; }
					preview += flagNames[i];
					preview.append(", ");
				}
			}
			preview.pop_back(); preview.pop_back();
		}

		ImGui::PushItemWidth(200);
		if (ImGui::BeginCombo(comboName.c_str(), preview.c_str()))
		{
			for (size_t i = 0; i < flagNames.size(); i++)
			{
				const bool flagActive = *flagVar & flagValues[i];
				if (ImGui::Selectable(flagActive ? std::format("+ {}", flagNames[i]).c_str() : flagNames[i], flagActive, ImGuiSelectableFlags_DontClosePopups))
				{
					if (flagActive)
					{
						*flagVar &= ~flagValues[i];
					}
					else
					{
						*flagVar |= flagValues[i];
					}
				}
			}

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
}