
#include "TransApp.h"
#include "TaskBarIcon.h"
#include "PopUpMenu.h"
#include "ThreadSwitch.h"
#include "ThreadWaitInactive.h"
#include "windows.h"
//#include "resource.h"

IMPLEMENT_APP(TransApp)

TransApp::TransApp()
{
	TransWin = (HWND)0;
	//IsWaitingMouseClick = false;
	//ExitMessage = false;
	IfNoHit = true;
}

bool TransApp::OnInit()
{
	ForbidWin1 = FindWindowW(L"Shell_TrayWnd", L"");
	ForbidWin2 = FindWindowW(L"NotifyIconOverflowWindow", L"");
	aTaskBarIcon = new TaskBarIcon(this);

	return true;
}

void TransApp::LeftClick()
{
	if (TransWin == 0)
	{
		WaitMouseClick();
	}
	else
	{
		if (IfNoHit)
		{
			ThreadWaitInactiveIsRuning = true;
			SetUnTrans(TransWin);
			//SetHitTrans(TransWin, 0xE0);
			SetForegroundWindow(TransWin);
			aThreadWaitInactive = new ThreadWaitInactive(this, TransWin);
			aThreadWaitInactive->Create();
			aThreadWaitInactive->Run();
		}
	}
}

void TransApp::RightClick()
{
	if (TransWin != 0)
	{
		Sleep(100);
		Cancel(false);
	}
	else
	{
		PopUpMenu *menu = new PopUpMenu(this);
		aTaskBarIcon->PopupMenu(menu);
	}
}

void TransApp::Quit()
{
	//ExitMessage = true;
	Sleep(200);
	aTaskBarIcon->RemoveIcon();
	//taskbar->Destroy();
	wxExit();
}

void TransApp::WaitMouseClick()
{
	aTaskBarIcon->SelectIcon(2);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32512);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32650);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32514);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32513);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32649);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32642);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32643);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32644);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32645);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32646);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32648);
	SetSystemCursor((HCURSOR)wxCURSOR(IDC_CURSOR).GetHCURSOR(), 32516);

	int waittick = 0;
	HWND hwnd;
	bool LeftIsClicked = false;
	bool RightIsClicked = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			LeftIsClicked = true;
		}
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000) && LeftIsClicked)
		{
			POINT mousepoint;
			GetCursorPos(&mousepoint);
			hwnd = WindowFromPoint(mousepoint);
			hwnd = GetAncestor(hwnd, GA_ROOT);
			if (hwnd != 0 && hwnd != ForbidWin1 && hwnd != ForbidWin2)
			{
				//wchar_t s[200];
				//GetClassNameW(hwnd, s, 100);
				//wxMessageBox(s);
				if (IfNoHit)
				{
					SetNoHitTrans(hwnd, 0x60);
					aThreadSwitch = new ThreadSwitch(this, hwnd);
					aThreadSwitch->Create();
					aThreadSwitch->Run();
				}
				else
				{
					SetHitTrans(hwnd, 0xD0);
					aThreadSwitch = new ThreadSwitch(this, hwnd);
					aThreadSwitch->Create();
					aThreadSwitch->Run();
				}
				aTaskBarIcon->SelectIcon(3);
				TransWin = hwnd;
				waittick = 0;
			}
			else
				aTaskBarIcon->SelectIcon(1);
			break;
		}
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			LeftIsClicked = false;
			RightIsClicked = true;
		}
		if (!(GetAsyncKeyState(VK_RBUTTON) & 0x8000) && RightIsClicked)
		{
			aTaskBarIcon->SelectIcon(1);
			break;
		}

		waittick++;
		if (waittick >= 15)
		{
			aTaskBarIcon->SelectIcon(12);
			waittick = 1;
		}

		Sleep(20);
	}

	SystemParametersInfo(SPI_SETCURSORS, 0, 0, 0);
	//IsWaitingMouseClick = false;
}

void TransApp::Cancel(bool setbottom)
{
	if (TransWin != 0)
	{
		aThreadSwitch->MessageExit = true;
		Sleep(50);
		if (ThreadWaitInactiveIsRuning)
		{
			aThreadWaitInactive->MessageExit = true;
		}
		SetUnTrans(TransWin, false);
		aTaskBarIcon->SelectIcon(1);
		TransWin = 0;
	}
}

void TransApp::SetUnTrans(HWND hwnd, bool setbottom)
{
	DWORD dwExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, dwExStyle & ~WS_EX_LAYERED & ~WS_EX_TRANSPARENT);
	if (setbottom)
		SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	else
		SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void TransApp::SetNoHitTrans(HWND hwnd, unsigned char trancoif)
{
	DWORD dwExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), trancoif, LWA_ALPHA);
	SetWindowLong(hwnd, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void TransApp::SetHitTrans(HWND hwnd, unsigned char trancoif)
{
	DWORD dwExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), trancoif, LWA_ALPHA);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}



