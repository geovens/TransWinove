#ifndef THREADWAITINACTIVE_H
#define THREADWAITINACTIVE_H
//#define wxDEBUG_LEVEL 0

#define __WXMSW__
#define WXUSINGDLL
#include "wx/wx.h"

class ThreadWaitInactive : public wxThread
{
	public:
	ThreadWaitInactive(TransApp *owner, HWND hwnd = NULL);
	virtual void* Entry();
	bool MessageExit;
	HWND HWndSet;

	private:
	TransApp *Owner;
};

#endif

