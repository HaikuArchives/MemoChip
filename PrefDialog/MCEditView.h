/////
// MCEditView.h
// chip-data edit area view
//
// Hideki Naito
// last modified : 1999/12/05
//

#ifndef	_MCEDITVIEW_H
#define	_MCEDITVIEW_H

#include	<View.h>
#include	"MCTextView.h"


/////
// define MCEditView class
//
class MCEditView : public BView
{
private:
	// member
	MCTextView		*tview;

	// method
	void			createAllComponent(BRect frame,
						font_family fam, int32 size);
	virtual void	AttachedToWindow();

public:
	// method
					MCEditView(BRect frame);
					MCEditView(BRect frame, font_family fam, int32 size);

	void			SetText(const char *data);
	const char		*GetText();
};


#endif	// _MCEDITVIEW_H
