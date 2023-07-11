#pragma once
enum Weight
{
	Normal = 0,
	Bold = 1,
	SemiBold = 2,
	Medium = 3,
	SemiLight = 4
};
void CreateFont(std::string name, std::wstring font, int size, Weight weight);
CanvasTextFormat ^ GetFont(std::string name);
void GetTextSize(const std::wstring text, int fontsize, float* const width, float* const height, std::string font);
float GetTextWidth(std::wstring text, int fontsize, std::string font);
float GetTextHeight(std::wstring text, int fontsize, std::string font);