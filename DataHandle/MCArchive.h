/////
// MCArchive.h
// MemoChip archiver
//
// Hideki Naito
// last modified : 1999/01/12
//

#ifndef	_MCARCHIVE_H
#define	_MCARCHIVE_H

#include	<Message.h>
#include	"MCDataHeader.h"
#include	"MCDataDetail.h"


/////
// define MCArchive class
//
class MCArchive : public BMessage
{
public:
	// method
	status_t	AddChipHeader(MCDataHeader *head);
	status_t	FindChipHeader(MCDataHeader *head);
	status_t	AddChipData(MCDataDetail *data);
	status_t	FindChipData(int32 idx, MCDataDetail *data);
};


#endif	// _MCARCHIVE_H
