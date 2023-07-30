#pragma once
#include "Entity.h"
class ListBoxTab : public Container
{
protected:
    int Index;
    int* Selected;
public:
    ListBoxTab(std::wstring name, int* selectedtab);
    void Update();
    void Draw();
};


