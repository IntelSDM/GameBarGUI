#include "pch.h"
#include "Font.h"

std::map<std::string, CanvasTextFormat^> Fonts;

void CreateFont(std::string name, std::wstring font, int size, Weight weight)
{
	CanvasTextFormat^ textformat = ref new CanvasTextFormat();
	Platform::String^ platfont = ref new Platform::String(font.c_str());
	textformat->FontFamily = platfont;
	textformat->FontSize = size;
	switch (weight)
	{
	case 0:
		textformat->FontWeight = FontWeights::Normal;
		break;
	case 1:
		textformat->FontWeight = FontWeights::Bold;
		break;
	case 2:
		textformat->FontWeight = FontWeights::SemiBold;
		break;
	case 3:
		textformat->FontWeight = FontWeights::Medium;
		break;
	case 4:
		textformat->FontWeight = FontWeights::SemiLight;
		break;
	}
	Fonts[name] = textformat;
}

CanvasTextFormat^ GetFont(std::string name)
{
	return Fonts[name];
}