#pragma once

extern Vector2 MousePos;
extern std::map<std::string, HCURSOR> Cursors;
extern wchar_t Char;

bool CanCollectInput();
bool IsKeyDown(int key);
bool IsKeyClicked(int key);
void SetInput();
bool IsMouseInRectangle(int x, int y, int width, int height);
bool IsMouseInRectangle(Vector2 pos, Vector2 Dimensions);
bool IsMouseInTriangle(Vector2 point1, Vector2 point2, Vector2 point3);
void UpdateKeyState(int key, bool down);

void SetCurrentCursor(std::string name);
void CreateCursor(std::string name, HCURSOR cursor);
HCURSOR GetCurrentCursor();