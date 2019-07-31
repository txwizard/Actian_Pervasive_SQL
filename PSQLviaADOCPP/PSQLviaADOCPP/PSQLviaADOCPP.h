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
						SQL (BTrieve) data base, using the Btrieve2 native API.

	Remarks:			This file contains the declarations required to bind the
						other source files into a complete program without any
						unresolved external references.

	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       Version By Description
	---------- ------- ---------------------------------------------------------
	2019/07/31 1,0,0,1 DG First version, severely simplified
	============================================================================
*/

#include <StandardMacros_DAG.H>			// My standard preprocessor macros

#include <exception>					// Declare std::exception and its cousins.

#include <btrieveCpp.h>					// BTrieve2 declarations for CPP programs

#include <CRTTime.H>					// Custom CRT time formatting functions built around strftime
#include <NativeConssoleAppAids.h>		// Custom routines for parsing command lines, displaying version info, etc.
#include <NativeStringAids.h>			// Custom string processing routines

#define SHOWPROGRAMINFO_ON_STDERR		TRUE
#define ERROR_RUNTIME					PLUS_ONE_P6C
#define ERROR_BAD_VERB					( ERROR_RUNTIME + ARRAY_NEXT_ELEMENT_P6C )

void __stdcall DoTask                  ( int pintArgC , char * pachrArgV [ ] , char* plpszProgramName );
void __stdcall EmitConsoleBeep         ( );
#endif // PSQLVIAADOCPPCPP_H