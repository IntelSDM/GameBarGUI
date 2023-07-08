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
void DrawTextClipped(int x, int y, int width, int height, std::wstring text, std::string font, int fontsize, Color colour, FontAlignment alignment);
void FilledRectangle(int x, int y, int width, int height, Color colour);
void OutlineRectangle(int x, int y, int width, int height, Color colour);
void FilledRoundedRectangle(int x, int y, int width, int height, int aax, int aay, Color colour);
void OutlineRoundedRectangle(int x, int y, int width, int height, int aax, int aay, Color colour);
void OutlineCircle(int x, int y, int radius, int thickness, Color colour);
void FillCircle(int x, int y, int radius, int thickness, Color colour);