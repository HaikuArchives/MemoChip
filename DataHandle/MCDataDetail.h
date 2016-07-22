/////
// MCDataDetail.h
// MemoChip data detail
//
// Hideki Naito
// last modified : 1999/12/28
//

#ifndef	_MCDATADETAIL_H
#define	_MCDATADETAIL_H

#include	"MCDataHandle.h"


/////
// define MCDataDetail class
//
class MCDataDetail : public MCDataHandle
{
public:
	// member
	uint32		wspace;		// chip workspace
	BRect		frame;		// chip position and size
	char		*name;		// chip name
	char		*data;		// chip data

	// method
				MCDataDetail() {this->name = NULL; this->data = NULL;}
	virtual 	~MCDataDetail()
	{
		if(this->name != NULL)
		{
			delete[] this->name;
		}
		if(this->data != NULL)
		{
			delete[] this->data;
		}
	}
};


#endif	// _MCDATADETAIL_H
