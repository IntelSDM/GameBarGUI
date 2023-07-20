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