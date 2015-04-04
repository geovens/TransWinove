#ifndef THREADSWITCH_H
#define THREADSWITCH_H
//#define wxDEBUG_LEVEL 0

#define __WXMSW__
#define WXUSINGDLL
#include "wx/wx.h"

class ThreadSwitch : public wxThread
{
	public:
	ThreadSwitch(TransApp *owner, HWND hwnd = NULL);
	virtual void* Entry();
	bool MessageExit;
	HWND HWndSet;

	private:
	TransApp *Owner;
	bool IsOn;
	bool IsFore;
};

#endif

