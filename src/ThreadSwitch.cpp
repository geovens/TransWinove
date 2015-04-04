
#include "TransApp.h"
#include "ThreadSwitch.h"

ThreadSwitch::ThreadSwitch(TransApp *owner, HWND hwnd) : wxThread()
{
	Owner = owner;
	HWndSet = hwnd;
	IsOn = true;
	MessageExit = false;
}

void* ThreadSwitch::Entry()
{
	HWND hwnd;
	while (!MessageExit)
	{
		POINT mousepoint;
		RECT rect;
		GetCursorPos(&mousepoint);
		GetWindowRect(HWndSet, &rect);
		bool nowon = false;
		if (mousepoint.x > rect.left && mousepoint.x < rect.right && mousepoint.y > rect.top && mousepoint.y < rect.bottom)
			nowon = true;

		if (Owner->IfNoHit)
		{
			if (Owner->ThreadWaitInactiveIsRuning)
				continue;
			if (nowon && !IsOn)
			{
				Owner->SetNoHitTrans(HWndSet, 0x60);
				IsOn = true;
			}
			else if (!nowon && IsOn)
			{
				Owner->SetNoHitTrans(HWndSet, 0xD0);
				IsOn = false;
			}
		}
		else
		{
			if (nowon && !IsOn)
			{
				Owner->SetHitTrans(HWndSet, 0xD0);
				IsOn = true;
			}
			else if (!nowon && IsOn)
			{
				Owner->SetHitTrans(HWndSet, 0xD0);
				IsOn = false;
			}
		}
		Sleep(20);
	}
	return NULL;
}
