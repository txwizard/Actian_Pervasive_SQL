#if !defined ( PSQLVIAADOCPP_H )
#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif	/* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

/*
	============================================================================

	Module Name:        PSQLviaADO.cpp

	Executable Name:    PSQLviaADO.exe

	Module Objective:   This application demonstrates basic CRUD operations,
						which were once called ACID operations, on a Pervacive
						SQL (BTrieve) data base, using the ADODB data provider,
						through COM.

	Remarks:			This is a port of PSQLviaADOCS, version 1.4, from C#.

						This file contains the declarations required to bind the
						other source files into a complete program without any
						unresolved external references.

	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       Version By Description
	---------- ------- ---------------------------------------------------------
	2019/07/27 1.0.0.1 DG Revise the naming scheme for managed resource strings.
	============================================================================
*/


#if defined ( RC_INVOKED )
	#pragma message ("Skipping unnecessary parts of " __FILE__ )
#else
	#include <StandardMacros_DAG.H>

	#include <CRTTime.H>
	#include <NativeConssoleAppAids.h>
	#include <NativeStringAids.h>

	#define SHOWPROGRAMINFO_ON_STDERR	TRUE
#endif // RC_INVOKED
#endif // PSQLVIAADOCPP_H
