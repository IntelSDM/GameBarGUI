#include "Pch.h"
#include "Colour.h"

Color Colour(int r, int g, int b, int a)
{
	Color col;
	col.A = a;
	col.R = r;
	col.G = g;
	col.B = b;
	return col;
}

Color HueToRGB(float hue)
{
    hue = fmod(hue, 360.0f);
    if (hue < 0)
        hue += 360.0f;

    int sector = static_cast<int>(hue / 60.0f);

    float fraction = (hue / 60.0f) - sector;

    float c = 1.0f;
    float x = 1.0f - std::abs(2 * fraction - 1);
    float m = 0.0f;
    Color col;
    switch (sector)
    {
    case 0:
        col.R = (c + m) * 255;
        col.G = (x + m) * 255;
        col.B = (m) * 255;
        break;
    case 1:
        col.R = (x + m) * 255;
        col.G = (c + m) * 255;
        col.B = (m) * 255;
        break;
    case 2:
        col.R = (m) * 255;
        col.G = (c + m) * 255;
        col.B = (x + m) * 255;
        break;
    case 3:
        col.R = (m) * 255;
        col.G = (x + m) * 255;
        col.B = (c + m) * 255;
        break;
    case 4:
        col.R = (x + m) * 255;
        col.G = (m) * 255;
        col.B = (c + m) * 255;
        break;
    case 5:
        col.R = (c + m) * 255;
        col.G = (m) * 255;
        col.B = (x + m) * 255;
        break;
    default:
        col.R = 0;
        col.G = 0;
        col.B = 0;
        break;
    }
    col.A = 255;
    return col;
}

float RGBToHue(int r, int g, int b)
{
    float hue = 0.0f;
    float rnorm = static_cast<float>(r) / 255.0f;
    float gnorm = static_cast<float>(g) / 255.0f;
    float bnorm = static_cast<float>(b) / 255.0f;

    float maxcolour = std::max({ rnorm, gnorm, bnorm });
    float mincolour = std::min({ rnorm, gnorm, bnorm });

    if (maxcolour == mincolour)
    {
        hue = 0.0f;
    }
    else
    {
        float delta = maxcolour - mincolour;
        if (maxcolour == rnorm)
            hue = 60.0f * fmod(((gnorm - bnorm) / delta), 6.0f);
        else if (maxcolour == gnorm)
            hue = 60.0f * (((bnorm - rnorm) / delta) + 2.0f);
        else if (maxcolour == bnorm)
            hue = 60.0f * (((rnorm - gnorm) / delta) + 4.0f);
    }

    if (hue < 0.0f)
        hue += 360.0f;

    return hue;
}


Color HsvToRgb(float hue, int saturation, int value,int alpha)
{
    hue = fmod(hue, 360.0f);
    if (hue < 0)
        hue += 360.0f;

    float s = static_cast<float>(saturation) / 255.0f;
    float v = static_cast<float>(value) / 255.0f;

    float c = v * s;
    float x = c * (1 - std::abs(fmod(hue / 60.0f, 2.0f) - 1));
    float m = v - c;

    Color col;
    if (hue >= 0 && hue < 60)
    {
        col.R = static_cast<int>((c + m) * 255);
        col.G = static_cast<int>((x + m) * 255);
        col.B = static_cast<int>(m * 255);
    }
    else if (hue >= 60 && hue < 120)
    {
        col.R = static_cast<int>((x + m) * 255);
        col.G = static_cast<int>((c + m) * 255);
        col.B = static_cast<int>(m * 255);
    }
    else if (hue >= 120 && hue < 180)
    {
        col.R = static_cast<int>(m * 255);
        col.G = static_cast<int>((c + m) * 255);
        col.B = static_cast<int>((x + m) * 255);
    }
    else if (hue >= 180 && hue < 240)
    {
        col.R = static_cast<int>(m * 255);
        col.G = static_cast<int>((x + m) * 255);
        col.B = static_cast<int>((c + m) * 255);
    }
    else if (hue >= 240 && hue < 300)
    {
        col.R = static_cast<int>((x + m) * 255);
        col.G = static_cast<int>(m * 255);
        col.B = static_cast<int>((c + m) * 255);
    }
    else if (hue >= 300 && hue < 360)
    {
        col.R = static_cast<int>((c + m) * 255);
        col.G = static_cast<int>(m * 255);
        col.B = static_cast<int>((x + m) * 255);
    }
    else
    {
        col.R = static_cast<int>(m * 255);
        col.G = static_cast<int>(m * 255);
        col.B = static_cast<int>(m * 255);
    }

    col.A = alpha;
    return col;
}
HsvColour RgbToHsv(int r, int g, int b)
{
    float rnorm = static_cast<float>(r) / 255.0f;
    float gnorm = static_cast<float>(g) / 255.0f;
    float bnorm = static_cast<float>(b) / 255.0f;

    float maxcolor = std::max({ rnorm, gnorm, bnorm });
    float mincolor = std::min({ rnorm, gnorm, bnorm });

    float delta = maxcolor - mincolor;
    float hue = 0.0f;
    float saturation = 0.0f;
    int value = static_cast<int>(maxcolor * 255.0f + 0.5f);

    if (delta != 0.0f)
    {
        if (maxcolor == rnorm)
            hue = 60.0f * fmod(((gnorm - bnorm) / delta), 6.0f);
        else if (maxcolor == gnorm)
            hue = 60.0f * (((bnorm - rnorm) / delta) + 2.0f);
        else if (maxcolor == bnorm)
            hue = 60.0f * (((rnorm - gnorm) / delta) + 4.0f);

        if (maxcolor != 0.0f)
            saturation = delta / maxcolor;
    }

    if (hue < 0.0f)
        hue += 360.0f;

    HsvColour hsv;
    hsv.H = hue;
    hsv.S = static_cast<int>(saturation * 255.0f + 0.5f);
    hsv.V = value;
    return hsv;
}