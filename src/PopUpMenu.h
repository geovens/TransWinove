#ifndef POPUPMENU_H
#define POPUPMENU_H
//#define wxDEBUG_LEVEL 0

#define __WXMSW__
#define WXUSINGDLL
#include "wx/wx.h"

class PopUpMenu : public wxMenu
{
	public:
	PopUpMenu(TransApp *owner);

	private:
	TransApp *Owner;
	wxMenuItem *ItemGhost;
	wxMenuItem *ItemPin;
	void OnMenu(wxCommandEvent &event);
	DECLARE_EVENT_TABLE();
};

#endif
