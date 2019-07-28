/*
	============================================================================

	Module Name:        PSQLviaADO.cpp

	Executable Name:    PSQLviaADO.exe

	Module Objective:   This application demonstrates basic CRUD operations,
						which were once called ACID operations, on a Pervacive
						SQL (BTrieve) data base, using the ADODB data provider,
						through COM.

	Remarks:			This is a port of PSQLviaADOCS, version 1.4, from C#.

						This file contains the main function. Program execution
						begins and ends there.
	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       Version By Description
	---------- ------- ---------------------------------------------------------
	2019/07/27 1.4.0.1 DG Revise the naming scheme for managed resource strings.
	============================================================================
*/

#include ".\PSQLviaADO.h"

static const char m_achrStrfTimeLocalFormatString[] = STRFTIME_DEFAULT_LOCAL_FORMAT;
static const char m_achrStrfTimeUTCFormatString[] = STRFTIME_DEFAULT_UTC_FORMAT;

static const char* m_lpStrfTimeLocalFormatString = (char*)& m_achrStrfTimeLocalFormatString;
static const char* m_lpStrfTimeUTCFormatString = (char*)& m_achrStrfTimeUTCFormatString;

int main ( int argc , char* argv [ ] )
{
	int intRetCode = ERROR_SUCCESS;
	char* lpszProgramName = ShowProgramInfo ( SHOWPROGRAMINFO_ON_STDERR );

	char* lpFormattedStartTimeLocal = FormatNowLocal  ( ( void* ) m_lpStrfTimeLocalFormatString ,
		                                             NULL );

	if (lpFormattedStartTimeLocal == NULL)
		return GetLastError ();

	LPTSTR  lpFormattedStartTimeUTC = FormatNowUTC ( ( void * ) m_lpStrfTimeUTCFormatString ,
		                                             NULL );

	Unless ( lpFormattedStartTimeUTC )
		return GetLastError ();

	_tprintf ( "Execution start time %s (%s)\n\n",
		       lpFormattedStartTimeLocal,
		       lpFormattedStartTimeUTC);

	return intRetCode;
}	// int main ( int argc , char* argv [ ] )