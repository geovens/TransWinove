#ifndef TASKBARICON_H
#define TASKBARICON_H
//#define wxDEBUG_LEVEL 0

#define __WXMSW__
#define WXUSINGDLL
#include "wx/wx.h"
#include "wx/taskbar.h"

class TaskBarIcon : public wxTaskBarIcon
{
	public:
	TaskBarIcon(TransApp *owner);
	~TaskBarIcon();
	void SelectIcon(int icon);

	private:
	TransApp *Owner;
	int IconNow;

	DECLARE_EVENT_TABLE();
	void LeftClick(wxTaskBarIconEvent &event);
	void RightClick(wxTaskBarIconEvent &event);
};

#endif
