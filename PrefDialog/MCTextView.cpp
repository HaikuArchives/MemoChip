/////
// MCTextView.cpp
// implement file for MCTextView class
//
// Hideki Naito
// last modified : 1999/12/22
//

#include	<stdio.h>
#include	"MCTextView.h"


/////
// constructor for MCTextView class
//
MCTextView::MCTextView(
	BRect	frame)
	: BTextView(frame, "mctextview", frame, B_FOLLOW_ALL, B_WILL_DRAW)
{
}


/////
// frame resize hook
//
void MCTextView::FrameResized(
	float	width,
	float	height)
{
	BRect	rect(this->TextRect());
	rect.right = rect.left + width;
	this->SetTextRect(rect);
}

/////
// view attached to window
//
void MCTextView::AttachedToWindow()
{
	BTextView::AttachedToWindow();
	this->MakeFocus(true);
}
