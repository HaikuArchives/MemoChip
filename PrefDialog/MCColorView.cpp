/////
// MCColorView.cpp
// implement file for MCColorView class
//
// Hideki Naito
// last modified : 1999/12/05
//

#include	<StringView.h>
#include	<RadioButton.h>
#include	"MCColorView.h"


/////
// constants
//

#define	MSG_WHITE_SEL	'whit'
#define	MSG_GRAY_SEL	'gray'
#define	MSG_YELLOW_SEL	'yelw'
#define	MSG_PINK_SEL	'pink'
#define	MSG_BLUE_SEL	'blue'
#define	MSG_GREEN_SEL	'gren'


/////
// static class member
//

rgb_color	MCColorView::white = {255, 255, 255, 255};
rgb_color	MCColorView::gray = {192, 192, 192, 255};
rgb_color	MCColorView::pink = {255, 192, 255, 255};
rgb_color	MCColorView::lightyellow = {255, 255, 192, 255};
rgb_color	MCColorView::lightblue = {192, 255, 255, 255};
rgb_color	MCColorView::lightgreen = {192, 255, 192, 255};


////
// macro
//

#define	COMPARECOLOR(c1, c2)	(c1.red == c2.red) && (c1.green == c2.green) && (c1.blue == c2.blue) && (c1.alpha == c2.alpha)


/////
// create all component
//
void MCColorView::createAllComponent()
{
	BStringView		*label;
	BRadioButton	*rbtn;

	// create information label
	label = new BStringView(BRect(15, 20, 105, 30), "info",
		"select chip-color :");
	this->AddChild(label);

	// create color-select button
	rbtn = new BRadioButton(BRect(20, 45, 110, 55), "white",
		"white", new BMessage(MSG_WHITE_SEL));
	if(COMPARECOLOR(this->selcolor, MCColorView::white))
	{
		rbtn->SetValue(B_CONTROL_ON);
	}
	this->AddChild(rbtn);
	rbtn = new BRadioButton(BRect(20, 70, 110, 80), "gray",
		"gray", new BMessage(MSG_GRAY_SEL));
	if(COMPARECOLOR(this->selcolor, MCColorView::gray))
	{
		rbtn->SetValue(B_CONTROL_ON);
	}
	this->AddChild(rbtn);
	rbtn = new BRadioButton(BRect(20, 95, 110, 105), "pink",
		"pink", new BMessage(MSG_PINK_SEL));
	if(COMPARECOLOR(this->selcolor, MCColorView::pink))
	{
		rbtn->SetValue(B_CONTROL_ON);
	}
	this->AddChild(rbtn);
	rbtn = new BRadioButton(BRect(20, 120, 110, 130), "yellow",
		"light yellow", new BMessage(MSG_YELLOW_SEL));
	if(COMPARECOLOR(this->selcolor, MCColorView::lightyellow))
	{
		rbtn->SetValue(B_CONTROL_ON);
	}
	this->AddChild(rbtn);
	rbtn = new BRadioButton(BRect(20, 145, 110, 155), "blue",
		"light blue", new BMessage(MSG_BLUE_SEL));
	if(COMPARECOLOR(this->selcolor, MCColorView::lightblue))
	{
		rbtn->SetValue(B_CONTROL_ON);
	}
	this->AddChild(rbtn);
	rbtn = new BRadioButton(BRect(20, 170, 110, 180), "green",
		"light green", new BMessage(MSG_GREEN_SEL));
	if(COMPARECOLOR(this->selcolor, MCColorView::lightgreen))
	{
		rbtn->SetValue(B_CONTROL_ON);
	}
	this->AddChild(rbtn);
}


/////
// constructor for MCColorView class
//
MCColorView::MCColorView(
	BRect	frame)
	: BView(frame, "mccolorview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->selcolor = MCColorView::white;	// default color set
	this->createAllComponent();
}


/////
// constructor for MCColorView class
//
MCColorView::MCColorView(
	BRect		frame,
	rgb_color	*color)
	: BView(frame, "mccolorview", B_FOLLOW_ALL, B_WILL_DRAW)
{
	this->selcolor = *color;
	this->createAllComponent();
}


/////
// view attached to window
//
void MCColorView::AttachedToWindow()
{
	BRadioButton	*rbtn;

	// set view color to parent
	this->SetViewColor(this->Parent()->ViewColor());

	// set target
	rbtn = (BRadioButton *) this->FindView("white");
	rbtn->SetTarget(this);
	rbtn = (BRadioButton *) this->FindView("gray");
	rbtn->SetTarget(this);
	rbtn = (BRadioButton *) this->FindView("yellow");
	rbtn->SetTarget(this);
	rbtn = (BRadioButton *) this->FindView("pink");
	rbtn->SetTarget(this);
	rbtn = (BRadioButton *) this->FindView("blue");
	rbtn->SetTarget(this);
	rbtn = (BRadioButton *) this->FindView("green");
	rbtn->SetTarget(this);
}


/////
// redraw hook
//
void MCColorView::Draw(
	BRect	rect)
{
	rgb_color	temp;

	// backup high-color
	temp = this->HighColor();

	// draw sample color
	this->StrokeRect(BRect(106, 15, 156, 33));
	this->SetHighColor(this->selcolor);
	this->FillRect(BRect(107, 16, 155, 32));
	this->SetHighColor(MCColorView::white);
	this->StrokeLine(BPoint(107, 16), BPoint(107, 32));
	this->StrokeLine(BPoint(107, 16), BPoint(155, 16));
	this->StrokeLine(BPoint(157, 15), BPoint(157, 33));
	this->StrokeLine(BPoint(106, 34), BPoint(156, 34));

	// restore high-color
	this->SetHighColor(temp);
}


/////
// message hook
//
void MCColorView::MessageReceived(
	BMessage	*msg)							// received message
{
	switch(msg->what)
	{
		case MSG_WHITE_SEL:
		{
			this->selcolor = MCColorView::white;
			this->Invalidate();
			break;
		}
		case MSG_GRAY_SEL:
		{
			this->selcolor = MCColorView::gray;
			this->Invalidate();
			break;
		}
		case MSG_PINK_SEL:
		{
			this->selcolor = MCColorView::pink;
			this->Invalidate();
			break;
		}
		case MSG_YELLOW_SEL:
		{
			this->selcolor = MCColorView::lightyellow;
			this->Invalidate();
			break;
		}
		case MSG_BLUE_SEL:
		{
			this->selcolor = MCColorView::lightblue;
			this->Invalidate();
			break;
		}
		case MSG_GREEN_SEL:
		{
			this->selcolor = MCColorView::lightgreen;
			this->Invalidate();
			break;
		}
		default:
		{
			BView::MessageReceived(msg);
		}
	}
}
