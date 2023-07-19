#pragma once
/*
Instructions on sprite batching:
Call SetDrawingSession
call your spritebatch drawing calls
call PackSpriteSession when you're finished with your draws.
*/
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
void OutlineRectangle(int x, int y, int width, int height, int thickness, Color colour);
void FilledRoundedRectangle(int x, int y, int width, int height, int aax, int aay, Color colour);
void OutlineRoundedRectangle(int x, int y, int width, int height, int aax, int aay, Color colour);
void OutlineCircle(int x, int y, int radius, int thickness, Color colour);
void FilledCircle(int x, int y, int radius, int thickness, Color colour);
void DrawColourPicker(int x, int y, int width, int height, Color colour);
void DrawColourPickerSlider(int x, int y, int width, int height);
void FilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color colour);
void FilledLine(int x1, int y1, int x2, int y2, int thickness, Color colour);


void FilledRectangleOnSpriteBatch(int x, int y, int width, int height, Color colour);
void OutlineRectangleOnSpriteBatch(int x, int y, int width, int height, int thickness, Color colour);
void FilledRoundedRectangleOnSpriteBatch(int x, int y, int width, int height, int aax, int aay, Color colour);
void OutlineRoundedRectangleOnSpriteBatch(int x, int y, int width, int height, int aax, int aay, Color colour);
void OutlineCircleOnSpriteBatch(int x, int y, int radius, int thickness, Color colour);
void FilledCircleOnSpriteBatch(int x, int y, int radius, int thickness, Color colour);
void ColourPickerOnSpriteBatch(int x, int y, int width, int height, Color colour);
void ColourPickerSliderOnSpriteBatch(int x, int y, int width, int height);
void FilledTriangleOnSpriteBatch(int x1, int y1, int x2, int y2, int x3, int y3, Color colour);
void FilledLineOnSpriteBatch(int x1, int y1, int x2, int y2, int thickness, Color colour);
void DrawTextOnSpriteBatch(int x, int y, std::wstring text, std::string font, int fontsize, Color colour, FontAlignment alignment);
void PackSpriteSession();
void SetDrawingSession();