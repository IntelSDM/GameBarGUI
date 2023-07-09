#include "pch.h"
#include "Form.h"
#include "pch.h"
#include "Form.h"
#include "Drawing.h"
#include "input.h"
#include "Entity.h"
#include "GUI.h"
Form::Form(float x, float y, float w, float h, float borderwidth, float borderheight, std::string text, bool stretch)
{
    Form::Name = text;
    Form::Pos = { x, y };
    Form::Size = { w, h };
    Form::OriginalSize = Form::Size;
    Form::SetVisible(true);
    Form::Stretching = false;
    Form::Dragging = false;
    Form::Drag = { 0,0 };
    Form::Scale.x = (Form::Size.x / Form::OriginalSize.x);
    Form::Scale.y = (Form::Size.y / Form::OriginalSize.y);
    Form::Border.x = borderwidth;
    Form::Border.y = borderheight;
    Form::CanStretch = stretch;
    Form::CanClose = true;
    Form::CanMinimize = true;


}
void Form::DragAction()
{
    if (Form::Dragging && !IsKeyDown(VK_LBUTTON))
        Form::Dragging = false;
    if (Form::Dragging)
    {

        Form::Pos.x = Form::Cursor.x - Form::Drag.x;
        Form::Pos.y = Form::Cursor.y - Form::Drag.y;
    }
    if (IsMouseInRectangle(Form::Pos, Form::TitleBar))
    {
        if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 48, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 28) - (Form::Pos.x + (Form::Size.x) - 48), 19) || IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 25, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 15) - (Form::Pos.x + (Form::Size.x) - 36), 19))
            return;
        if (IsKeyClicked(VK_LBUTTON)) // This prevents a user holding down and hovering over the title bar to drag it. You need to actually click down.
            Form::Dragging = true;

        Form::Drag.x = Form::Cursor.x - Form::Pos.x;
        Form::Drag.y = Form::Cursor.y - Form::Pos.y;
    }
}
void Form::StretchAction()
{
    if (Form::Blocked)
        return;
    // If the user clicks in the rectangle we go through all forms and then set this one as the highest priority to draw
    StretchPoint1 = Vector2{ Form::Pos.x + Form::Size.x, Form::Pos.y + Form::Size.y };
    StretchPoint2 = Vector2{ Form::Pos.x + Form::Size.x - (25 * Form::Scale.x), Form::Pos.y + Form::Size.y };
    StretchPoint3 = Vector2{ Form::Pos.x + Form::Size.x, Form::Pos.y + Form::Size.y - (25 * Form::Scale.y) };

    if (Form::Stretching && !IsKeyDown(VK_LBUTTON))
    {
        Form::Stretching = false;
    }
    if (Form::Stretching)
    {
        float stretchx = Form::Cursor.x - Form::Stretch.x;
        float stretchy = Form::Cursor.y - Form::Stretch.y;
        Vector2 Stretched{ stretchx,stretchy };
        // Prevent the gui going below the original scale
        if (stretchx > Form::OriginalSize.x && stretchy > Form::OriginalSize.y)
        {
            Form::Scale.x = (Form::Size.x / Form::OriginalSize.x);
            Form::Scale.y = (Form::Size.y / Form::OriginalSize.y);
            Form::Size.x = stretchx;
            Form::Size.y = stretchy;
        }
    }
    if (IsMouseInTriangle(StretchPoint1, StretchPoint2, StretchPoint3) && Form::CanStretch)
    {
        if (IsKeyClicked(VK_LBUTTON))
            Form::Stretching = true;

        Form::Stretch.x = Form::Cursor.x - (Form::Size.x);
        Form::Stretch.y = Form::Cursor.y - (Form::Size.y);

    }
}
void Form::Update()
{

    if (!Form::Parent)
        Form::SetVisible(false);
    if (!Form::IsVisible())
        return;
    //SetCursor()
    Form::TitleBar = { Form::Size.x,  Form::Border.y };
    Form::Cursor = MousePos;

    if (Form::Blocked)
        return;
    Form::DragAction();
    Form::StretchAction();
    if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 48, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 28) - (Form::Pos.x + (Form::Size.x) - 48), 19) && (IsKeyClicked(VK_LBUTTON)))
        ShowWindow(NULL, SW_MINIMIZE);
    if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 25, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 15) - (Form::Pos.x + (Form::Size.x) - 36), 19) && IsKeyClicked(VK_LBUTTON))
        exit(NULL);

    Container::Update();

}

void Form::Draw()
{

    if (!Form::IsVisible())
        return;
    // when someone clicks into a form it will prioritize the drawing of the form.
    if (IsMouseInRectangle(Form::Pos, Form::Size) && IsKeyClicked(VK_LBUTTON))
    {
        Form::SetLastClick(clock() * 0.00001f); // we multiple it for accuracy purposes to turn it into a float
    }
    if (!IsMouseInTriangle(StretchPoint1, StretchPoint2, StretchPoint3) && IsMouseInRectangle(Form::Pos, Form::Size) && GetCurrentCursor() == Cursors["Corner Drag"] && !Form::Stretching)
        SetCurrentCursor("Default");
    if (IsMouseInTriangle(StretchPoint1, StretchPoint2, StretchPoint3) && Form::CanStretch)
        SetCurrentCursor("Corner Drag");
    if (Form::CanStretch)
    {
        // debug purposes
      //  Text("1", StretchPoint1.x, StretchPoint1.y, 12, "Verdana",Colour(255, 0, 0, 255), Centre);
       // Text("2", StretchPoint2.x, StretchPoint2.y, 12,"Verdana",Colour(255, 0, 0, 255), Centre);
        //Text("3", StretchPoint3.x, StretchPoint3.y, 12, "Verdana", Colour(255, 0, 0, 255), Centre);
    }

    OutlineRectangle((Form::Pos.x - Form::Border.x / 2) + 1, (Form::Pos.y - Form::Border.x / 2) + 1, Form::Size.x + Form::Border.x - 1, Form::Size.y + Form::Border.x - 1, 1, Colour(140, 140, 140, 255)); // Draw Border
    FilledRectangle(Form::Pos.x, Form::Pos.y, Form::Size.x, Form::Size.y, Colour(40, 40, 40, 255));
    FilledRectangle(Form::Pos.x, Form::Pos.y, Form::Size.x, Form::Border.y, Colour(30, 30, 30, 255)); // header

    Text(Form::Name, Form::Pos.x + 5, Form::Pos.y + 5, 12, "Verdana", Colour(255, 255, 255, 255), None);


#pragma region Minimize
    if (Form::CanMinimize)
    {
        if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 48, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 28) - (Form::Pos.x + (Form::Size.x) - 48), 19) && !IsKeyDown(VK_LBUTTON))
        {
            FilledRectangle(Form::Pos.x + (Form::Size.x) - 43, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 30) - (Form::Pos.x + (Form::Size.x) - 50), 19, Colour(80, 80, 80, 150));
            FilledLine(Form::Pos.x + (Form::Size.x) - 39, Form::Pos.y + 10, Form::Pos.x + (Form::Size.x) - 27, Form::Pos.y + 10, 1, Colour(255, 255, 255, 255));
        }
        else if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 48, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 28) - (Form::Pos.x + (Form::Size.x) - 48), 19) && IsKeyDown(VK_LBUTTON))
        {
            FilledRectangle(Form::Pos.x + (Form::Size.x) - 43, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 30) - (Form::Pos.x + (Form::Size.x) - 50), 19, Colour(80, 80, 80, 150));
            FilledLine(Form::Pos.x + (Form::Size.x) - 39, Form::Pos.y + 10, Form::Pos.x + (Form::Size.x) - 27, Form::Pos.y + 10, 1, Colour(255, 255, 255, 255));
        }
        else
        {
            FilledLine(Form::Pos.x + (Form::Size.x) - 39, Form::Pos.y + 10, Form::Pos.x + (Form::Size.x) - 27, Form::Pos.y + 10, 1, Colour(255, 255, 255, 255));
        }
    }
#pragma endregion

#pragma region Exit
    if (Form::CanClose)
    {
        if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 25, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 15) - (Form::Pos.x + (Form::Size.x) - 36), 19) && !IsKeyDown(VK_LBUTTON))
        {
            FilledRectangle(Form::Pos.x + (Form::Size.x) - 23, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 10) - (Form::Pos.x + (Form::Size.x) - 33), 19, Colour(80, 80, 80, 100));
            FilledLine(Form::Pos.x + (Form::Size.x) - 5, Form::Pos.y + 16, Form::Pos.x + (Form::Size.x) - 18, Form::Pos.y + 4, 1, Colour(255, 255, 255, 255));
            FilledLine(Form::Pos.x + (Form::Size.x) - 18, Form::Pos.y + 16, Form::Pos.x + (Form::Size.x) - 5, Form::Pos.y + 4, 1, Colour(255, 255, 255, 255));
        }
        else if (IsMouseInRectangle(Form::Pos.x + (Form::Size.x) - 25, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 15) - (Form::Pos.x + (Form::Size.x) - 36), 19) && IsKeyDown(VK_LBUTTON))
        {
            FilledRectangle(Form::Pos.x + (Form::Size.x) - 23, Form::Pos.y, (Form::Pos.x + (Form::Size.x) - 10) - (Form::Pos.x + (Form::Size.x) - 33), 19, Colour(80, 80, 80, 150));
            FilledLine(Form::Pos.x + (Form::Size.x) - 5, Form::Pos.y + 16, Form::Pos.x + (Form::Size.x) - 18, Form::Pos.y + 4, 1, Colour(255, 255, 255, 255));
            FilledLine(Form::Pos.x + (Form::Size.x) - 18, Form::Pos.y + 16, Form::Pos.x + (Form::Size.x) - 5, Form::Pos.y + 4, 1, Colour(255, 255, 255, 255));
        }
        else
        {
            FilledLine(Form::Pos.x + (Form::Size.x) - 5, Form::Pos.y + 16, Form::Pos.x + (Form::Size.x) - 18, Form::Pos.y + 4, 1, Colour(255, 255, 255, 255));
            FilledLine(Form::Pos.x + (Form::Size.x) - 18, Form::Pos.y + 16, Form::Pos.x + (Form::Size.x) - 5, Form::Pos.y + 4, 1, Colour(255, 255, 255, 255));
        }
    }
#pragma endregion
    Container::Draw();
}