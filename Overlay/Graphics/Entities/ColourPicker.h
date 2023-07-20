#pragma once
#include "Entity.h"
class ColourPicker : public Entity
{
protected:
    Vector2 ClickedPos;
    Color* MainColour;
    Color* RangeColour;
    Color* SelectedColour;
    Vector2 SelectedPos;
    Vector2 SelectedRangePos;
    float Hue = 360;
    bool HeldHue = false;
    bool Open = false;
    static float HueToSliderValue(float hue);
    static float SliderValueToHue(float slidervalue);
    COLORREF ColourPicker::GetColorAtPosition(int x, int y);
public:
    ColourPicker(float x, float y, Color* colour);
    void Update();
    void Draw();
};
