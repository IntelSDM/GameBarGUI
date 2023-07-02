#include "pch.h"
#include "input.h"
const std::wstring ProcessTitle = L"Overlay";
// 	if ((GetKeyState(VK_RBUTTON) & 0x80) != 0) 
bool CanCollectInput()
{
	wchar_t  title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, title, sizeof(title));

	std::wstring windowTitle(title);
	return windowTitle == ProcessTitle;
}