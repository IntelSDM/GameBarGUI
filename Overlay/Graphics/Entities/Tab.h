#pragma once
#include "Entity.h"
class Tab : public Container
{
protected:
    int Index;
    int* Selected;
public:
    Tab(std::wstring name, float x, float y, float width, float height, int* selectedtab);
    void Update();
    void Draw();
};