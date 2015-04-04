
#include "TransApp.h"
#include "ThreadWaitInactive.h"

ThreadWaitInactive::ThreadWaitInactive(TransApp *owner, HWND hwnd) : wxThread()
{
	Owner = owner;
	HWndSet = hwnd;
	MessageExit = false;
}

void* ThreadWaitInactive::Entry()
{
	HWND hwnd;
	while (!MessageExit)
	{
		hwnd = GetForegroundWindow();
		if (hwnd != HWndSet)
		{
			//wxMessageBox(L"1");
			Owner->SetNoHitTrans(HWndSet, 0xD0);
			break;
		}
		Sleep(20);
	}
	Owner->ThreadWaitInactiveIsRuning = false;
	return NULL;
}
