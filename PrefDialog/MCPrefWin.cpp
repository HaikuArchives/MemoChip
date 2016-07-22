/////
// MCPrefWin.cpp
// implement file for MCPrefWin class
//
// Hideki Naito
// last modified : 1999/12/05
//

#include	"MCPrefWin.h"
#include	"MCApp.h"
#include	"MCMsgConst.h"


/////
// constructor for MCPrefWin class
//
MCPrefWin::MCPrefWin(
	BRect			frame,
	MCPrefViewAbst	*view)
	: BWindow(frame, "prefwin", B_MODAL_WINDOW,
	0)
//		(B_NOT_RESIZABLE | B_NOT_ZOOMABLE))
{
	this->cview = view;
	this->AddChild(view);
}


/////
// quit request hook
//
bool MCPrefWin::QuitRequested()
{
	((MCApp*) be_app)->isOpenPref = false;
	return true;
}


/////
// message handler
//
void MCPrefWin::MessageReceived(
	BMessage	*msg)
{
	switch(msg->what)
	{
		case MSG_PREFSET:
		{
			cview->PrefSet();
			break;
		}
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}
