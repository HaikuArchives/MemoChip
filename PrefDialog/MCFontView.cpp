/////
// MCFontView.cpp
// implement file for MCFontView class
//
// Hideki Naito
// last modified : 1999/01/01
//

#include	<MenuField.h>
#include	<PopUpMenu.h>
#include	<MenuItem.h>
#include	<StringView.h>
#include	<stdlib.h>
#include	"MCFontView.h"


/////
// constants
//

#define	MSG_FAMILYCHANGE	'faml'
#define	MSG_SIZECHANGE		'size'

#define	NUM_FONTSIZE		9

#define	SAMPLE_STRING		"aBc"


/////
// static class member
//

BRect	samplebox(20, 102, 190, 182);


/////
// create all component
//
void MCFontView::createAllComponent()
{
	int32		i, nf, ifs;
	font_family	ff;
	char		sizes[][3] = {"9", "10", "12", "14", "18",
		"24", "36", "48", "72"};
	BMenuField	*mf;
	BPopUpMenu	*pm;
	BMenuItem	*item;
	BMessage	*msg;
	BStringView	*slabel;

	// create font_family menu
	nf = count_font_families();
	pm = new BPopUpMenu("familypopup");
	for(i = 0; i < nf; ++i)
	{
		get_font_family(i, &ff);
		msg = new BMessage(MSG_FAMILYCHANGE);
		msg->AddInt32("id", i);
		item = new BMenuItem(ff, msg);
		pm->AddItem(item);
		if(strcmp(ff, this->family) == 0)
		{
			item->SetMarked(true);
		}
	}
	mf = new BMenuField(BRect(20, 20, 191, 40), "familymenu",
		"font_family", pm);
	mf->SetDivider(61);
	this->AddChild(mf);

	// create font_size menu
	pm = new BPopUpMenu("fsizepopup");
	for(i = 0; i < NUM_FONTSIZE; ++i)
	{
		ifs = atoi(sizes[i]);
		msg = new BMessage(MSG_SIZECHANGE);
		msg->AddInt32("fsize", ifs);
		item = new BMenuItem(sizes[i], msg);
		pm->AddItem(item);
		if(ifs == this->fsize)
		{
			item->SetMarked(true);
		}
	}
	mf = new BMenuField(BRect(20, 50, 191, 70), "fsizemenu",
		"font_size", pm);
	mf->SetDivider(61);
	this->AddChild(mf);

	// create sample label
	slabel = new BStringView(BRect(21, 90, 56, 100), "samplelabel", "sample");
	this->AddChild(slabel);
}


/////
// constructor for MCFontView class
//
MCFontView::MCFontView(
	BRect	frame)
	: BView(frame, "mcfontview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	font_family	ff;
	font_style	fs;

	be_plain_font->GetFamilyAndStyle(&ff, &fs);
	strcpy(this->family, ff);
	this->fsize = 10;

	this->createAllComponent();
}


/////
// constructor for MCFontView class
//
MCFontView::MCFontView(
	BRect		frame,
	font_family	fam,
	int32		size)
	: BView(frame, "mcfontview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	strcpy(this->family, fam);
	this->fsize = size;

	this->createAllComponent();
}


/////
// view attached to window
//
void MCFontView::AttachedToWindow()
{
	BMenuField	*mf;

	// set view color to parent
	this->SetViewColor(this->Parent()->ViewColor());

	// set target
	mf = (BMenuField *) this->FindView("familymenu");
	mf->Menu()->SetTargetForItems(this);
	mf = (BMenuField *) this->FindView("fsizemenu");
	mf->Menu()->SetTargetForItems(this);
}


/////
// redraw hook
//
void MCFontView::Draw(
	BRect	rect)
{
	float		x, y;
	font_height	ht;
	rgb_color	backclr;
	rgb_color	drawclr = {255, 255, 255, 255};
	BFont		backfont, drawfont;

	// clear rect
	backclr = this->HighColor();
	this->SetHighColor(drawclr);
	this->FillRect(samplebox);
	this->SetHighColor(backclr);
	this->StrokeRect(samplebox);

	// draw sample
	this->GetFont(&backfont);
	drawfont = backfont;
	drawfont.SetFamilyAndStyle(this->family, NULL);
	drawfont.SetSize((float) this->fsize);
	this->SetFont(&drawfont);

	x = this->StringWidth(SAMPLE_STRING);
	x = (samplebox.right - samplebox.left) - x;
	x = (x < 0) ? 0 : (x / 2);
	x += samplebox.left;
	y = (samplebox.bottom - samplebox.top) / 2;
	this->GetFontHeight(&ht);
	y = y + ((ht.ascent - ht.descent) / 2) + samplebox.top;
	this->MovePenTo(x, y);
	this->DrawString(SAMPLE_STRING);
	this->SetFont(&backfont);
}


/////
// message hook
//
void MCFontView::MessageReceived(
	BMessage	*msg)
{
	int32		nwork;
	font_family	ff;

	switch(msg->what)
	{
		case MSG_FAMILYCHANGE:
		{
			msg->FindInt32("id", &nwork);
			get_font_family(nwork, &ff);
			strcpy(this->family, ff);
			this->Invalidate();
			break;
		}
		case MSG_SIZECHANGE:
		{
			msg->FindInt32("fsize", &nwork);
			this->fsize = nwork;
			this->Invalidate();
			break;
		}
		default:
		{
			BView::MessageReceived(msg);
		}
	}
}
