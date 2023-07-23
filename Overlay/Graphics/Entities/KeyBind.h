#pragma once
#include "Entity.h"
class KeyBind : public Entity
{
protected:

    float LastClickTime = 0;

    std::function< void()> Action;
public:
    KeyBind(float x, float y, std::wstring text, int key);
    void Update();
    void Draw();
};
