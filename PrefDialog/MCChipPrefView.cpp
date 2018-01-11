/////
// MCChipPrefView.cpp
// implement file for MCChipPrefView class
//
// Hideki Naito
// last modified : 2000/10/14
//

#include	<Application.h>
#include	<Window.h>
#include	<stdlib.h>
#include	<string.h>
#include	"MCChipPrefView.h"
#include	"MCMsgConst.h"


/////
// constructor for MCChipPrefView class
//
MCChipPrefView::MCChipPrefView(
	BRect			frame,
	MCDataDetail	*data)
	: MCPrefViewAbst(frame, "chipprefview")
{
	BTab	*tab;
	BRect	rect;

	rect = this->tview->Bounds();
	rect.InsetBy(5, 5);
	rect.bottom -= this->tview->TabHeight();

	// create 'edit' tab
	this->editview = new MCEditView(rect, data->family, data->fsize);
	tab = new BTab(this->editview);
	tab->SetLabel("edit");
	this->tview->AddTab(this->editview, tab);

	// create 'font' tab
	this->fontview = new MCFontView(rect, data->family, data->fsize);
	tab = new BTab(this->fontview);
	tab->SetLabel("font");
	this->tview->AddTab(this->fontview, tab);

	// create 'color' tab
	this->clrview = new MCColorView(rect, &(data->ccolor));
	tab = new BTab(this->clrview);
	tab->SetLabel("color");
	this->tview->AddTab(this->clrview, tab);

	// create 'chip option' tab
	this->cpoptview = new MCChipOptView(rect, data->ffws);
	tab = new BTab(this->cpoptview);
	tab->SetLabel("chip option");
	this->tview->AddTab(this->cpoptview, tab);

	this->AddChild(this->tview);
}


/////
// set text to edit box
//
void MCChipPrefView::SetText(
	MCDataDetail	*data)
{
	if(data->data != NULL)
	{
		this->editview->SetText(data->data);
	}
	if(data->name != NULL)
	{
		this->cpoptview->SetName(data->name);
	}
}


/////
// 'Set' button handler
//
void MCChipPrefView::PrefSet()
{
	int32			size;
	char			*work;
	MCDataDetail	*data;
	BMessage		*msg;

	data = new MCDataDetail();
	work = (char*) this->editview->GetText();
	size = strlen(work);
	if(size > 0)
	{
		data->data = new char[size + 1];
		strcpy(data->data, work);
	}
	else
	{
		data->data = NULL;
	}
	this->fontview->GetFontInfo(data->family, &(data->fsize));
	data->ccolor = this->clrview->GetSelColor();
	work = (char*) this->cpoptview->GetName();
	size = strlen(work);
	if(size > 0)
	{
		data->name = new char[size + 1];
		strcpy(data->name, work);
	}
	else
	{
		data->name = NULL;
	}
	this->cpoptview->GetOption(&(data->ffws));

	msg = new BMessage(MSG_SETCHIPDATA);
	msg->AddPointer("data", (void*) data);
	be_app->PostMessage(msg);
	delete msg;

	this->Window()->PostMessage(B_QUIT_REQUESTED);
}
