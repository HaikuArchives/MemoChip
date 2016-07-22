/////
// MCChipView.h
// MemoChip window view
//
// Hideki Naito
// last modified : 2000/10/14
//

#ifndef	_MCCHIPVIEW_H
#define	_MCCHIPVIEW_H

#include	<TextView.h>
#include	<PopUpMenu.h>
#include	"MCDataDetail.h"


/////
// define MCChipView class
//
class MCChipView : public BTextView
{
private:
	// member
	bigtime_t		prev_click;

	// method
	virtual void	FrameResized(float width, float height);
	virtual void	MouseDown(BPoint point);

	BPopUpMenu		*createPopUpMenu();

public:
	// method
					MCChipView(BRect frame);

	void			SetData(MCDataDetail *data);
	void			GetData(MCDataDetail *data);
};


#endif	// _MCCHIPVIEW_H
