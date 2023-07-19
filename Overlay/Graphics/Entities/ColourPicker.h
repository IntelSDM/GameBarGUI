#pragma once
#include "Entity.h"
class ColourPicker : public Entity
{
protected:

    Color* MainColour;
public:
    ColourPicker(float x, float y, std::wstring text, Color* colour);
    void Update();
    void Draw();
};
