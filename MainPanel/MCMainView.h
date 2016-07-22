/////
// MCMainView.h
// MemoChip main-panel view
//
// Hideki Naito
// last modified : 1999/01/13
//

#ifndef	_MCMAINVIEW_H
#define	_MCMAINVIEW_H

#include	<View.h>


/////
// define MCMainView class
//
class MCMainView : public BView
{
private:
	// method
	virtual void	AttachedToWindow();

public:
	// method
					MCMainView(BRect frame);
};


#endif	// _MCMAINVIEW_H
