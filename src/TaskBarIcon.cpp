
#include "TransApp.h"
#include "TaskBarIcon.h"
//#include "resource.h"

BEGIN_EVENT_TABLE(TaskBarIcon, wxTaskBarIcon)
	EVT_TASKBAR_LEFT_UP(TaskBarIcon::LeftClick)
   EVT_TASKBAR_RIGHT_UP(TaskBarIcon::RightClick)
END_EVENT_TABLE()

TaskBarIcon::TaskBarIcon(TransApp *owner) : wxTaskBarIcon()
{
	Owner = owner;
	SelectIcon(1);
}

TaskBarIcon::~TaskBarIcon()
{
}

void TaskBarIcon::SelectIcon(int icon)
{
	if (icon == 1)
	{
		SetIcon(wxICON(IDI_GREEN));
		IconNow = 1;
	}
	else if (icon == 2)
	{
		SetIcon(wxICON(IDI_GREENBLANK));
		IconNow = 2;
	}
	else if (icon == 3)
	{
		SetIcon(wxICON(IDI_RED));
		IconNow = 3;
	}
	else if (icon == 12)
	{
		if (IconNow == 1)
		{
			SetIcon(wxICON(IDI_GREENBLANK));
			IconNow = 2;
		}
		else if (IconNow == 2)
		{
			SetIcon(wxICON(IDI_GREEN));
			IconNow = 1;
		}
	}
}

void TaskBarIcon::LeftClick(wxTaskBarIconEvent &event)
{
	Owner->LeftClick();
}

void TaskBarIcon::RightClick(wxTaskBarIconEvent &event)
{
	Owner->RightClick();
}


