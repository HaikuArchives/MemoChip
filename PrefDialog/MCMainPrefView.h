/////
// MCMainPrefView.h
// MemoChip main preference view
//
// Hideki Naito
// last modified : 1999/01/13
//

#ifndef	_MCMAINPREFVIEW_H
#define	_MCMAINPREFVIEW_H

#include	"MCPrefViewAbst.h"
#include	"MCOptView.h"
#include	"MCFontView.h"
#include	"MCColorView.h"
#include	"MCDataHeader.h"


/////
// define MCMainPrefView class
//
class MCMainPrefView : public MCPrefViewAbst
{
private:
	// member
	MCOptView		*optview;
	MCFontView		*fontview;
	MCColorView		*clrview;

public:
	// method
					MCMainPrefView(BRect frame, MCDataHeader *head);

	virtual void	PrefSet();
};


#endif	// _MCMAINPREFVIEW_H
