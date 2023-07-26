#pragma once
#include "Entity.h"
class Toggle : public Entity
{
protected:

    bool* Data;
    bool Tabbed = false;

    float TextWidth = 0;
    float TextHeight = 0;

public:
    Toggle(float x, float y, std::wstring text, bool* data);
    void Update();
    void Draw();
};
