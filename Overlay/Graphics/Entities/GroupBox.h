#pragma once
#include "Entity.h"
class GroupBox : public Container
{
protected:
    float TextWidth;
    float TextHeight;
    float TextStartPos;
    int TextStartOffset;

    float YBuffer;
public:
    GroupBox(std::wstring name, float x, float y, float width, float height);
    void Update();
    void Draw();
};


