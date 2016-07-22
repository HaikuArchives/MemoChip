/////
// MCPrefViewAbst.cpp
// implement file for MCPrefViewAbst class
//
// Hideki Naito
// last modified : 1999/12/15
//

#include	<Button.h>
#include	"MCPrefViewAbst.h"
#include	"MCMsgConst.h"


/////
// constructor for MCPrefViewAbst class
//
MCPrefViewAbst::MCPrefViewAbst(
	BRect		frame,
	const char	*name)
	: BView(frame, name, B_FOLLOW_ALL, B_WILL_DRAW)
{
	BRect	rect;
	BButton	*button;

	// create pref tab
	rect = this->Bounds();
	rect.bottom -= 30;
	rect.InsetBy(5, 5);

	this->tview = new BTabView(rect, "tabview");

	// create Set/Cancel button
	float	by;
	by = rect.bottom + 5;
	button = new BButton(BRect(305, by, 355, (by + 20)), "setbtn",
		"Set", new BMessage(MSG_PREFSET),
		(B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM));
	this->AddChild(button);

	button = new BButton(BRect(365, by, 415, (by + 20)), "cancelbtn",
		"Cancel", new BMessage(B_QUIT_REQUESTED),
		(B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM));
	this->AddChild(button);
}


/////
// view attached to window
//
void MCPrefViewAbst::AttachedToWindow()
{
	this->SetViewColor(220, 220, 220, 255);
}
