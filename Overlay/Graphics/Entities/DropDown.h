#pragma once
#include "Entity.h"
class DropDown : public Entity
{
protected:
    float DropWidth;
    std::list<std::wstring>Names;
    int* Index;
    bool Active = false;
    std::wstring SelectedName;
    float TextWidth = 0;
    float CutOffBuffer = 0;
    void ConvertSelectedName();
    void CalculateBuffer();
    void SetDropDownWidth();
    float SizeDifference;
public:
    DropDown(float x, float y, std::wstring text, int* items,std::list<std::wstring>names);
    void Update();
    void Draw();
};
