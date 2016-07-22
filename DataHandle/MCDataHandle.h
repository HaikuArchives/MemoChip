/////
// MCDataHandle.h
// MamoChip data handler
//
// Hideki Naito
// last modified : 1999/12/06
//

#ifndef	_MCDATAHANDLE_H
#define	_MCDATAHANDLE_H

#include	<Font.h>

/////
// define MCDataHandle class
//
class MCDataHandle
{
public:
	// member
	font_family	family;		// font family
	int32		fsize;		// font size
	rgb_color	ccolor;		// chip color
	bool		ffws;		// follow workspace flag
};


#endif	// _MCDATAHANDLE_H
