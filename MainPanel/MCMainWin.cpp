/////
// MCMainWin.cpp
// implement file for MCMainWin class
//
// Hideki Naito
// last modified : 1999/01/24
//

#include	<Application.h>
#include	"MCMainWin.h"
#include	"MCMainView.h"
#include	"MCMsgConst.h"


/////
// constructor for MCMainWin class
//
MCMainWin::MCMainWin(
	BRect	frame,
	bool	fws)
	: BWindow(frame, "MemoChip", B_TITLED_WINDOW,
		(B_NOT_RESIZABLE | B_NOT_ZOOMABLE))
{
	MCMainView	*cview;

	this->ffws = fws;
	this->isQuit = false;

	cview = new MCMainView(this->Bounds());
	this->AddChild(cview);
}


/////
// mainpanel close
//
bool MCMainWin::QuitRequested()
{
	if(this->isQuit == false)
	{
		this->isQuit = true;
		be_app->PostMessage(B_QUIT_REQUESTED);
		return false;
	}

	return true;
}


/////
// workspace changed
//
void MCMainWin::WorkspaceActivated(
	int32	ws,
	bool	active)
{
	if(this->ffws == false)
	{
		return;
	}

	if(active == false)
	{
		this->SetWorkspaces(1 << current_workspace());
	}
}
