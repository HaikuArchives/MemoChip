/////
// MCChipWin.cpp
// implement file for MCChipWin class
//
// Hideki Naito
// last modified : 2000/10/15
//

#include	<Alert.h>
#include	<Clipboard.h>
#include	<string.h>
#include	"MCApp.h"
#include	"MCChipWin.h"
#include	"MCMsgConst.h"


/////
// constructor for MCChipWin class
//
MCChipWin::MCChipWin(
	BRect	frame)
	: BWindow(frame, "chip", B_MODAL_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, 0)
{
	this->ffws = false;
	this->cview = new MCChipView(this->Bounds());
	this->AddChild(cview);
}


/////
// set MemoChip data
//
void MCChipWin::SetData(
	MCDataDetail	*data,
	bool			isLoad)
{
	this->cview->SetData(data);
	this->ffws = data->ffws;
	this->SetTitle(data->name);
	if(isLoad == true)
	{
		this->SetWorkspaces(data->wspace);
		this->MoveTo(data->frame.left, data->frame.top);
		this->ResizeTo(data->frame.Width(), data->frame.Height());
	}
}


/////
// get MemoChip data
//
void MCChipWin::GetData(
	MCDataDetail	*data)
{
	const char	*work;

	this->cview->GetData(data);
	data->wspace = this->Workspaces();
	data->frame = this->Frame();
	data->ffws = this->ffws;
	work = this->Title();
	data->name = new char[strlen(work) + 1];
	strcpy(data->name, work);
}


/////
// quit request hook
//
bool MCChipWin::QuitRequested()
{
	bool		isExitApp;
	status_t	sts;
	
	sts = this->CurrentMessage()->FindBool("isExitApp", &isExitApp);
	if(sts != B_NO_ERROR)
	{
		// confirm before tear off(when option selected)
		if(((MCApp*) be_app)->NeedConfirm() == true)
		{
			int32	bidx;
			BAlert	*confwin;
			confwin = new BAlert("confirm", "Tear off this chip. Sure?",
				"OK", "Cancel", NULL, B_WIDTH_AS_USUAL, B_EVEN_SPACING,
				B_WARNING_ALERT);
			bidx = confwin->Go();
			if(bidx == 1)
			{
				return false;
			}
		}

		// tear off this chip
		BMessage	*msg;
		msg = new BMessage(MSG_TEAROFF);
		msg->AddPointer("window", (void*) this);
		be_app->PostMessage(msg);
		delete msg;
	}
	
	return true;
}


/////
// message handler
//
void MCChipWin::MessageReceived(
	BMessage	*msg)
{
	switch(msg->what)
	{
		case MSG_CHIPEDIT:
		{
			msg->AddPointer("window", (void*) this);
			be_app->PostMessage(msg);
			break;
		}
		case MSG_COPYCLIP:
		{
			MCDataDetail	data;
			BMessage		*clip = NULL;
			this->GetData(&data);

			if(be_clipboard->Lock())
			{
				be_clipboard->Clear();
				if((clip = be_clipboard->Data()))
				{
					clip->AddData("text/plain", B_MIME_TYPE,
						data.data, (strlen(data.data) + 1));
					be_clipboard->Commit();
				}
				be_clipboard->Unlock();
			}
			break;
		}
		default:
		{
			BWindow::MessageReceived(msg);
		}
	}
}


/////
// workspace changed
//
void MCChipWin::WorkspaceActivated(
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
