/////
// MCDataHeader.h
// MemoChip data header
//
// Hideki Naito
// last modified : 1999/12/28
//

#ifndef	_MCDATAHEADER_H
#define	_MCDATAHEADER_H

#include	"MCDataHandle.h"


/////
// define MCDataHeader class
//
class MCDataHeader : public MCDataHandle
{
public:
	// member
	bool		fcdfws;		// chip default follows workspace flag
	bool		fspos;		// save mainpanel flag
	bool		findeskbar;	// install in Deskbar flag
	bool		fconfirm;	// confirm before tear off chip
	bool		fdblckedit;	// enable double-click to edit
	int32		numchips;	// chip count
};


#endif	// _MCDATAHEADER_H
