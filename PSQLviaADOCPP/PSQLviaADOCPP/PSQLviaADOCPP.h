#if !defined ( PSQLVIAADOCPPCPP_H )
#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif	/* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

/*
	============================================================================

	File Name:			PSQLviaADOCPP.h

	Module Name:        PSQLviaADOCPP.cpp

	Executable Name:    PSQLviaADOCPP.exe

	Module Objective:   This application demonstrates basic CRUD operations,
						which were once called ACID operations, on a Pervacive
						SQL (BTrieve) data base, using the ADODB data provider,
						through COM.

	Remarks:			This is a port of PSQLviaADOCPPCS, version 1.4, from C#.

						This file contains the declarations required to bind the
						other source files into a complete program without any
						unresolved external references.

	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       Version By Description
	---------- ------- ---------------------------------------------------------
	2019/07/30 1,0,0,1 DG First version, severely simplified
	============================================================================
*/


#if defined ( RC_INVOKED )
	#pragma message ( "Skipping unnecessary parts of " __FILE__ )
#else
	#include <StandardMacros_DAG.H>							// My standard preprocessor macros
	#include <exception>
	#include <comdef.h>										// Main COM declarations, which auto-includes comutil.h

	#import "msado15.dll" no_namespace rename ( "EOF" , "EndOfFile" )

	typedef ADODB::_ConnectionPtr CnnPtr;
	typedef ADODB::_RecordsetPtr  RecPtr;

	#include <CRTTime.H>									// Custom CRT time formatting functions built around strftime
	#include <NativeConssoleAppAids.h>						// Custom routines for parsing command lines, displaying version info, etc.
	#include <NativeStringAids.h>							// Custom string processing routines


	#define SHOWPROGRAMINFO_ON_STDERR	TRUE
	#define ERROR_RUNTIME				PLUS_ONE_P6C
	#define ERROR_BAD_VERB				( ERROR_RUNTIME + ARRAY_NEXT_ELEMENT_P6C )

	void                __stdcall DoTask                  ( int pintArgC , char * pachrArgV [ ] , char* plpszProgramName );
	void                __stdcall EmitConsoleBeep         ( );
#endif // RC_INVOKED
#endif // PSQLVIAADOCPPCPP_H
