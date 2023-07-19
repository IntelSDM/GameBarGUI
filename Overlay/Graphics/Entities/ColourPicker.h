#pragma once
#include "Entity.h"
class ColourPicker : public Entity
{
protected:
    Vector2 ClickedPos;
    Color* MainColour;
public:
    ColourPicker(float x, float y, Color* colour);
    void Update();
    void Draw();
};
