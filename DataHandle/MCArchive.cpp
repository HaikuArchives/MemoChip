/////
// MCArchive.cpp
// implement file for MCArchive class
//
// Hideki Naito
// last modified : 1999/12/29
//

#include	<string.h>
#include	"MCArchive.h"


/////
// archiving MemoChip data header
//
status_t MCArchive::AddChipHeader(
	MCDataHeader	*head)
{
	status_t	sts;

	sts = this->AddBool("MCHffws", head->ffws);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddBool("MCHcdfws", head->fcdfws);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddBool("MCHfspos", head->fspos);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddBool("MCHindeskbar", head->findeskbar);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddBool("MCHconfirm", head->fconfirm);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddBool("MCHdblckedit", head->fdblckedit);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddString("MCHfamily", head->family);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt32("MCHfsize", head->fsize);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt8("MCHred", head->ccolor.red);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt8("MCHgreen", head->ccolor.green);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt8("MCHblue", head->ccolor.blue);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt32("MCHnumchips", head->numchips);
	if(sts != B_NO_ERROR) goto ERR;

	return B_NO_ERROR;

ERR:
	return sts;
}


/////
// find MemoChip data header
//
status_t MCArchive::FindChipHeader(
	MCDataHeader	*head)
{
	status_t	sts;
	char		*work;

	sts = this->FindBool("MCHffws", &(head->ffws));
	if(sts != B_NO_ERROR) head->ffws = true;
	sts = this->FindBool("MCHcdfws", &(head->fcdfws));
	if(sts != B_NO_ERROR) head->fcdfws = false;
	sts = this->FindBool("MCHfspos", &(head->fspos));
	if(sts != B_NO_ERROR) head->fspos = true;
	sts = this->FindBool("MCHindeskbar", &(head->findeskbar));
	if(sts != B_NO_ERROR) head->findeskbar = false;
	sts = this->FindBool("MCHconfirm", &(head->fconfirm));
	if(sts != B_NO_ERROR) head->fconfirm = true;
	sts = this->FindBool("MCHdblckedit", &(head->fdblckedit));
	if(sts != B_NO_ERROR) head->fdblckedit = false;
	sts = this->FindString("MCHfamily", (const char**) &work);
	if(sts != B_NO_ERROR)
	{
		font_family	ff;
		font_style	fs;
		be_plain_font->GetFamilyAndStyle(&ff, &fs);
		strcpy(head->family, ff);
	}
	else
	{
		strcpy(head->family, work);
	}
	sts = this->FindInt32("MCHfsize", &(head->fsize));
	if(sts != B_NO_ERROR) head->fsize = 10;
	sts = this->FindInt8("MCHred", (int8*) &(head->ccolor.red));
	if(sts != B_NO_ERROR) head->ccolor.red = 255;
	sts = this->FindInt8("MCHgreen", (int8*) &(head->ccolor.green));
	if(sts != B_NO_ERROR) head->ccolor.green = 255;
	sts = this->FindInt8("MCHblue", (int8*) &(head->ccolor.blue));
	if(sts != B_NO_ERROR) head->ccolor.blue = 255;
	head->ccolor.alpha = 255;
	sts = this->FindInt32("MCHnumchips", &(head->numchips));
	if(sts != B_NO_ERROR) head->numchips = 0;

	return B_NO_ERROR;
}


/////
// archiving MemoChip data detail
//
status_t MCArchive::AddChipData(
	MCDataDetail	*data)
{
	status_t	sts;

	sts = this->AddBool("MCDffws", data->ffws);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddString("MCDfamily", data->family);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt32("MCDfsize", data->fsize);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt8("MCDred", data->ccolor.red);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt8("MCDgreen", data->ccolor.green);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt8("MCDblue", data->ccolor.blue);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddInt32("MCDwspace", data->wspace);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddRect("MCDframe", data->frame);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddString("MCDname", data->name);
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->AddString("MCDdata", data->data);
	if(sts != B_NO_ERROR) goto ERR;

	return B_NO_ERROR;

ERR:
	return sts;
}


/////
// find MemoChip data detail
//
status_t MCArchive::FindChipData(
	int32			idx,
	MCDataDetail	*data)
{
	status_t	sts;
	char		*work;
	char		defname[] = {"chip"};

	sts = this->FindBool("MCDffws", idx, &(data->ffws));
	if(sts != B_NO_ERROR) data->ffws = false;
	sts = this->FindString("MCDfamily", idx, (const char**) &work);
	if(sts != B_NO_ERROR)
	{
		font_family	ff;
		font_style	fs;
		be_plain_font->GetFamilyAndStyle(&ff, &fs);
		strcpy(data->family, ff);
	}
	else
	{
		strcpy(data->family, work);
	}
	sts = this->FindInt32("MCDfsize", idx, &(data->fsize));
	if(sts != B_NO_ERROR) data->fsize = 10;
	sts = this->FindInt8("MCDred", idx, (int8*) &(data->ccolor.red));
	if(sts != B_NO_ERROR) data->ccolor.red = 255;
	sts = this->FindInt8("MCDgreen", idx, (int8*) &(data->ccolor.green));
	if(sts != B_NO_ERROR) data->ccolor.green = 255;
	sts = this->FindInt8("MCDblue", idx, (int8*) &(data->ccolor.blue));
	if(sts != B_NO_ERROR) data->ccolor.blue = 255;
	data->ccolor.alpha = 255;
	sts = this->FindInt32("MCDwspace", idx, (int32*) &(data->wspace));
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->FindRect("MCDframe", idx, &(data->frame));
	if(sts != B_NO_ERROR) goto ERR;
	sts = this->FindString("MCDname", idx, (const char**) &work);
	if(sts != B_NO_ERROR) work = defname;
	if(data->name != NULL)
	{
		delete[] data->name;
	}
	data->name = new char[strlen(work) + 1];
	strcpy(data->name, work);
	sts = this->FindString("MCDdata", idx, (const char**) &work);
	if(sts != B_NO_ERROR) goto ERR;
	if(data->data != NULL)
	{
		delete[] data->data;
	}
	data->data = new char[strlen(work) + 1];
	strcpy(data->data, work);

	return B_NO_ERROR;

ERR:
	return sts;
}
