/////
// MCChipWin.h
// MemoChip window
//
// Hideki Naito
// last modified : 1999/12/05
//

#ifndef	_MCCHIPWIN_H
#define	_MCCHIPWIN_H

#include	<Window.h>
#include	"MCChipView.h"
#include	"MCDataDetail.h"


/////
// define MCChipWin class
//
class MCChipWin : public BWindow
{
private:
	// member
	MCChipView		*cview;
	bool			ffws;	// follow workspace flag

	// method
	virtual bool	QuitRequested();
	virtual void	MessageReceived(BMessage *msg);
	virtual void	WorkspaceActivated(int32 ws, bool active);

public:
	// method
					MCChipWin(BRect frame);

	void			SetData(MCDataDetail *data, bool isLoad = false);
	void			GetData(MCDataDetail *data);
};


#endif	// _MCCHIPWIN_H
