#pragma once
struct HsvColour
{
    float H;
    float S;
    float V;
};
Color Colour(int r, int g, int b, int a = 255);
Color HueToRGB(float hue);
float RGBToHue(int r, int g, int b);
Color HsvToRgb(float hue, int saturation, int value, int alpha);
HsvColour RgbToHsv(int r, int g, int b);
