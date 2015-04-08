
#include "TransApp.h"
#include "ThreadSwitch.h"
#include "flowgraph.h"

ThreadSwitch::ThreadSwitch(TransApp *owner, HWND hwnd) : wxThread()
{
	Owner = owner;
	HWndSet = hwnd;
	MessageExit = false;
}

void* ThreadSwitch::Entry()
{
	while (!MessageExit)
	{
		POINT mousepoint;
		RECT rect;
		GetCursorPos(&mousepoint);
		GetWindowRect(HWndSet, &rect);
		bool on = false;
		if (mousepoint.x > rect.left && mousepoint.x < rect.right && mousepoint.y > rect.top && mousepoint.y < rect.bottom)
			on = true;

		mousepoint.x -= 3;
		mousepoint.y -= 3;
		HWND point00 = WindowFromPoint(mousepoint);
		mousepoint.x += 6;
		HWND point01 = WindowFromPoint(mousepoint);
		mousepoint.y += 6;
		HWND point11 = WindowFromPoint(mousepoint);
		mousepoint.x -= 6;
		HWND point10 = WindowFromPoint(mousepoint);

		int firefox = 0;
		wchar_t text[256];
		HWND fore = GetForegroundWindow();
		GetWindowText(fore, text, 256);
		if (std::wstring(text).find(L"Firefox") != std::wstring::npos)
			firefox++;
		GetWindowText(HWndSet, text, 256);
		if (std::wstring(text).find(L"Firefox") != std::wstring::npos)
			firefox++;

		//bool button = false;
		//if (GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON))
		//	button = true;

		if (Owner->IfNoHit)
		{
			if (Owner->ThreadWaitInactiveIsRuning)
				continue;
			if (on && !LastOn)
			{
				Owner->SetNoHitTrans(HWndSet, 0x60);
			}
			else if (!on && LastOn)
			{
				Owner->SetNoHitTrans(HWndSet, 0xD0);
			}
			if (firefox != 2)
			{
				if (on && (point00 != LastPoint00 || point01 != LastPoint01 || point10 != LastPoint10 || point11 != LastPoint11))
				{
					Owner->SetNoHitTrans(HWndSet, 0x60);
				}
				else if (!on && (point00 != LastPoint00 || point01 != LastPoint01 || point10 != LastPoint10 || point11 != LastPoint11))
				{
					Owner->SetNoHitTrans(HWndSet, 0xD0);
				}
				//if (nowon && button != LastButton)
				//{
				//	Sleep(50);
				//	Owner->SetNoHitTrans(HWndSet, 0x60);
				//	LastButton = button;
				//}
				//else if (!nowon && button != LastButton)
				//{
				//	Sleep(50);
				//	Owner->SetNoHitTrans(HWndSet, 0xD0);
				//	LastButton = button;
				//}
			}
		}
		else
		{
			if (on && !LastOn)
			{
				Owner->SetHitTrans(HWndSet, 0xD0);
			}
			else if (!on && LastOn)
			{
				Owner->SetHitTrans(HWndSet, 0xD0);
			}
			if (firefox != 2)
			{
				if (on && (point00 != LastPoint00 || point01 != LastPoint01 || point10 != LastPoint10 || point11 != LastPoint11))
				{
					Owner->SetHitTrans(HWndSet, 0xD0);
				}
				else if (!on && (point00 != LastPoint00 || point01 != LastPoint01 || point10 != LastPoint10 || point11 != LastPoint11))
				{
					Owner->SetHitTrans(HWndSet, 0xD0);
				}
				//if (nowon && button != LastButton)
				//{
				//	Sleep(50);
				//	Owner->SetHitTrans(HWndSet, 0xD0);
				//	LastButton = button;
				//}
				//else if (!nowon && button != LastButton)
				//{
				//	Sleep(50);
				//	Owner->SetHitTrans(HWndSet, 0xD0);
				//	LastButton = button;
				//}
			}
		}

		LastOn = on;
		LastPoint00 = point00;
		LastPoint01 = point01;
		LastPoint10 = point10;
		LastPoint11 = point11;

		Sleep(20);
	}
	return NULL;
}
