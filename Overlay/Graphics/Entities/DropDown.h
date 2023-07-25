#pragma once
#include "Entity.h"
class DropDown : public Entity
{
protected:
    std::list<std::wstring>Names;
    int* Items;
public:
    DropDown(float x, float y, std::wstring text, int* items,std::list<std::wstring>names);
    void Update();
    void Draw();
};
