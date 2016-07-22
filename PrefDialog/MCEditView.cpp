/////
// MCEditView.cpp
// implement file for MCEditView class
//
// Hideki Naito
// last modified : 1999/12/22
//

#include	<ScrollView.h>
#include	"MCEditView.h"


/////
// create all component
//
void MCEditView::createAllComponent(
	BRect		frame,
	font_family	fam,
	int32		size)
{
	BFont			font;
	BRect			rect;
	BScrollView		*sview;

	rect = frame;
	rect.OffsetTo(B_ORIGIN);
	rect.right -= B_V_SCROLL_BAR_WIDTH;
	rect.bottom -= B_H_SCROLL_BAR_HEIGHT;
	this->tview = new MCTextView(rect);
	this->tview->GetFont(&font);
	font.SetFamilyAndStyle(fam, NULL);
	font.SetSize(size);
	this->tview->SetFontAndColor(&font);
	sview = new BScrollView("parent", this->tview, B_FOLLOW_ALL,
		0, true, true);
	this->AddChild(sview);
}


/////
// constructor for MCEditView class
//
MCEditView::MCEditView(
	BRect	frame)
	: BView(frame, "mceditview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	font_family	ff;
	font_style	fs;

	be_plain_font->GetFamilyAndStyle(&ff, &fs);
	this->createAllComponent(frame, ff, 10);
}


/////
// constructor for MCEditView class
//
MCEditView::MCEditView(
	BRect		frame,
	font_family	fam,
	int32		size)
	: BView(frame, "mceditview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->createAllComponent(frame, fam, size);
}


/////
// view attached to window
//
void MCEditView::AttachedToWindow()
{
	this->tview->MakeFocus(true);
}


/////
// set text to editbox
//
void MCEditView::SetText(
	const char	*data)
{
	this->tview->SetText(data);
}


/////
// get editting text
//
const char *MCEditView::GetText()
{
	return this->tview->Text();
}
