/////
// MCApp.h
// MemoChip application class
//
// Hideki Naito
// last modified : 2000/10/12
//

#ifndef	_MCAPP_H
#define	_MCAPP_H

#include	<Application.h>
#include	"MCDummyWin.h"
#include	"MCMainWin.h"
#include	"MCChipWin.h"
#include	"MCDataHandle.h"
#include	"MCDataHeader.h"
#include	"MCDataDetail.h"


/////
// define MCApp class
//
class MCApp : public BApplication
{
private:
	// member
	MCDummyWin		*dummy;		// anytime follow workspace
	BList			chips;		// MemoChip window list
	MCChipWin		*target;	// ChipPref target window

	BRect			oldrect;	// old mainpanel position
	bool			ffws;		// mainpanel follows workspace
	bool			fcdfws;		// chip default follows workspace
	bool			fspos;		// is save mainpanel position
	bool			findeskbar;	// install in Deskbar
	bool			fconfirm;	// confirm before tear off
	bool			fdblckedit;	// enable double-click to edit
	MCDataHandle	defset;		// default setting

	int32			icon_id;	// mini-icon id

	// method
	virtual void	ReadyToRun();
	virtual void	MessageReceived(BMessage *msg);
	virtual bool	QuitRequested();

	void			createMemoChip(MCDataDetail *data, bool isLoad);
	void			callMemoChipPref(int32 tabidx = 0);
	void			callMainPref();
	void			appExit(BRect frame);
	void			tearOffMemoChip(MCChipWin *win);
	void			setOption(MCDataHeader *head);
	void			setChipData(MCDataDetail *data);
	void			switchInterface();
	void			installInDeskbar();
	void			removeFromDeskbar();

public:
	// member
	bool			isOpenPref;
	MCMainWin		*mainpanel;	// mainpanel window
	
	// method
					MCApp();

	bool			NeedConfirm() {return this->fconfirm;}
	bool			IsEnableDblClk() {return this->fdblckedit;}
};


#endif	// _MCAPP_H
