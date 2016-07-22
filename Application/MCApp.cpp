/////
// MCApp.cpp
// implement file for MCApp class
//
// Hideki Naito
// last modified : 2000/10/12
//

#include	<Path.h>
#include	<Directory.h>
#include	<Screen.h>
#include	<File.h>
#include	<Deskbar.h>
#include	<FindDirectory.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"MCApp.h"
#include	"MCArchive.h"
#include	"MCMiniIcon.h"
#include	"MCPrefWin.h"
#include	"MCChipPrefView.h"
#include	"MCMainPrefView.h"
#include	"MCMsgConst.h"


/////
// signatures
//
const char *app_sig = "application/x-vnd.wbAPPS-MemoChip";	// this application


/////
// constants
//

#define	MP_WIDTH	103		// mainpanel size
#define	MP_HEIGHT	52

#define	MC_WIDTH	200		// default MemoChip size
#define	MC_HEIGHT	60

#define	PW_WIDTH	420		// preference window size
#define	PW_HEIGHT	290


/////
// constructor for MCApp class
//
MCApp::MCApp()
	: BApplication(app_sig), icon_id(0)
{
}


/////
// application ready
//
void MCApp::ReadyToRun()
{
	status_t		sts;
	BPath			path;
	BFile			file;
	BRect			rect;
	MCDataHeader	head;
	MCDataDetail	data;
	char			df[B_PATH_NAME_LENGTH];

	this->target = NULL;

	// show dummy window(for guarantee, recognize current workspace)
	rect = BScreen().Frame();
	rect.left = rect.right;
	rect.top = rect.bottom;
	this->dummy = new MCDummyWin(rect);
	this->dummy->Show();

	// read memochip data
	sts = find_directory(B_USER_CONFIG_DIRECTORY, &path);
	if(sts != B_NO_ERROR) goto ERR;

	sprintf(df, "%s%s", path.Path(), "/settings/wbAPPS/MemoChip.dat");
	sts = file.SetTo(df, B_READ_ONLY);
	if(sts == B_NO_ERROR)
	{// read memochip data
		MCArchive	*arc;
		arc = new MCArchive();
		arc->Unflatten(&file);

		// get header info
		arc->FindChipHeader(&head);
		this->ffws = head.ffws;
		this->fcdfws = head.fcdfws;
		this->fspos = head.fspos;
		this->findeskbar = head.findeskbar;
		this->fconfirm = head.fconfirm;
		this->fdblckedit = head.fdblckedit;
		strcpy(this->defset.family, head.family);
		this->defset.fsize = head.fsize;
		this->defset.ccolor = head.ccolor;

		// create and show memochip
		int32	cw;
		cw = current_workspace();	// backup current workspace
		for(int32 i = 0; i < head.numchips; ++i)
		{
			arc->FindChipData(i, &data);
			this->createMemoChip(&data, true);
		}
		activate_workspace(cw);		// restore workspace

		// create and show mainpanel
		arc->FindRect("mpos", &(this->oldrect));

		this->mainpanel = new MCMainWin(this->oldrect, head.ffws);

		if(this->findeskbar == false)
		{
			this->mainpanel->Show();
		}
		else
		{
			this->installInDeskbar();
		}
	}
	else
	{// first memochip exec
		// set default info
		this->ffws = true;
		this->fcdfws = false;
		this->fspos = true;
		this->findeskbar = false;
		this->fconfirm = true;
		this->fdblckedit = false;

		font_family	ff;
		font_style	fs;
		be_plain_font->GetFamilyAndStyle(&ff, &fs);
		strcpy(this->defset.family, ff);
		this->defset.fsize = 10;

		this->defset.ccolor.red = 255;
		this->defset.ccolor.green = 255;
		this->defset.ccolor.blue = 255;
		this->defset.ccolor.alpha = 255;

		// create and show mainpanel
		this->oldrect = BScreen().Frame();
		this->oldrect.left = (this->oldrect.Width() - MP_WIDTH) / 2;
		this->oldrect.top = (this->oldrect.Height() - MP_HEIGHT) / 2;
		this->oldrect.right = this->oldrect.left + MP_WIDTH - 1;
		this->oldrect.bottom = this->oldrect.top + MP_HEIGHT - 1;

		this->mainpanel = new MCMainWin(this->oldrect);
		this->mainpanel->Show();
	}

ERR:
	return;
}


/////
// message handler
//
void MCApp::MessageReceived(
	BMessage	*msg)
{
	switch(msg->what)
	{
		case MSG_NEWCHIP:
		{
			this->target = NULL;
			this->callMemoChipPref();
			break;
		}
		case MSG_PREFERENCE:
		{
			this->callMainPref();
			break;
		}
		case MSG_CHIPEDIT:
		{
			int32	tabidx;
			msg->FindPointer("window", (void**) &(this->target));
			msg->FindInt32("tabindex", &tabidx);
			this->callMemoChipPref(tabidx);
			break;
		}
		case MSG_TEAROFF:
		{
			MCChipWin	*win;
			msg->FindPointer("window", (void**) &win);
			this->tearOffMemoChip(win);
			break;
		}
		case MSG_SETOPTION:
		{
			MCDataHeader	*head;
			msg->FindPointer("data", (void**) &head);
			this->setOption(head);
			break;
		}
		case MSG_SETCHIPDATA:
		{
			MCDataDetail	*data;
			msg->FindPointer("data", (void**) &data);
			this->setChipData(data);
			break;
		}
		default:
		{
			BApplication::MessageReceived(msg);
			break;
		}
	}
}


/////
// application quit request hook
//
bool MCApp::QuitRequested()
{
	this->appExit(this->mainpanel->Frame());
	this->mainpanel->PostMessage(B_QUIT_REQUESTED);
	this->dummy->PostMessage(B_QUIT_REQUESTED);
	this->removeFromDeskbar();

	return true;
}


/////
// create and show memochip
//
void MCApp::createMemoChip(
	MCDataDetail	*data,
	bool			isLoad = false)
{
	MCChipWin	*win;
	win = new MCChipWin(data->frame);
	this->chips.AddItem((void*) win);

	win->SetData(data, isLoad);
	win->SetTitle(data->name);
	win->Show();
}


/////
// MemoChip preference call
//
void MCApp::callMemoChipPref(
	int32	tabidx)
{
	BRect			frame, vrect;
	MCChipPrefView	*view;
	MCPrefWin		*pwin;
	MCDataDetail	data;

	if(this->isOpenPref == true)
	{
		return;
	}
	this->isOpenPref = true;

	if(this->target == NULL)
	{
		// New Chip
		char	defname[] = {"chip"};

		strcpy(data.family, this->defset.family);
		data.fsize = this->defset.fsize;
		data.ccolor = this->defset.ccolor;
		data.ffws = this->fcdfws;
		data.name = new char[strlen(defname) + 1];
		strcpy(data.name, defname);
	}
	else
	{
		// Chip edit
		this->target->Lock();
		this->target->GetData(&data);
		this->target->Unlock();
	}

	frame = BScreen().Frame();
	frame.left = (frame.Width() - PW_WIDTH) / 2;
	frame.top = (frame.Height() - PW_HEIGHT) / 2;
	frame.right = frame.left + PW_WIDTH - 1;
	frame.bottom = frame.top + PW_HEIGHT - 1;

	vrect = frame;
	vrect.OffsetTo(B_ORIGIN);
	view = new MCChipPrefView(vrect, &data);
	view->SetText(&data);
	pwin = new MCPrefWin(frame, view);
	pwin->SelectTab(tabidx);
	pwin->Show();
}


/////
// main preference call
//
void MCApp::callMainPref()
{
	BRect			frame, vrect;
	MCMainPrefView	*view;
	MCPrefWin		*pwin;
	MCDataHeader	head;

	if(this->isOpenPref == true)
	{
		return;
	}
	this->isOpenPref = true;

	strcpy(head.family, this->defset.family);
	head.fsize = this->defset.fsize;
	head.ccolor = this->defset.ccolor;
	head.ffws = this->ffws;
	head.fcdfws = this->fcdfws;
	head.fspos = this->fspos;
	head.findeskbar = this->findeskbar;
	head.fconfirm = this->fconfirm;
	head.fdblckedit = this->fdblckedit;

	frame = BScreen().Frame();
	frame.left = (frame.Width() - PW_WIDTH) / 2;
	frame.top = (frame.Height() - PW_HEIGHT) / 2;
	frame.right = frame.left + PW_WIDTH - 1;
	frame.bottom = frame.top + PW_HEIGHT - 1;

	vrect = frame;
	vrect.OffsetTo(B_ORIGIN);
	view = new MCMainPrefView(vrect, &head);
	pwin = new MCPrefWin(frame, view);
	pwin->Show();
}


/////
// MemoChip application exit
//
void MCApp::appExit(
	BRect	frame)
{
	status_t		sts;
	BPath			path;
	BFile			file;
	MCArchive		*arc;
	MCChipWin		*cwin;
	MCDataHeader	head;
	MCDataDetail	*data;
	char			df[B_PATH_NAME_LENGTH];

	// archiving memochip data
	arc = new MCArchive();

	head.ffws = this->ffws;
	head.fcdfws = this->fcdfws;
	head.fspos = this->fspos;
	head.findeskbar = this->findeskbar;
	head.fconfirm = this->fconfirm;
	head.fdblckedit = this->fdblckedit;
	strcpy(head.family, this->defset.family);
	head.fsize = this->defset.fsize;
	head.ccolor = this->defset.ccolor;
	head.numchips = this->chips.CountItems();

	arc->AddChipHeader(&head);
	if(this->fspos == true)
	{
		arc->AddRect("mpos", frame);
	}
	else
	{
		arc->AddRect("mpos", this->oldrect);
	}

	BMessage	*msg;
	msg = new BMessage(B_QUIT_REQUESTED);
	msg->AddBool("isExitApp", true);
	for(int32 i = 0; i < head.numchips; ++i)
	{
		data = new MCDataDetail();
		cwin = (MCChipWin*) this->chips.ItemAt(i);
		cwin->Lock();
		cwin->GetData(data);
		cwin->Unlock();
		arc->AddChipData(data);
		cwin->PostMessage(msg);
		delete data;
	}
	delete msg;
	this->chips.MakeEmpty();

	// write memochip data
	sts = find_directory(B_USER_CONFIG_DIRECTORY, &path);
	if(sts != B_NO_ERROR) goto ERR;

	BDirectory	*dir;
	sprintf(df, "%s%s", path.Path(), "/settings");
	dir = new BDirectory(df);
	sts = dir->CreateDirectory("wbAPPS", dir);
	delete	dir;

	sprintf(df, "%s%s", df, "/wbAPPS/MemoChip.dat");
	sts = file.SetTo(df, (B_WRITE_ONLY | B_CREATE_FILE | B_ERASE_FILE));
	if(sts != B_NO_ERROR) goto ERR;

	arc->Flatten(&file);

ERR:
	return;
}


/////
// tear off MemoChip
//
void MCApp::tearOffMemoChip(
	MCChipWin	*win)
{
	this->chips.RemoveItem(win);
}


/////
// set main option
//
void MCApp::setOption(
	MCDataHeader	*head)
{
	this->ffws = head->ffws;
	this->fcdfws = head->fcdfws;
	this->fspos = head->fspos;
	if(this->findeskbar != head->findeskbar)
	{
		this->findeskbar = head->findeskbar;
		this->switchInterface();
	}
	this->fconfirm = head->fconfirm;
	this->fdblckedit = head->fdblckedit;
	strcpy(this->defset.family, head->family);
	this->defset.fsize = head->fsize;
	this->defset.ccolor = head->ccolor;

	this->mainpanel->SetFollowWorkspaces(this->ffws);

	delete head;
}


/////
// set chip data(or create new chip)
//
void MCApp::setChipData(
	MCDataDetail	*data)
{
	if(this->target == NULL)
	{
		// create new chip
		data->wspace = (1 << current_workspace());
		data->frame = BScreen().Frame();
		data->frame.left = (data->frame.Width() - MC_WIDTH) / 2;
		data->frame.top = (data->frame.Height() - MC_HEIGHT) / 2;
		data->frame.right = data->frame.left + MC_WIDTH - 1;
		data->frame.bottom = data->frame.top + MC_HEIGHT - 1;
		this->createMemoChip(data);
	}
	else
	{
		// edit chip data
		this->target->Lock();
		this->target->SetData(data);
		this->target->Unlock();
	}

	delete data;
}


/////
// switch interface 'Mainpanel Window' or 'Deskbar Icon'
//
void MCApp::switchInterface()
{
	if(this->findeskbar == true)
	{
		this->mainpanel->Hide();
		this->installInDeskbar();
	}
	else
	{
		this->mainpanel->Show();
		this->removeFromDeskbar();
	}
}


/////
// install MemoChip miniicon in Deskbar
//
void MCApp::installInDeskbar()
{
	MCMiniIcon	*mi = new MCMiniIcon(BRect(0, 0, 15, 15));
	BDeskbar().AddItem(mi, &(this->icon_id));
}


/////
// remove MemoChip miniicon from Deskbar
//
void MCApp::removeFromDeskbar()
{
	BDeskbar().RemoveItem(this->icon_id);
}


/////
// application startup
//
int main()
{
	MCApp	app;
	app.Run();
	return true;
}
