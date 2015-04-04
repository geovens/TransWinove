#ifndef TRANSAPP_H
#define TRANSAPP_H
//#define wxDEBUG_LEVEL 0
#define wxCURSOR(X) wxCursor(wxT(#X))

#define __WXMSW__
#define WXUSINGDLL
#include "wx/wx.h"

class TransApp : public wxApp
{
	public:
	TransApp();
	virtual bool OnInit();
	void LeftClick();
	void RightClick();
	void WaitMouseClick();
	void Quit();

	void SetNoHitTrans(HWND hwnd, unsigned char trancoif);
	void SetHitTrans(HWND hwnd, unsigned char trancoif);
	void SetUnTrans(HWND hwnd, bool setbottom = false);

	bool IfNoHit;
	bool ThreadWaitInactiveIsRuning;

	private:
	void Cancel(bool setbottom = false);
	class TaskBarIcon *aTaskBarIcon;
	class ThreadSwitch *aThreadSwitch;
	class ThreadWaitInactive *aThreadWaitInactive;

	HWND TransWin;
	HWND ForbidWin1;
	HWND ForbidWin2;
};

DECLARE_APP(TransApp)

#endif
