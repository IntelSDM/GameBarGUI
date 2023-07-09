#pragma once
#include "Entity.h"

class Label : public Entity
{
protected:
    bool Tabbed;
public:
    Label(std::wstring, float, float);
    void Update();
    void Draw();
};

