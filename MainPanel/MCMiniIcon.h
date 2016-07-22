/////
// MCMiniIcon.h
// MemoChip mini icon in Deskbar
//
// Hideki Naito
// last modified : 1999/04/16
//

#ifndef	_MCMINIICON_H
#define	_MCMINIICON_H

#include	<View.h>
#include	<Bitmap.h>
#include	<PopUpMenu.h>


/////
// define MCMiniIcon class
//
class __declspec(dllexport) MCMiniIcon : public BView
{
private:
	// member
	BBitmap				*icon;

	// method
	virtual void		MouseDown(BPoint point);
	virtual void		Draw(BRect rect);
	virtual void		AttachedToWindow();

	BPopUpMenu			*createPopUpMenu();

public:
	// method
						MCMiniIcon(BRect frame);
						MCMiniIcon(BMessage *msg);
						~MCMiniIcon(); 

	static MCMiniIcon	*Instantiate(BMessage *data);
	virtual status_t	Archive(BMessage *data, bool deep = true) const;
};


#endif	// _MCMINIICON_H
