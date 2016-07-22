/////
// MCColorView.h
// chip-color preference view
//
// Hideki Naito
// last modified : 1998/12/29
//

#ifndef	_MCCOLORVIEW_H
#define	_MCCOLORVIEW_H

#include	<View.h>


/////
// define MCColorView class
//
class MCColorView : public BView
{
private:
	// member
	rgb_color		selcolor;

	// method
	void			createAllComponent();
	virtual void	AttachedToWindow();
	virtual void	Draw(BRect rect);
	virtual void	MessageReceived(BMessage *msg);

public:
	// member
	static rgb_color	white;
	static rgb_color	gray;
	static rgb_color	pink;
	static rgb_color	lightyellow;
	static rgb_color	lightblue;
	static rgb_color	lightgreen;

	// method
					MCColorView(BRect frame);
					MCColorView(BRect frame, rgb_color *color);

	rgb_color		GetSelColor()
	{
		return selcolor;
	}
};


#endif	// _MCCOLORVIEW_H
