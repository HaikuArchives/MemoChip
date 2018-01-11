/////
// MCChipView.cpp
// implement file for MCChipView class
//
// Hideki Naito
// last modified : 2000/10/14
//

#include	<MenuItem.h>
#include	<string.h>
#include	"MCApp.h"
#include	"MCChipView.h"
#include	"MCMsgConst.h"


/////
// constants
//

#define	DBLCLICK_SPEED	150000


/////
// constructor for MCChipView class
//
MCChipView::MCChipView(
	BRect	frame)
	: BTextView(frame, "mcchipview", frame, B_FOLLOW_ALL, B_WILL_DRAW),
	prev_click(0)
{
	this->MakeEditable(false);
}


/////
// set MemoChip data
//
void MCChipView::SetData(
	MCDataDetail	*data)
{
	BFont	font;

	// set MemoChip data
	this->GetFont(&font);
	font.SetFamilyAndStyle(data->family, NULL);
	font.SetSize((float) data->fsize);
	this->SetFontAndColor(&font);
	this->SetViewColor(data->ccolor);
	this->SetText(data->data);
	this->Invalidate();
}


/////
// get MemoChip data
//
void MCChipView::GetData(
	MCDataDetail	*data)
{
	BFont		font;
	font_style	fstyle;
	char		*work;

	this->GetFont(&font);
	font.GetFamilyAndStyle(&(data->family), &fstyle);
	data->fsize = (int32) font.Size();
	data->ccolor = this->ViewColor();
	work = (char*) this->Text();
	data->data = new char[strlen(work) + 1];
	strcpy(data->data, work);
}


/////
// frame resize hook
//
void MCChipView::FrameResized(
	float	width,
	float	height)
{
	BRect	rect(this->TextRect());
	rect.right = rect.left + width;
	this->SetTextRect(rect);
}


/////
// mouse down on this view
//
void MCChipView::MouseDown(
	BPoint	point)
{
	int32	i;
	uint32	button;

	// check clicked button
	this->Window()->CurrentMessage()->FindInt32("buttons", &i);
	button = i;

	if(button == B_PRIMARY_MOUSE_BUTTON)
	{
		// check double-click (to edit)
		bigtime_t	curr_click = system_time();
		this->Window()->CurrentMessage()->FindInt32("clicks", &i);

		if(((curr_click - this->prev_click) < DBLCLICK_SPEED)
			&& (((MCApp *) be_app)->IsEnableDblClk() == true))
		{
			BMessage	*msg;

			msg = new BMessage(MSG_CHIPEDIT);
			msg->AddInt32("tabindex", 0);
			this->Window()->PostMessage(msg);
			this->prev_click = 0;
		}
		else
		{
			BPoint	old;
			this->ConvertToScreen(&point);
			old = point;
			while(button == B_PRIMARY_MOUSE_BUTTON)
			{
				if(old != point)
				{
					this->Window()->Lock();
					this->Window()->MoveBy((point.x - old.x),
						(point.y - old.y));
					this->Window()->Unlock();
				}
				old = point;
				snooze(20000);
				this->GetMouse(&point, &button);
				this->ConvertToScreen(&point);
			}
			this->prev_click = curr_click;
		}
	}
	else if(button == B_SECONDARY_MOUSE_BUTTON)
	{
		// show chip menu
		BPopUpMenu	*pmenu;
		pmenu = this->createPopUpMenu();

		BMenuItem	*item;
		BMessage	*msg;
		this->ConvertToScreen(&point);
		item = NULL;
		item = pmenu->Go(point, false, false,
			BRect((point.x - 3), (point.y - 3), (point.x + 3), (point.y + 3)));
		if(item != NULL)
		{
			msg = item->Message();
			if(msg != NULL);
			{
				this->Window()->PostMessage(msg);
			}
		}
		delete pmenu;
	}
}


/////
// create chip edit menu
//
BPopUpMenu *MCChipView::createPopUpMenu()
{
	BMessage	*msg;
	BMenuItem	*item;
	BPopUpMenu	*pmenu;

	pmenu = new BPopUpMenu("chipmenu");

	msg = new BMessage(MSG_CHIPEDIT);
	msg->AddInt32("tabindex", 0);
	item = new BMenuItem("Edit", msg);
	pmenu->AddItem(item);

	pmenu->AddSeparatorItem();

	msg = new BMessage(MSG_CHIPEDIT);
	msg->AddInt32("tabindex", 1);
	item = new BMenuItem("Font", msg);
	pmenu->AddItem(item);

	msg = new BMessage(MSG_CHIPEDIT);
	msg->AddInt32("tabindex", 2);
	item = new BMenuItem("Color", msg);
	pmenu->AddItem(item);

	msg = new BMessage(MSG_CHIPEDIT);
	msg->AddInt32("tabindex", 3);
	item = new BMenuItem("Option", msg);
	pmenu->AddItem(item);

	pmenu->AddSeparatorItem();

	msg = new BMessage(MSG_COPYCLIP);
	item = new BMenuItem("Copy", msg);
	pmenu->AddItem(item);

	pmenu->AddSeparatorItem();

	item = new BMenuItem("Tear off", new BMessage(B_QUIT_REQUESTED));
	pmenu->AddItem(item);
	
	return pmenu;
}
