#if !defined ( PSQLVIAADOCPP_H )
#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif	/* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

/*
	============================================================================

	File Name:			PSQLviaADO.h

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
	2019/07/29 1.4.1.0 DG Port from the inidcated version of PSQLviaADOCS, the
	                      Visual C# implementation.
	============================================================================
*/


#if defined ( RC_INVOKED )
	#pragma message ( "Skipping unnecessary parts of " __FILE__ )
#else
	#include <StandardMacros_DAG.H>							// My standard preprocessor macros
	#include <exception>
	#include <comdef.h>										// Main COM declarations, which auto-includes comutil.h

	#import "msado15.dll" no_namespace rename ( "EOF" , "EndOfFile" )

	#include <CRTTime.H>									// Custom CRT time formatting functions built around strftime
	#include <NativeConssoleAppAids.h>						// Custom routines for parsing command lines, displaying version info, etc.
	#include <NativeStringAids.h>							// Custom string processing routines

	#include ".\MessageResourceHelpers.h"
	#include ".\res\PSQLviaADO.h"

	#define SHOWPROGRAMINFO_ON_STDERR	TRUE
	#define ERROR_RUNTIME				PLUS_ONE_P6C
	#define ERROR_BAD_VERB				( ERROR_RUNTIME + ARRAY_NEXT_ELEMENT_P6C )

	enum AddOrUpdateMode
	{
		AddingOneRow,
		UpdatingOneRow
	};   // enum AddOrUpdateMode

	enum CrudVerb
	{
		List,
		Create,
		Read,
		Update,
		Delete,
		TableProperties
	};   // enum CrudVerb

	enum OutputFileType
	{
		DetailListReport,
		DetailTabularReport,
		TablePropertiesReport
	};   // enum OutputFileType

	enum WhereCondition
	{
		Undspecified,
		IsEqualTo,
		IsLikeContains,
		IsLikePrefix,
		IsLikeSuffix,
	};   // enum WhereCondition

	struct OperatingParameters
	{
		char *			TableName;
		CrudVerb		Verb;
	};   // struct OperatingParameters


	struct SelectionCriteria
	{
		WhereCondition	Condition;
		char *			CriterionValue;
		FieldPtr		MatchfieldInfo;
	};   // struct SelectionCriteria

	void                __stdcall DoTask                  ( int pintArgC , char * pachrArgV [ ] );
	void                __stdcall EmitConsoleBeep         ( );
	CrudVerb __stdcall EvaluateCrudVerb (char* pstrVerb);
	OperatingParameters __stdcall GetOperatingParamerters ( int pintArgC , char * pachrArgV [ ] );
#endif // RC_INVOKED
#endif // PSQLVIAADOCPP_H
