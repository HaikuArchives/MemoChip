/////
// MCChipOptView.h
// mainpanel preference view
//
// Hideki Naito
// last modified : 1999/12/28
//

#ifndef	_MCCHIPOPTVIEW_H
#define	_MCCHIPOPTVIEW_H

#include	<View.h>
#include	<TextControl.h>


/////
// define MCChipOptView class
//
class MCChipOptView : public BView
{
private:
	// member
	BTextControl	*nametext;
	bool			fworkspc;

	// method
	void			createAllComponent();
	virtual void	AttachedToWindow();
	virtual void	MessageReceived(BMessage *msg);

public:
	// method
					MCChipOptView(BRect frame);
					MCChipOptView(BRect frame, bool fws);

	void			SetName(const char *name)
	{
		this->nametext->SetText(name);
	}
	const char		*GetName()
	{
		return this->nametext->Text();
	}
	void			GetOption(bool *fws)
	{
		*fws = this->fworkspc;
	}
};


#endif	// _MCCHIPOPTVIEW_H
