/*
	============================================================================

	Module Name:        PSQLviaADOCPP.cpp

	Executable Name:    PSQLviaADOCPP.exe

	Module Objective:   This application demonstrates basic CRUD operations,
						which were once called ACID operations, on a Pervacive
						SQL (BTrieve) data base, using the ADODB data provider,
						through COM.

	Remarks:			This is a port of PSQLviaADOCPPCS, version 1.4, from C#.

						This file contains the main function. Program execution
						begins and ends there.
	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       Version By Description
	---------- ------- ---------------------------------------------------------
	2019/07/30 1,0,0,1 DG First version, severely simplified
	============================================================================
*/

#include ".\PSQLviaADOCPP.h"

static const char   m_achrStrfTimeLocalFormatString [ ]	= STRFTIME_DEFAULT_LOCAL_FORMAT;
static const char   m_achrStrfTimeUTCFormatString   [ ]	= STRFTIME_DEFAULT_UTC_FORMAT;

static const char * m_lpStrfTimeLocalFormatString		= ( char * ) &m_achrStrfTimeLocalFormatString;
static const char * m_lpStrfTimeUTCFormatString			= ( char * ) &m_achrStrfTimeUTCFormatString;

CRTWaitForCarbonUnit m_utpWFCU;

int main ( int argc , char * argv [ ] )
{
	m_utpWFCU.dwDuration				= WFCU_BELL_DFLT_DURATION;
	m_utpWFCU.dwFreqquency				= WFCU_BELL_DFLT_FREQUENCY;

	char * lpszProgramName				= ShowProgramInfo ( SHOWPROGRAMINFO_ON_STDERR );
	char * lpFormattedStartTimeLocal	= FormatNowLocal ( ( void* ) m_lpStrfTimeLocalFormatString ,
											                NULL );

	Unless ( lpFormattedStartTimeLocal )
		return GetLastError ( );

	LPTSTR  lpFormattedStartTimeUTC = FormatNowUTC ( ( void * ) m_lpStrfTimeUTCFormatString ,
		                                             NULL );

	Unless ( lpFormattedStartTimeUTC )
		return GetLastError ( );

	_tprintf ( "Execution start time %s (%s)\n\n",
		       lpFormattedStartTimeLocal ,
		       lpFormattedStartTimeUTC );

	try
	{
		DoTask ( argc ,
			     argv ,
			     lpszProgramName );
	}
	catch ( const std::exception ex )
	{
		printf ( "Exception caught in main routine: %s\n\n",
			     ( const char * ) ex.what ( ) );
		m_utpWFCU.intReturnCode = ERROR_RUNTIME;
	}

	if ( m_utpWFCU.intReturnCode )
	{
		printf ( "%s ended abnormally with status code 0x%08x (%i decimal)\n\n" ,
			     lpszProgramName ,
				 m_utpWFCU.intReturnCode,
				 m_utpWFCU.intReturnCode);
	}	// if ( m_utpWFCU.intReturnCode )

	return	WaitForCarbonUnit ( &m_utpWFCU );
}	// int main ( int argc , char* argv [ ] )


void __stdcall DoTask ( int pintArgC , char * pachrArgV [ ] , char * plpszProgramName )
{
	CoInitialize ( NULL );
	_RecordsetPtr pRs ("ADODB.Recordset");
	_ConnectionPtr pCn ("ADODB.Connection");
	_variant_t vtTableName ("authors"), vtCriteria;
	printf ( "%s Done\n\n",
		     plpszProgramName );
}	// void __stdcall DoTask


void __stdcall EmitConsoleBeep ( )
{
	Beep ( m_utpWFCU.dwFreqquency
			? m_utpWFCU.dwFreqquency
			: WFCU_BELL_DFLT_FREQUENCY ,
		   m_utpWFCU.dwDuration
			? m_utpWFCU.dwDuration
			: WFCU_BELL_DFLT_DURATION );
}	// void __stdcall EmitConsoleBeep