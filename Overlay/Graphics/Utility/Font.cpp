#include "pch.h"
#include "Font.h"
#include "graphics.h"
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

void GetTextSize(const std::wstring text, int fontsize, float* const width, float* const height, std::string font)
{
	if (text.empty())
		return;
	if (!width && !height)
		return;
	
	Platform::String^ platstring = ref new Platform::String(text.data());
	CanvasTextLayout^ layout = ref new CanvasTextLayout(SwapChain, platstring, GetFont(font), *width, *height);
	layout->SetFontSize(0, text.length(), fontsize);
	float modifier = layout->DefaultFontSize / 4.0f; // metrics isn't ever correct
	// yeah the height and width are the wrong way round. no idea why
	*width = layout->LayoutBounds.Height;
	*height = layout->LayoutBounds.Width + modifier;
}