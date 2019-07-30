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
	2019/07/27 1,4,1,0 DG This is the version of the C# source that I ported.
	============================================================================
*/

#include ".\PSQLviaADO.h"

static const char m_achrStrfTimeLocalFormatString [ ]	= STRFTIME_DEFAULT_LOCAL_FORMAT;
static const char m_achrStrfTimeUTCFormatString   [ ]	= STRFTIME_DEFAULT_UTC_FORMAT;

static const char* m_lpStrfTimeLocalFormatString		= ( char * ) &m_achrStrfTimeLocalFormatString;
static const char* m_lpStrfTimeUTCFormatString			= ( char * ) &m_achrStrfTimeUTCFormatString;

CRTWaitForCarbonUnit m_utpWFCU;

int main ( int argc , char* argv [ ] )
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
		DoTask ( argc , argv );
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


void __stdcall DoTask ( int pintArgC , char * pachrArgV [ ] )
{
	FILE hfDetailsList;
	FILE hfDetailsTable;
	OperatingParameters params;

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


CrudVerb __stdcall EvaluateCrudVerb ( char * pstrVerb )
{

	return List;
}   // private static CrudVerb EvaluateCrudVerb


OperatingParameters __stdcall GetOperatingParamerters ( int pintArgC , char* pachrArgV [ ] )
{
	#define ARG_COUNT_NONE				CMDLINE_FIRST_ARG_P6C
	#define ARG_COUNT_TABLE_NAME		( ARG_COUNT_NONE       + ARRAY_NEXT_ELEMENT_P6C )
	#define ARG_COUNT_CRUD_VERB			( ARG_COUNT_TABLE_NAME + ARRAY_NEXT_ELEMENT_P6C )

	#define ARG_TABLE_NAME				CMDLINE_FIRST_ARG_P6C
	#define ARG_CRUD_VERB				( ARG_TABLE_NAME       + ARRAY_NEXT_ELEMENT_P6C )

	char * strErrorPrompt				= NULL;
	char * strPrompt					= NULL;
	char * strTableNameCandidate		= NULL;
	char * strVerbCandidate				= NULL;
//	WizardWrx.ConsoleStreams.ErrorMessagesInColor messagesInColor = null;

	OperatingParameters rparameters;

	switch (pintArgC)
	{
		case ARG_COUNT_NONE:
			break;
		case ARG_COUNT_TABLE_NAME:
			strTableNameCandidate		= pachrArgV [ ARG_TABLE_NAME ];
			break;
		case ARG_COUNT_CRUD_VERB:
			strTableNameCandidate		= pachrArgV [ ARG_TABLE_NAME ];
			strVerbCandidate			= pachrArgV [ ARG_CRUD_VERB  ];
			break;
		default:
			strTableNameCandidate		= pachrArgV [ ARG_TABLE_NAME ];
			strVerbCandidate			= pachrArgV [ ARG_CRUD_VERB  ];
		break;
	}   // switch ( pastrArgs.Length )

	if (File.Exists (DeriveTableSchemaFQFN (strTableNameCandidate)))
	{
		rparameters.TableName = strTableNameCandidate;
	}
	else
	{
		//messagesInColor = new WizardWrx.ConsoleStreams.ErrorMessagesInColor (
		//	s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageForegroundColor,
		//	s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageBackgroundColor);

		//if (strErrorPrompt == null)
		//{   // Defer loading until needed.
		//	strErrorPrompt = Properties.Resources.MSG_ERR_INVALID_NAME;
		//}   // if ( strErrorPrompt == null )

		//messagesInColor.WriteLine (
		//	strErrorPrompt,                                        // Format control string read from managed resource table
		//	strTableNameCandidate.QuoteString (),				   // Format Item 0: Table name {0}
		//	Environment.NewLine);                                  // Format Item 1: {1}Table ... is invalid.{1}
	}   // if ( messagesInColor == null )

	while ( rparameters.TableName == NULL )
	{
		strPrompt = strPrompt ? strPrompt : LoadMessage ( NULL , MSG_PROMPT_FOR_TABLE_NAME);
		fprintf ( stderr ,
			      strPrompt );
		EmitConsoleBeep ( );

		strTableNameCandidate = strTableNameCandidate 
								? strTableNameCandidate
								: ( char* ) HeapAlloc ( GetProcessHeap ( ) ,
                                                        HEAP_ZERO_MEMORY ,
			                                            TINY_SCRATCH_BUFFER_256 );

		Unless ( strTableNameCandidate )
		{	// Game over: Windows is out of memory.
			SetLastError (ERROR_OUTOFMEMORY);
			m_utpWFCU.intReturnCode = ERROR_OUTOFMEMORY;
			return rparameters;
		}	// Unless ( strTableNameCandidate )

		if (File.Exists (DeriveTableSchemaFQFN (strTableNameCandidate)))
		{
			rparameters.TableName = strTableNameCandidate;
		}   // TRUE (desired outcome) block, if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
		else
		{   // Perform just-in-time object initializations.
			Unless ( strErrorPrompt )
			{   // Defer loading until needed.
				strErrorPrompt = LoadMessage ( NULL ,
					                           MSG_ERR_INVALID_NAME );

				Unless ( strErrorPrompt )
				{
					m_utpWFCU.intReturnCode = ReportSystemErrorOnConsole ( NULL , 
						                                                   NO_ERROR );
				}	// Unless ( strErrorPrompt )
			}   // Unless ( strErrorPrompt )

			//if (messagesInColor == null)
			//{   // Defer creation until needed.
			//	messagesInColor = new WizardWrx.ConsoleStreams.ErrorMessagesInColor (
			//		s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageForegroundColor,
			//		s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageBackgroundColor);
			//}   // if ( messagesInColor == null )

			//messagesInColor.WriteLine (
			//	strErrorPrompt,                                        // Format control string read from managed resource table
			//	strTableNameCandidate.QuoteString (),                 // Format Item 0: Table name {0}
			//	Environment.NewLine);                                  // Format Item 1: {1}Table ... is invalid.{1}
		}   // FALSE (undesired outcome) block, if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
	}   // while ( rparameters.TableName == NULL )

	if ( pintArgC > ARG_CRUD_VERB )
	{
		rparameters.Verb = EvaluateCrudVerb ( pachrArgV [ ARG_CRUD_VERB ] );

		if ( m_utpWFCU.intReturnCode == ERROR_BAD_VERB )
		{
			return rparameters;
		}   // if ( s_csm.BaseStateManager.AppReturnCode == ERROR_BAD_VERB )
	}   // TRUE (The verb is in the command tail.) block, if ( m_utpWFCU.intReturnCode == ERROR_BAD_VERB )
	else
	{   // ToDo: Add code to prompt for verb.
	}   // FALSE (The command tail omits a verb.) block, if ( pintArgC > ARG_CRUD_VERB )

	Console.WriteLine (
		Properties.Resources.MSG_DISPLAY_TABLE_NAME_AND_VERB,      // Format control string read from managed resource table
		rparameters.TableName,                                         // Format Item 0: Processing PSQL database table {0}
		rparameters.Verb,                                              // Format Item 1: Action Taken = {1}
		Environment.NewLine);                                          // Format Item 1: Platform depdent newline database table {0}{2} AND Action Taken = {1}{2}

	return rparameters;
}   // private static string GetOperatingParamerters