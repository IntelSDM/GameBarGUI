#include "pch.h"
#include "ColourPicker.h"
#include "Input.h"
#include "Drawing.h"

ColourPicker::ColourPicker(float x, float y, Color* colour)
{
	ColourPicker::MainColour = colour;
	ColourPicker::Size = {20,10};
	ColourPicker::Pos = { x,y };
	ColourPicker::Open = false;
	ColourPicker::Hue = RGBToHue(ColourPicker::MainColour->R, ColourPicker::MainColour->G, ColourPicker::MainColour->B);
	ColourPicker::Alpha = MainColour->A;
	ColourPicker::Saturation = RgbToHsv(ColourPicker::MainColour->R, ColourPicker::MainColour->G, ColourPicker::MainColour->B).V;
	ColourPicker::Brightness = RgbToHsv(ColourPicker::MainColour->R, ColourPicker::MainColour->G, ColourPicker::MainColour->B).S;

}
float ColourPicker::HueToSliderValue(float hue)
{
	return hue / 360.0f;
}

float ColourPicker::SliderValueToHue(float slidervalue)
{
	return slidervalue * 360.0f;
}

float ColourPicker::AlphaToSliderValue(float alpha)
{
	return alpha / 255.0f;
}
float ColourPicker::SaturationToSliderValue(float saturation)
{
	return saturation / 255.0f;
}
void ColourPicker::Update()
{
	if (!ColourPicker::Parent)
		ColourPicker::SetVisible(false);
	if (!ColourPicker::IsVisible())
		return;
	ColourPicker::ParentPos = ColourPicker::Parent->GetParent()->GetPos();
	if (!(IsMouseInRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y) || IsMouseInRectangle(ClickedPos.x - 5, ClickedPos.y - 5, 175, 175)) && IsKeyClicked(VK_LBUTTON) && ColourPicker::Open)
	{
		ColourPicker::Open = false;
		SetBlockedSiblings(false);

	}
	if (ColourPicker::Blocked)
		return;
	if (IsMouseInRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y) && IsKeyClicked(VK_LBUTTON) && ColourPicker::LastClick < (clock() * 0.00001f))
	{
		ClickedPos = MousePos;
		ColourPicker::Open = !ColourPicker::Open;
		ColourPicker::LastClick = (clock() * 0.00001f) + 0.002f;
		if(ColourPicker::Open)
			SetBlockedSiblings(true);
		if (!ColourPicker::Open)
			SetBlockedSiblings(false);
	}
	if (!IsKeyDown(VK_LBUTTON))
	{
		ColourPicker::HeldHue = false;
		ColourPicker::HeldAlpha = false;
		ColourPicker::HeldSaturation = false;
		*ColourPicker::MainColour = HsvToRgb(ColourPicker::Hue, ColourPicker::Brightness, ColourPicker::Saturation, ColourPicker::Alpha);
	}
	
	if (!ColourPicker::Open)
		return;
	if (IsMouseInRectangle(ClickedPos.x, ClickedPos.y, 150, 150) && IsKeyClicked(VK_LBUTTON) && ColourPicker::LastClick < (clock() * 0.00001f))
	{
		ColourPicker::HeldSaturation = true;
		ColourPicker::LastClick = (clock() * 0.00001f) + 0.002f;
	}
	if (IsMouseInRectangle(ClickedPos.x, ClickedPos.y+155, 150, 10) && IsKeyClicked(VK_LBUTTON) && ColourPicker::LastClick < (clock() * 0.00001f))
	{
		ColourPicker::HeldHue = true;
		ColourPicker::LastClick = (clock() * 0.00001f) + 0.002f;
	}
	if (IsMouseInRectangle(ClickedPos.x + 155, ClickedPos.y, 20, 165) && IsKeyClicked(VK_LBUTTON) && ColourPicker::LastClick < (clock() * 0.00001f))
	{
		ColourPicker::HeldAlpha = true;
		ColourPicker::LastClick = (clock() * 0.00001f) + 0.002f;
	}
	if (HeldHue)
	{
		// Calculate the slider value from the mouse position
		const float clamp = std::clamp<float>((float)MousePos.x - (float)(ClickedPos.x), 0.00f, (float)150);
		const float ratio = clamp /150;
		ColourPicker::Hue = 0.0f + (360.0f - 0.0f) * ratio;
		// second var creates brigthness/ fullcolour - white, second one does black to full colour
		*ColourPicker::MainColour = HsvToRgb(ColourPicker::Hue, ColourPicker::Brightness, ColourPicker::Saturation, ColourPicker::Alpha);
	}
	if (HeldAlpha)
	{
		// Calculate the slider value from the mouse position
		const float clamp = std::clamp<float>((float)MousePos.y - (float)(ClickedPos.y), 0.00f, (float)165);
		const float ratio = clamp / 165;
		ColourPicker::Alpha = (1.0f - ratio) * 255;
		ColourPicker::MainColour->A = ColourPicker::Alpha;
	}
	if (HeldSaturation)
	{
		// Calculate the saturation values from the mouse position
		const float xclamp = std::clamp<float>((float)MousePos.x - (float)(ClickedPos.x), 0.00f, (float)150);
		const float yclamp = std::clamp<float>((float)MousePos.y - (float)(ClickedPos.y), 0.00f, (float)150);

		const float xratio = xclamp / 150.0f;
		const float yratio = (150.0f - yclamp) / 150.0f;
		ColourPicker::Saturation = yratio * 255.0f;
		ColourPicker::Brightness = xratio * 255.0f;
	//	ColourPicker::Saturation = std::sqrt(xratio * xratio + yratio * yratio) * 255.0f;
		if (ColourPicker::Saturation > 255.0f)
			ColourPicker::Saturation = 255.0f;
		if (ColourPicker::Brightness > 255.0f)
			ColourPicker::Brightness = 255.0f;
	
	}
}

void ColourPicker::Draw()
{
	if (!ColourPicker::Parent)
		ColourPicker::SetVisible(false);
	if (!ColourPicker::IsVisible())
		return;
	FilledRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y, *ColourPicker::MainColour);
	OutlineRectangle(ColourPicker::ParentPos.x + ColourPicker::Pos.x, ColourPicker::ParentPos.y + ColourPicker::Pos.y, ColourPicker::Size.x, ColourPicker::Size.y, 1, Colour(85, 85, 85, 255));
	
	

	if (ColourPicker::Open)
	{
		FilledRectangle(ClickedPos.x - 5, ClickedPos.y - 5, 185, 175, Colour(85, 85, 85, 255));
		OutlineRectangle(ClickedPos.x - 5, ClickedPos.y - 5, 185, 175,1, Colour(180, 180, 180, 255));
		SaturationSlider(ClickedPos.x, ClickedPos.y, 150, 150, HsvToRgb(ColourPicker::Hue, 255.0f, 255.0f,ColourPicker::Alpha));
		

		// alpha
		OutlineRectangle(ClickedPos.x + 155, ClickedPos.y, 20, 165, 1, Colour(180, 180, 180, 255));
		AlphaSlider(ClickedPos.x + 155, ClickedPos.y, 20, 165, *ColourPicker::MainColour);
		float alphavalue = ColourPicker::AlphaToSliderValue(ColourPicker::Alpha);
		FilledRectangle(ClickedPos.x + 155, ClickedPos.y + ((int)165 * (1.0f - alphavalue)), 20, 2, Colour(255, 255, 255, 255));
		
		// hue
		HueSlider(ClickedPos.x, ClickedPos.y + 155, 150, 10);
		float huevalue = ColourPicker::HueToSliderValue(ColourPicker::Hue);
		FilledRectangle(ClickedPos.x + ((int)150 * huevalue), ClickedPos.y + 155, 2, 10, Colour(255, 255, 255, 255));
	}
}