#include "../Header Files/globals.hh"
#include <Windows.h>


void mouse::Move(float x, float y, float s)
{
	mouse_event(0x0001, x * 10, y * 10, 0, 0);

	Sleep(s * 10);
}

void mouse::click(int holdTime)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(holdTime);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}