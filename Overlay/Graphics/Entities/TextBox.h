#pragma once
#include "Entity.h"
class TextBox : public Entity
{
protected:

    int LastAnimationTime = 0;
    int AnimationDuration = 1;

    int SelectionStart = 0;
    int SelectionEnd = 0;
    int SlidingValue = 0;

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
