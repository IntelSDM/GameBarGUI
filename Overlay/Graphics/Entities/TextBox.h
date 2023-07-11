#pragma once
#include "Entity.h"
class TextBox : public Entity
{
protected:

    std::chrono::time_point<std::chrono::high_resolution_clock> AnimationStart;
    float AnimationInterval = 1.0f;

    int SelectedPoint;
    float SelectedPosition;

    int VisiblePointerStart;
    int  VisiblePointerEnd;
    void TextBox::SetStartIndex();
    Vector2 Pos;
    Vector2 Size;
    Vector2 ParentPos;

    std::wstring* MainString;
    std::wstring VisibleString;

    float TextWidth = 0;
    float TextHeight = 0;

    bool Selecting = false;
    bool Held = false;

    bool IsKeyAcceptable();

public:
    TextBox(float x, float y, std::wstring text, std::wstring* data);
    void Update();
    void Draw();
    bool IsTabbed;
};
