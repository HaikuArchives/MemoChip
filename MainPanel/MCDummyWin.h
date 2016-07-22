/////
// MCDummyWin.h
// MemoChip main-panel window
// anytime follow workspace change
//
// Hideki Naito
// last modified : 1999/07/12
//

#ifndef	_MCDUMMYWIN_H
#define	_MCDUMMYWIN_H

#include	<Window.h>


/////
// define MCDummyWin class
//
class MCDummyWin : public BWindow
{
private:
	// method
	virtual void	WorkspaceActivated(int32 ws, bool active);
	virtual void	ScreenChanged(BRect frame, color_space mode);

public:
	// method
					MCDummyWin(BRect frame);
};


#endif	// _MCDUMMYWIN_H
