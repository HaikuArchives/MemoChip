/////
// MCOptView.h
// mainpanel preference view
//
// Hideki Naito
// last modified : 1999/12/28
//

#ifndef	_MCOPTVIEW_H
#define	_MCOPTVIEW_H

#include	<View.h>


/////
// define MCOptView class
//
class MCOptView : public BView
{
private:
	// member
	bool			fworkspc;		// mainpanel follows workspace flag
	bool			fcpdeffws;		// chip default follows workspace flag
	bool			fsavepos;		// save mainpanel position flag
	bool			findeskbar;		// install in deskbar flag
	bool			fconfirm;		// confirm before tear off flag
	bool			fdblckedit;		// enable double-click to edit

	// method
	void			createAllComponent();
	virtual void	AttachedToWindow();
	virtual void	MessageReceived(BMessage *msg);

public:
	// method
					MCOptView(BRect frame);
					MCOptView(BRect frame, bool fws, bool fcdfws, bool fsp,
						bool findsk, bool fconf, bool fdced);

	void			GetOption(bool *fws, bool *fcdfws, bool *fsp,
						bool *findsk, bool *fconf, bool *fdced)
	{
		*fws = this->fworkspc;
		*fcdfws = this->fcpdeffws;
		*fsp = this->fsavepos;
		*findsk = this->findeskbar;
		*fconf = this->fconfirm;
		*fdced = this->fdblckedit;
	}
};


#endif	// _MCOPTVIEW_H
