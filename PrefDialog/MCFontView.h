/////
// MCFontView.h
// chip-font preference view
//
// Hideki Naito
// last modified : 1999/01/15
//

#ifndef	_MCFONTVIEW_H
#define	_MCFONTVIEW_H

#include	<View.h>


/////
// define MCFontView class
//
class MCFontView : public BView
{
private:
	// member
	font_family		family;
	int32			fsize;

	// method
	void			createAllComponent();
	virtual void	AttachedToWindow();
	virtual	void	Draw(BRect rect);
	virtual void	MessageReceived(BMessage *msg);

public:
	// method
					MCFontView(BRect frame);
					MCFontView(BRect frame, font_family fam, int32 size);

	void			GetFontInfo(font_family fam, int32 *fs)
	{
		strcpy(fam, family);
		*fs = fsize;
	}
};


#endif	// _MCFONTVIEW_H
