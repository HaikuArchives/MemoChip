/////
// MCMainView.cpp
// implement file for MCMainView class
//
// Hideki Naito
// last modified : 1999/01/15
//

#include	<Application.h>
#include	<Button.h>
#include	"MCMainView.h"
#include	"MCMsgConst.h"


/////
// constructor for MCMainView class
//
MCMainView::MCMainView(
	BRect	frame)
	: BView(frame, "mcmainview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	BButton	*btn;

	// create 'New Chip' button
	btn = new BButton(BRect(5, 1, 96, 24), "newchipbtn",
		"New Chip", new BMessage(MSG_NEWCHIP));
	this->AddChild(btn);
	// create 'Preference' button
	btn = new BButton(BRect(5, 26, 96, 49), "prefbtn",
		"Preference", new BMessage(MSG_PREFERENCE));
	this->AddChild(btn);
}


/////
// view attached to window
//
void MCMainView::AttachedToWindow()
{
	BButton	*btn;

	btn = (BButton*) this->FindView("newchipbtn");
	btn->SetTarget(be_app);
	btn = (BButton*) this->FindView("prefbtn");
	btn->SetTarget(be_app);
}
