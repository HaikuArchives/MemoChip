/////
// MCChipPrefView.h
// MemoChip chip preference view
//
// Hideki Naito
// last modified : 1999/12/05
//

#ifndef	_MCCHIPPREFVIEW_H
#define	_MCCHIPPREFVIEW_H

#include	"MCPrefViewAbst.h"
#include	"MCEditView.h"
#include	"MCFontView.h"
#include	"MCColorView.h"
#include	"MCChipOptView.h"
#include	"MCDataDetail.h"


/////
// define MCChipPrefView class
//
class MCChipPrefView : public MCPrefViewAbst
{
private:
	// member
	MCEditView		*editview;
	MCFontView		*fontview;
	MCColorView		*clrview;
	MCChipOptView	*cpoptview;

public:
	// method
					MCChipPrefView(BRect frame, MCDataDetail *data);

	virtual	void	SetText(MCDataDetail *data);
	virtual void	PrefSet();
};


#endif	// _MCCHIPPREFVIEW_H
