/////
// MCPrefViewAbst.h
// abstruct view class for preference dialog
//
// Hideki Naito
// last modified : 1999/01/16
//

#ifndef	_MCPREFABSTVIEW_H
#define	_MCPREFABSTVIEW_H

#include	<View.h>
#include	<TabView.h>


/////
// define MCPrefViewAbst class
//
class MCPrefViewAbst : public BView
{
protected:
	// member
	BTabView		*tview;

private:
	// method
	virtual void	AttachedToWindow();
	
public:
	// method
					MCPrefViewAbst(BRect frame, const char *name);

	void			SelectTab(int32 tabidx) {this->tview->Select(tabidx);}
	virtual void	PrefSet() = 0;
};


#endif	// _MCPREFABSTVIEW_H
