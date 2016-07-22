/////
// MCMainWin.h
// MemoChip main-panel window
//
// Hideki Naito
// last modified : 1999/01/16
//

#ifndef	_MCMAINWIN_H
#define	_MCMAINWIN_H

#include	<Window.h>


/////
// define MCMainWin class
//
class MCMainWin : public BWindow
{
private:
	// member
	bool			ffws;	// follow workspace flag
	bool			isQuit;	// quit ok flag

	// method
	virtual bool	QuitRequested();
	virtual void	WorkspaceActivated(int32 ws, bool active);

public:
	// method
					MCMainWin(BRect frame, bool fws = true);

	void			SetFollowWorkspaces(bool fws)
	{
		this->ffws = fws;
	}
};


#endif	// _MCMAINWIN_H
