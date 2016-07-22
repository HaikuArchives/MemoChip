/////
// MCChipOptView.cpp
// implement file for MCChipOptView class
//
// Hideki Naito
// last modified : 1999/12/28
//

#include	<CheckBox.h>
#include	"MCChipOptView.h"


/////
// constants
//

#define	MSG_CP_FOLLOWWRKSPC	'cfws'


/////
// create all component
//
void MCChipOptView::createAllComponent()
{
	BCheckBox	*chk;

	// create 'chip name' textbox
	this->nametext = new BTextControl(BRect(20, 20, 250, 36), "cpnametxt",
		"chip name :", NULL, NULL);
	this->nametext->SetDivider(60);
	this->AddChild(this->nametext);

	// create 'follow workspace' checkbox
	chk = new BCheckBox(BRect(20, 50, 200, 70), "cpfwscheck",
		"chip follows workspace", new BMessage(MSG_CP_FOLLOWWRKSPC));
	if(this->fworkspc == true)
	{
		chk->SetValue(B_CONTROL_ON);
	}
	else
	{
		chk->SetValue(B_CONTROL_OFF);
	}
	this->AddChild(chk);
}


/////
// constructor for MCChipOptView class
//
MCChipOptView::MCChipOptView(
	BRect	frame)
	: BView(frame, "mcchipoptview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->fworkspc = false;
	this->createAllComponent();
}


/////
// constructor for MCChipOptView class
//
MCChipOptView::MCChipOptView(
	BRect	frame,
	bool	fws)
	: BView(frame, "mcchipoptview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->fworkspc = fws;
	this->createAllComponent();
}


/////
// view attached to window
//
void MCChipOptView::AttachedToWindow()
{
	BCheckBox	*chk;

	// set view color to parent
	this->SetViewColor(this->Parent()->ViewColor());

	// set target
	chk = (BCheckBox *) this->FindView("cpfwscheck");
	chk->SetTarget(this);
}


/////
// message hook
//
void MCChipOptView::MessageReceived(
	BMessage	*msg)
{
	BCheckBox	*chk;

	switch(msg->what)
	{
		case MSG_CP_FOLLOWWRKSPC:
		{
			chk = (BCheckBox *) this->FindView("cpfwscheck");
			this->fworkspc = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		default:
		{
			BView::MessageReceived(msg);
		}
	}
}
