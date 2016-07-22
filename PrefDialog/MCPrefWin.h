/////
// MCPrefWin.h
// preference dialog window
//
// Hideki Naito
// last modified : 1999/01/24
//

#ifndef	_MCPREFWIN_H
#define	_MCPREFWIN_H

#include	<Window.h>
#include	"MCPrefViewAbst.h"


/////
// define MCPrefWin class
//
class MCPrefWin : public BWindow
{
private:
	// member
	MCPrefViewAbst	*cview;

	// method
	virtual bool	QuitRequested();
	virtual void	MessageReceived(BMessage *msg);

public:
	// method
					MCPrefWin(BRect frame, MCPrefViewAbst *view);
					
	void			SelectTab(int32 tabidx) {this->cview->SelectTab(tabidx);}
};


#endif	// _MCPREFWIN_H
