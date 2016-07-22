/////
// MCMainPrefView.cpp
// implement file for MCMainPrefView class
//
// Hideki Naito
// last modified : 2000/10/12
//

#include	<Application.h>
#include	<Window.h>
#include	"MCMainPrefView.h"
#include	"MCMsgConst.h"


/////
// constructor for MCMainPrefView class
//
MCMainPrefView::MCMainPrefView(
	BRect			frame,
	MCDataHeader	*head)
	: MCPrefViewAbst(frame, "mainprefview")
{
	BTab	*tab;
	BRect	rect;

	rect = this->tview->Bounds();
	rect.InsetBy(5, 5);
	rect.bottom -= this->tview->TabHeight();

	// create 'main option' tab
	this->optview = new MCOptView(rect, head->ffws, head->fcdfws, head->fspos,
		head->findeskbar, head->fconfirm, head->fdblckedit);
	tab = new BTab(this->optview);
	tab->SetLabel("main option");
	this->tview->AddTab(this->optview, tab);

	// create 'default font' tab
	this->fontview = new MCFontView(rect, head->family, head->fsize);
	tab = new BTab(this->fontview);
	tab->SetLabel("default font");
	this->tview->AddTab(this->fontview, tab);

	// create 'default color' tab
	this->clrview = new MCColorView(rect, &(head->ccolor));
	tab = new BTab(this->clrview);
	tab->SetLabel("default color");
	this->tview->AddTab(this->clrview, tab);

	this->AddChild(this->tview);
}


/////
// 'Set' button handler
//
void MCMainPrefView::PrefSet()
{
	MCDataHeader	*head;
	BMessage		*msg;

	head = new MCDataHeader();
	this->optview->GetOption(&(head->ffws), &(head->fcdfws), &(head->fspos),
		&(head->findeskbar), &(head->fconfirm), &(head->fdblckedit));
	this->fontview->GetFontInfo(head->family, &(head->fsize));
	head->ccolor = this->clrview->GetSelColor();

	msg = new BMessage(MSG_SETOPTION);
	msg->AddPointer("data", (void*) head);
	be_app->PostMessage(msg);
	delete msg;

	this->Window()->PostMessage(B_QUIT_REQUESTED);
}
