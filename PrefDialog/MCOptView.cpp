/////
// MCOptView.cpp
// implement file for MCOptView class
//
// Hideki Naito
// last modified : 2000/10/12
//

#include	<CheckBox.h>
#include	"MCOptView.h"


/////
// constants
//

#define	MSG_FOLLOWWORKSPC			'ffws'
#define	MSG_CHIPDEF_FOLLOWWORKSPC	'cdfw'
#define	MSG_SAVEPOS					'spos'
#define	MSG_INDESKBAR				'idsk'
#define	MSG_CONFIRM					'conf'
#define	MSG_ENABLE_DBLCK_EDIT		'edce'


/////
// create all component
//
void MCOptView::createAllComponent()
{
	BCheckBox	*chk;

	// create 'mainpanel follows workspace' checkbox
	chk = new BCheckBox(BRect(20, 20, 200, 40), "fwscheck",
		"mainpanel follows workspace", new BMessage(MSG_FOLLOWWORKSPC));
	if(this->fworkspc == true)
	{
		chk->SetValue(B_CONTROL_ON);
	}
	else
	{
		chk->SetValue(B_CONTROL_OFF);
	}
	this->AddChild(chk);

	// create 'chip default follows workspace' checkbox
	chk = new BCheckBox(BRect(20, 50, 200, 70), "cdfwscheck",
		"chip default follows workspace",
		new BMessage(MSG_CHIPDEF_FOLLOWWORKSPC));
	if(this->fcpdeffws == true)
	{
		chk->SetValue(B_CONTROL_ON);
	}
	else
	{
		chk->SetValue(B_CONTROL_OFF);
	}
	this->AddChild(chk);

	// create 'save mainpanel position' checkbox
	chk = new BCheckBox(BRect(20, 80, 200, 100), "sposcheck",
		"save mainpanel position", new BMessage(MSG_SAVEPOS));
	if(this->fsavepos == true)
	{
		chk->SetValue(B_CONTROL_ON);
	}
	else
	{
		chk->SetValue(B_CONTROL_OFF);
	}
	this->AddChild(chk);

	// create 'install in Deskbar' checkbox
	chk = new BCheckBox(BRect(20, 110, 200, 130), "idskcheck",
		"install in Deskbar", new BMessage(MSG_INDESKBAR));
	if(this->findeskbar == true)
	{
		chk->SetValue(B_CONTROL_ON);
	}
	else
	{
		chk->SetValue(B_CONTROL_OFF);
	}
	this->AddChild(chk);

	// create 'confirm before tear off' checkbox
	chk = new BCheckBox(BRect(20, 140, 200, 160), "confcheck",
		"confirm before tear off", new BMessage(MSG_CONFIRM));
	if(this->fconfirm == true)
	{
		chk->SetValue(B_CONTROL_ON);
	}
	else
	{
		chk->SetValue(B_CONTROL_OFF);
	}
	this->AddChild(chk);

	// create 'enable double-click to edit' checkbox
	chk = new BCheckBox(BRect(20, 170, 200, 190), "edblckcheck",
		"enable double-click to edit", new BMessage(MSG_ENABLE_DBLCK_EDIT));
	if(this->fdblckedit == true)
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
// constructor for MCOptView class
//
MCOptView::MCOptView(
	BRect	frame)
	: BView(frame, "mcoptview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->fworkspc = true;
	this->fcpdeffws = false;
	this->fsavepos = true;
	this->findeskbar = false;
	this->fconfirm = true;
	this->fdblckedit = false;
	this->createAllComponent();
}


/////
// constructor for MCOptView class
//
MCOptView::MCOptView(
	BRect	frame,
	bool	fws,
	bool	fcdfws,
	bool	fsp,
	bool	findsk,
	bool	fconf,
	bool	fdced)
	: BView(frame, "mcoptview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->fworkspc = fws;
	this->fcpdeffws = fcdfws;
	this->fsavepos = fsp;
	this->findeskbar = findsk;
	this->fconfirm = fconf;
	this->fdblckedit = fdced;
	this->createAllComponent();
}


/////
// view attached to window
//
void MCOptView::AttachedToWindow()
{
	BCheckBox	*chk;

	// set view color to parent
	this->SetViewColor(this->Parent()->ViewColor());

	// set target
	chk = (BCheckBox *) this->FindView("fwscheck");
	chk->SetTarget(this);
	chk = (BCheckBox *) this->FindView("cdfwscheck");
	chk->SetTarget(this);
	chk = (BCheckBox *) this->FindView("sposcheck");
	chk->SetTarget(this);
	chk = (BCheckBox *) this->FindView("idskcheck");
	chk->SetTarget(this);
	chk = (BCheckBox *) this->FindView("confcheck");
	chk->SetTarget(this);
	chk = (BCheckBox *) this->FindView("edblckcheck");
	chk->SetTarget(this);
}


/////
// message hook
//
void MCOptView::MessageReceived(
	BMessage	*msg)
{
	BCheckBox	*chk;

	switch(msg->what)
	{
		case MSG_FOLLOWWORKSPC:
		{
			chk = (BCheckBox *) this->FindView("fwscheck");
			this->fworkspc = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		case MSG_CHIPDEF_FOLLOWWORKSPC:
		{
			chk = (BCheckBox *) this->FindView("cdfwscheck");
			this->fcpdeffws = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		case MSG_SAVEPOS:
		{
			chk = (BCheckBox *) this->FindView("sposcheck");
			this->fsavepos = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		case MSG_INDESKBAR:
		{
			chk = (BCheckBox *) this->FindView("idskcheck");
			this->findeskbar = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		case MSG_CONFIRM:
		{
			chk = (BCheckBox *) this->FindView("confcheck");
			this->fconfirm = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		case MSG_ENABLE_DBLCK_EDIT:
		{
			chk = (BCheckBox *) this->FindView("edblckcheck");
			this->fdblckedit = (chk->Value() == B_CONTROL_ON) ? true : false;
			break;
		}
		default:
		{
			BView::MessageReceived(msg);
		}
	}
}
