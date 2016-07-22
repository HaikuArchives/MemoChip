/////
// MCDummyWin.cpp
// implement file for MCDummyWin class
//
// Hideki Naito
// last modified : 1999/07/12
//

#include	<Screen.h>
#include	"MCDummyWin.h"


/////
// constructor for MCDummyWin class
//
MCDummyWin::MCDummyWin(
	BRect	frame)
	: BWindow(frame, "_skywalker_", B_BORDERED_WINDOW, B_NOT_MOVABLE)
{
}


/////
// workspace changed
//
void MCDummyWin::WorkspaceActivated(
	int32	ws,
	bool	active)
{
	if(active == false)
	{
		BRect	rect;
		this->SetWorkspaces(1 << current_workspace());

		rect = BScreen().Frame();
		this->MoveTo((float) rect.right, (float) rect.bottom);
	}
}


/////
// Screen settings changed
//
void MCDummyWin::ScreenChanged(
	BRect		frame,
	color_space	mode)
{
	this->MoveTo((float) frame.right, (float) frame.bottom);
}
