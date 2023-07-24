#pragma once
#include "Entity.h"
class ImageTab : public Entity
{
protected:

public:
    ImageTab(float x, float y, std::wstring image);
    void Update();
    void Draw();
};
