#include "pch.h"
#include "input.h"
const std::wstring ProcessTitle = L"Overlay";

enum class KeyState
{
    KeyDormant = 0,
    KeyInvoked = 1,
    KeyActive = 2
};


std::map<int, bool> KeyHeld;
std::map<int, KeyState> KeyStates;
std::map<int, float> KeyTimes;
std::map<std::string, HCURSOR> Cursors = { {"Default", LoadCursor(NULL, IDC_ARROW)},{"Hand", LoadCursor(NULL, IDC_HAND)},{"Corner Drag", LoadCursor(NULL, IDC_SIZENWSE)},{"Up Down Drag", LoadCursor(NULL, IDC_SIZENS)},{"Side To Side Drag", LoadCursor(NULL, IDC_SIZEWE)} };
HCURSOR CurrentCursor;
Vector2 MousePos;
wchar_t Char;

bool CanCollectInput()
{
	wchar_t  title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, title, sizeof(title));

	std::wstring windowTitle(title);
	return windowTitle == ProcessTitle;
}

void CreateCursor(std::string name, HCURSOR cursor)
{
    Cursors[name] = cursor;
}
void SetCurrentCursor(std::string name)
{
    CurrentCursor = Cursors[name];
}
HCURSOR GetCurrentCursor()
{
    return CurrentCursor;
}


void UpdateKeyState(int key, bool down)
{
    if (key < 0 || key >= KeyStates.size())
        return;
    KeyTimes[key] = clock() * 0.00001f;
    if (KeyHeld[key] && !down)
        KeyStates[key] = KeyState::KeyDormant;

    if (KeyHeld[key] && down)
        KeyStates[key] = KeyState::KeyActive;

    if (!KeyHeld[key] && down)
        KeyStates[key] = KeyState::KeyInvoked;

    KeyHeld[key] = down;
}

// check for a held key
bool IsKeyDown(int key)
{
    if (key < 0 || key >= KeyStates.size())
        return false;
    if (KeyHeld[key] == true)
    {
        return true;
    }
    else
        return false;
}
// check for a clicked key
bool IsKeyClicked(int key)
{
    if (key < 0 || key >= KeyStates.size())
        return false;
    // Check if the click time is below the current time by 0.05 seconds and is invoked, Kinda messy but works well.
    if (KeyStates[key] == KeyState::KeyInvoked && (KeyTimes[key]) <= clock() * 0.00001f)
    {
        KeyTimes[key] = clock() * 0.00001f;
        return true;
    }
    else
        return false;
}

bool IsMouseInRectangle(int x, int y, int width, int height)
{
    return (
        MousePos.x > x &&
        MousePos.y > y &&
        MousePos.x < x + width &&
        MousePos.y < y + height
        );
}

bool IsMouseInRectangle(Vector2 pos, Vector2 Dimensions)
{
    return (
        MousePos.x > pos.x &&
        MousePos.y > pos.y &&
        MousePos.x < pos.x + Dimensions.x &&
        MousePos.y < pos.y + Dimensions.y
        );
}
// just fill the dictionaries
void SetInput()
{
    for (int i = 0; i <= 1000; i++) // 255 is for the ascii character set, expand it for utf8 unicode
    {
        KeyStates[i] = KeyState::KeyDormant;
        KeyHeld[i] = false;

    }
}


float TriangleArea(Vector2 point1, Vector2 point2, Vector2 point3)
{
    return (point1.x - point3.x) * (point2.y - point3.y) - (point2.x - point3.x) * (point1.y - point3.y);
}
bool IsMouseInTriangle(Vector2 point1, Vector2 point2, Vector2 point3)
{
    float d1;
    float d2;
    float d3;

    bool neg;
    bool pos;

    d1 = TriangleArea(MousePos, point1, point2);
    d2 = TriangleArea(MousePos, point2, point3);
    d3 = TriangleArea(MousePos, point3, point1);

    neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(neg && pos);
}
