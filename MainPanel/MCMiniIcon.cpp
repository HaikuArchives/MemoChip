/////
// MCMiniIcon.cpp
// implement file for MCMiniIcon class
//
// Hideki Naito
// last modified : 2000/10/13
//

#include	<Roster.h>
#include	<MenuItem.h>
#include	"MCMiniIcon.h"
#include	"MCMsgConst.h"


/////
// constants
//

// transparent color
#define	TRAN			B_TRANSPARENT_8_BIT


/////
// icon bitmap
//
unsigned char pat[] =
{
	TRAN, TRAN, 0x10, 0x10, 0x00, 0x00, 0x00, TRAN,
	TRAN, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN,
	TRAN, 0x10, 0x25, 0x25, 0x10, 0x10, 0x10, 0x00,
	0x00, 0x00, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN,
	TRAN, 0x10, 0x25, 0x7e, 0x7e, 0x25, 0x25, 0x10,
	0x10, 0x10, 0x00, 0x00, 0x00, TRAN, TRAN, TRAN,
	TRAN, 0x10, 0x25, 0x7e, 0x56, 0x39, 0x20, 0x20,
	0x25, 0x25, 0x10, 0x10, 0x10, 0x00, 0x00, TRAN,
	TRAN, 0x10, 0x25, 0x20, 0x56, 0x56, 0x56, 0x39,
	0x20, 0x20, 0x20, 0x25, 0x25, 0x10, 0x00, TRAN,
	TRAN, 0x10, 0x25, 0x20, 0x56, 0x56, 0x56, 0x39,
	0x20, 0x20, 0x20, 0x20, 0x25, 0x10, 0x00, TRAN,
	TRAN, 0x10, 0x25, 0x20, 0x20, 0x20, 0x56, 0x39,
	0x20, 0x20, 0xdb, 0xdb, 0x25, 0x10, 0x00, TRAN,
	TRAN, 0x10, 0xfb, 0x8b, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0xdb, 0xdb, 0xdb, 0x10, 0x00, TRAN,
	TRAN, 0x10, 0xfb, 0xfb, 0xfb, 0x8b, 0x20, 0x20,
	0x20, 0x20, 0xba, 0xdb, 0xdb, 0x10, 0x00, TRAN,
	TRAN, 0x10, 0xfb, 0xfb, 0xfb, 0x8b, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x25, 0xba, 0x20, 0x00, TRAN,
	TRAN, 0x10, 0x20, 0x8b, 0xfb, 0x8b, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x25, 0x10, 0x00, TRAN,
	TRAN, 0x10, 0x25, 0x25, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x25, 0x25, 0x10, 0x00, TRAN,
	TRAN, TRAN, 0x10, 0x10, 0x10, 0x25, 0x25, 0x20,
	0x20, 0x20, 0x25, 0x20, 0x25, 0x10, 0x00, TRAN,
	TRAN, TRAN, TRAN, TRAN, TRAN, 0x10, 0x10, 0x10,
	0x25, 0x25, 0x20, 0x25, 0x25, 0x10, 0x00, TRAN,
	TRAN, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN,
	0x10, 0x10, 0x10, 0x25, 0x25, 0x10, 0x00, TRAN,
	TRAN, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN, TRAN,
	TRAN, TRAN, TRAN, 0x10, 0x10, TRAN, TRAN, TRAN
};


/////
// signatures
//
extern const char *app_sig;
extern const char *db_sig;


/////
// constructor for MCMiniIcon class
//
MCMiniIcon::MCMiniIcon(
	BRect	frame)
	: BView(frame, "mcminiicon", (B_FOLLOW_LEFT | B_FOLLOW_TOP), B_WILL_DRAW)
{
	this->icon = NULL;
}


/////
// constructor for MCMiniIcon(for Replicant)
//
MCMiniIcon::MCMiniIcon(
	BMessage	*msg)
	: BView(msg)
{
	BRect	rect(0, 0, 15, 15);
	this->icon = new BBitmap(rect, B_COLOR_8_BIT);
	this->icon->SetBits(pat, 256, 0, B_COLOR_8_BIT);
}


/////
// destructor for MCMiniIcon
//
MCMiniIcon::~MCMiniIcon()
{
	delete this->icon;
}


/////
// instanciate this view(for Replicant)
//
MCMiniIcon *MCMiniIcon::Instantiate(
	BMessage	*data)
{
	if(validate_instantiation(data, "MCMiniIcon") == false)
	{
		return NULL;
	}
	return new MCMiniIcon(data);
}


/////
// archiving object(for Replicant)
//
status_t MCMiniIcon::Archive(
	BMessage	*data,
	bool		deep) const
{
	BView::Archive(data, deep);
	data->AddString("add_on", app_sig);
	return B_NO_ERROR;
}


/////
// mouse button down hook
//
void MCMiniIcon::MouseDown(
	BPoint	point)
{
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
		if(msg != NULL)
		{
			BMessenger	*mgr;
			mgr = new BMessenger(app_sig);
			mgr->SendMessage(msg);
			delete mgr;
		}
	}
	delete pmenu;
}


/////
// redraw hook
//
void MCMiniIcon::Draw(
	BRect	rect)
{
	this->DrawBitmap(this->icon);
	return;
}


/////
// view attached to window
//
void MCMiniIcon::AttachedToWindow()
{
	this->SetViewColor(this->Parent()->ViewColor());
	this->SetDrawingMode(B_OP_ALPHA);
}


/////
// create chip edit menu
//
BPopUpMenu *MCMiniIcon::createPopUpMenu()
{
	BMenuItem	*item;
	BPopUpMenu	*pmenu;

	pmenu = new BPopUpMenu("chipmenu");

	item = new BMenuItem("New Chip", new BMessage(MSG_NEWCHIP));
	pmenu->AddItem(item);
	item = new BMenuItem("Preference", new BMessage(MSG_PREFERENCE));
	pmenu->AddItem(item);
	pmenu->AddSeparatorItem();
	item = new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED));
	pmenu->AddItem(item);
	return pmenu;
}
