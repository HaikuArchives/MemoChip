/////
// MCTextView.h
// MemoChip window view
//
// Hideki Naito
// last modified : 1999/12/22
//

#ifndef	_MCTEXTVIEW_H
#define	_MCTEXTVIEW_H

#include	<TextView.h>


/////
// define MCTextView class
//
class MCTextView : public BTextView
{
private:
	// method
	virtual void	FrameResized(float width, float height);
	virtual void	AttachedToWindow();

public:
	// method
					MCTextView(BRect frame);
};


#endif	// _MCTEXTVIEW_H
