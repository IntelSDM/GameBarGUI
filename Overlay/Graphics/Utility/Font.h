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
Microsoft::Graphics::Canvas::Text::CanvasTextFormat ^ GetFont(std::string name);