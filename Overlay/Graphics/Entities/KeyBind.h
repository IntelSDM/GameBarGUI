#pragma once
#include "Entity.h"
class KeyBind : public Entity
{
protected:
    int* Key;
    void CollectInput();
public:
    KeyBind(float x, float y, std::wstring text, int* key);
    void Update();
    void Draw();
};
