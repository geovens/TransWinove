
#include "TransApp.h"
#include "PopUpMenu.h"

BEGIN_EVENT_TABLE(PopUpMenu, wxMenu)
	EVT_MENU(1, PopUpMenu::OnMenu)
	EVT_MENU(2, PopUpMenu::OnMenu)
	EVT_MENU(3, PopUpMenu::OnMenu)
END_EVENT_TABLE()

PopUpMenu::PopUpMenu(TransApp *owner) : wxMenu()
{
	Owner = owner;
	ItemGhost = AppendCheckItem(2, L"Ghost Mode", L"Set the selected window invisible to mouse.");
	ItemPin = AppendCheckItem(3, L"Pin Mode", L"set the selected window always on top.");
	Append(1, L"Exit", L"Quit TransWinove.");

	if (Owner->IfNoHit)
	{
		ItemGhost->Check(true);
		ItemPin->Check(false);
	}
	else
	{
		ItemGhost->Check(false);
		ItemPin->Check(true);
	}

}

void PopUpMenu::OnMenu(wxCommandEvent &event)
{
	if (event.GetId() == 3)
	{
		Owner->IfNoHit = false;
		ItemGhost->Check(false);
		ItemPin->Check(true);
	}
	else if (event.GetId() == 2)
	{
		Owner->IfNoHit = true;
		ItemGhost->Check(true);
		ItemPin->Check(false);
	}
	else if (event.GetId() == 1)
		Owner->Quit();
}
