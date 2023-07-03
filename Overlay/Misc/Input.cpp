#include "pch.h"
#include "input.h"
const std::wstring ProcessTitle = L"Overlay";

std::map<int, bool> KeyHeld;
std::map<int, KeyState> KeyStates;
std::map<int, float> KeyTimes;
std::map<std::string, HCURSOR> Cursors = { {"Default", LoadCursor(NULL, IDC_ARROW)},{"Hand", LoadCursor(NULL, IDC_HAND)},{"Corner Drag", LoadCursor(NULL, IDC_SIZENWSE)},{"Up Down Drag", LoadCursor(NULL, IDC_SIZENS)},{"Side To Side Drag", LoadCursor(NULL, IDC_SIZEWE)} };
HCURSOR CurrentCursor;
POINT MousePos;

enum class KeyState
{
    KeyDormant = 0,
    KeyInvoked = 1,
    KeyActive = 2
};

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
    KeyTimes[key] = clock() * 0.001f;
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
    if (KeyStates[key] == KeyState::KeyInvoked && (KeyTimes[key]) >= (clock() * 0.001f) - 0.05f)
        return true;
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
    for (int i = 0; i <= 285; i++) // 255 is for the ascii character set, expand it for utf8 unicode
    {
        KeyStates[i] = KeyState::KeyDormant;
        KeyHeld[i] = false;

    }
}
float TriangleArea(Vector2 point1, Vector2 point2, Vector2 point3)
{
    return abs((point1.x * (point2.y - point3.y) + point2.x * (point3.y - point1.y) + point3.x * (point1.y - point2.y)) / 2.0);
}
bool IsMouseInTriangle(Vector2 point1, Vector2 point2, Vector2 point3)
{
    Vector2 pos{ (float)MousePos.x,(float)MousePos.y };
    float a = TriangleArea(point1, point2, point3);
    float a1 = TriangleArea(pos, point2, point3);
    float a2 = TriangleArea(point1, pos, point3);
    float a3 = TriangleArea(point1, point2, pos);

    return(a == a1 + a2 + a3);
}
