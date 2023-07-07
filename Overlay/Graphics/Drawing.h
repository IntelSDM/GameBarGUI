#pragma once
enum FontAlignment
{
    Left = 0,
    Centre = 1,
    Right = 2,
    CentreLeft = 3,
    CentreRight = 4,
    CentreCentre = 5,
    None = 6
};
void DrawText(int x, int y, std::wstring text, std::string font, int fontsize, Color colour, FontAlignment alignment);