#if !defined ( _NATIVESTRINGAIDS_DEFINED )
#define _NATIVESTRINGAIDS_DEFINED

/*
	============================================================================

	File Name:          NativeStringAids.h

	File Synopsis:      This C/C++ header file defines the functions exported by
						NativeConssoleAppAids.dll, along with a few symbolic
						constants used by it.

	Remarks:            These functions were defined and tested for the projects
						that I created to port three open source libraries, zlib,
						iconv, and libxml2, to the ARM processor.

	Date Created:       Tuesday, 19 March 2019

	License:            Copyright (C) 2019, David A. Gray. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	*   Redistributions of source code must retain the above copyright notice,
	this list of conditions and the following disclaimer.

	*   Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.

	*   Neither the name of David A. Gray nor the names of his contributors may
	be used to endorse or promote products derived from this software without
	specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL David A. Gray BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       Version By  Synopsis	RCDATA_MAX_BUFFER_P6C
	---------- ------- --- -----------------------------------------------------
	2019/04/09 1.0.0.1 DAG Extract from NativeConssoleAppAids.
	============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#if defined ( NATIVESTRINGAIDS_EXPORTS )
	#define LIBSPEC_NATIVESTRINGAIDS_API __declspec(dllexport) __stdcall
#else
	#define LIBSPEC_NATIVESTRINGAIDS_API __declspec(dllimport) __stdcall
#endif	/* NATIVESTRINGAIDS_EXPORTS */

typedef enum _STATUS_CODE_FORMAT2
{
	SCF2_HEXADECIMAL ,   // 0
	SCF2_DECIMAL ,       // 1
	SCF2_OCTAL           // 2
} STATUS_CODE_FORMAT2;

//  ----------------------------------------------------------------------------
//  Define specialized constants for use as arguments.
//
//  NOTE:   A console program has a null instance handle, A NULL instance handle
//          is a signal to GetStringPointer() to look for the requested resource
//          in the EXE that was first loaded into the process. FB_HIDE_LENGTH,
//          likewise, signals that the length of the string should be discarded.
//  ----------------------------------------------------------------------------

#define FB_HIDE_LENGTH					0x00000000
#define FB_LOOK_IN_THIS_EXE             0x00000000

#define FB_SCF2_HEXADECIMAL             SCF2_HEXADECIMAL
#define FB_SCF2_DECIMAL                 SCF2_DECIMAL
#define FB_SCF2_OCTAL                   SCF2_OCTAL

typedef const unsigned int              FB_RES_STRING_ID;
typedef       STATUS_CODE_FORMAT2       FB_STATUS_CODE_FORMAT2;
typedef const STATUS_CODE_FORMAT2       CSTATUS_CODE_FORMAT2;
typedef const FB_STATUS_CODE_FORMAT2    CFB_STATUS_CODE_FORMAT2;

#if !defined ( _CONST_TYPEDEFS_WW_INCLUDED )
	typedef const DWORD					CDWORD;
	typedef const INT					CINT;
	typedef const HMODULE               CHMODULE;
	typedef unsigned int * const        CLPUINT;
	typedef const unsigned int          CUINT;
	typedef const unsigned int          RES_STRING_ID;
#endif	/* #if !defined ( _CONST_TYPEDEFS_WW_INCLUDED ) */

#define GFV_SUCCEEDED					0x00000000
#define GFV_GETFILEVERSIONINFOSIZE_FAIL	0x00000001
#define GFV_GETFILEVERSIONINFO_FAIL		0x00000002
#define GFV_VERQUERYVALUE_FAIL			0x00000003

#define IBF_USE_DEFAULT_HEAP            NULL
#if defined ( __cplusplus )
extern "C" {
#endif  /* #if defined ( __cplusplus ) */
	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API FB_FindLineEndA
	(
		LPCTSTR              plpString ,
		CINT                 pintPosEnd
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API FB_FindLineEndW
	(
		LPCTSTR              plpString ,
		CINT                 pintPosEnd
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API FB_FormatMessageA
	(
		LPCTSTR              plpHint ,											// Pointer to string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API FB_FormatMessageW
	(
		LPCTSTR              plpHint ,											// Pointer to string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);


	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API FB_FormatMessage2A
	(
		RES_STRING_ID		 puintStringID ,									// Resource ID of string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API FB_FormatMessage2W
	(
		RES_STRING_ID		 puintStringID ,									// Resource ID of string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);

	DWORD LIBSPEC_NATIVESTRINGAIDS_API FB_ProcessStatusCode
	(
		CDWORD pdwLastError														// Status code to establish, or NO_ERROR (zero) to cause GetLastError to be called
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      GetExeHameFromWindows
	//
	//  Abstract:           Get a pointer to a null terminated string that holds
	//                      the absolute (fully qualified) name of the first
	//                      program file that was loaded into the current
	//                      process.
	//
	//  In:                 This function takes no arguments.
	//
	//  Out:                If it succeeds, the return value is a pointer to the
	//                      desired null terminated Unicode program name string.
	//
	//  Remarks:            Since this routine supports only Unicode strings, it
	//                      has a return type of LPWSTR.
	//  ------------------------------------------------------------------------

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API GetExeHameFromWindowsA ( );

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API GetExeHameFromWindowsW ( );


	//  ------------------------------------------------------------------------
	//  Function Name:      GetFileVersion
	//
	//  Abstract:           Get a pointer to a null terminated string that holds
	//                      the numerical version number string stored in the
	//                      program file named in its first argument.
	//
	//  In:                 plpOutBuf				= Pointer to buffer to
	//                                                receive the formatted full
	//                                                version number string as
	//                                                up to pintOutBufSize - 1
	//                                                wide characters
	//
	//						pintOutBufSize			= Capacity of buffer
	//                                                plpOutBuf, in wide
	//                                                characters
	//
	//                      plpAbsoluteExeFileName	= Pointer to string that
	//                                                contains the absolute
	//                                                (fully qualified) name of
	//                                                the program file
	//
	//  Out:                If it succeeds, the return value is a pointer to the
	//                      desired null terminated Unicode numerical program
	//						version sring.
	//
	//  Remarks:            Since this routine runs in a character mode host, it
	//						writes its result on the console output string, and
	//						returns a status code, which is expected to be zero.
	//  ------------------------------------------------------------------------

	int     LIBSPEC_NATIVESTRINGAIDS_API GetFileVersionA
	(
		LPTSTR			plpOutBuf ,							// Pointer to buffer to receive formatted full version number string as up to pintOutBufSize - 1 wide characters
		CINT			pintOutBufSize ,					// Capacity of buffer plpOutBuf in wide characters
		LPCTSTR         plpAbsoluteExeFileName				// Pointer to string containing the absolute (fully qualified) name of the program file
	);

	int     LIBSPEC_NATIVESTRINGAIDS_API GetFileVersionW
	(
		LPTSTR			plpOutBuf ,							// Pointer to buffer to receive formatted full version number string as up to pintOutBufSize - 1 wide characters
		CINT			pintOutBufSize ,					// Capacity of buffer plpOutBuf in wide characters
		LPCTSTR         plpAbsoluteExeFileName				// Pointer to string containing the absolute (fully qualified) name of the program file
	);



	//  ------------------------------------------------------------------------
	//  Function Name:      GetANSIStringPointer (ANSI, narrow characters)
	//						GetUnicodeStringPointer (Unicode, wide characters)
	//
	//  Abstract:           Get a pointer to a null terminated string resource
	//                      for use, in situ, by any routine that deals in such
	//                      strings.
	//
	//						IMPORTANT:	Since GetANSIStringPointer must use an
	//									output buffer, and it is common for two
	//									or more strings to be used together,
	//									such as a format string and a token
	//									replacement string being fed into printf
	//									or one of its kin, it allocates a buffer
	//									from the default process heap. Unless
	//									your code discards it, your program will
	//									leak 4098 bytes of memory per abandoned
	//									buffer.
	//
	//  In:                 phSourceModule	= either the instance handle of the
	//                                        the module from which the string
	//                                        was expected to be read, or NULL,
	//                                        indicating that the source is the
	//                                        first PE file that was loaded into
	//                                        the current process.
	//
	//                      puintStringID	= the unsigned integer resource
	//                                        (string) ID that was sought.
	//
	//                      plpuintLength	= the location where the length of
	//                                        of the returned string should be
	//                                        written, if the calling routine
	//                                        needs it. Otherwise, the pointer
	//                                        may be NULL.
	//
	//  Out:                If it succeeds, the return value is a pointer to the
	//                      desired null terminated Unicode string resource. If
	//                      the desired string cannot be found in the specified
	//                      module, the return value is NULL, and a call to
	//                      GetLastError should give some hint about why the
	//                      call failed.
	//
	//  Remarks:            Since this routine supports only Unicode strings, it
	//                      has a return type of LPWSTR.
	//
	//                      The documented return value of LoadString excludes
	//                      the trailing null from the reported string length.
	//                      However, when nBufferMax = RCDATA_INPLACE_POINTER,
	//                      it is included. Hence, for consistency, this routine
	//                      deducts one from the return value when reporting the
	//                      length of the string.
	//  ------------------------------------------------------------------------

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API GetANSIStringPointer
	(
		CHMODULE        phSourceModule ,					// HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		RES_STRING_ID	puintStringID ,						// Resource ID of string to load
		CLPUINT         plpuintLength						// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API GetUnicodeStringPointer
	(
		CHMODULE        phSourceModule ,					// HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		RES_STRING_ID	puintStringID ,						// Resource ID of string to load
		CLPUINT         plpuintLength						// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API GetStringFromNamedDllA
	(
		LPCTSTR         plpDLLName ,						// Pointer to string containing name of a resource DLL
		RES_STRING_ID	puintStringID ,						// Resource ID of string to load
		CLPUINT         plpuintLength						// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API GetStringFromNamedDllW
	(
		LPCTSTR         plpDLLName ,						// Pointer to string containing name of a resource DLL
		RES_STRING_ID	puintStringID ,						// Resource ID of string to load
		CLPUINT         plpuintLength						// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
	);

	//  ------------------------------------------------------------------------
	//  Function Name:      ProgramIDFromArgV
	//
	//  Abstract:           Get a pointer to a null terminated string resource
	//                      for use, in situ, by any routine that deals in such
	//                      strings.
	//
	//  In:                 plpszArg0    	= pointer to argv [0], which always
	//                                        contains the name of the program
	//                                        that started the process
	//
	//  Out:                If it succeeds, the return value is a pointer to a
	//                      null terminated Unicode string that conatins the
	//                      base name of the program, with both its path and its
	//                      extension removed.
	//
	//  Remarks:            Since this routine supports only Unicode strings, it
	//                      has a return type of LPWSTR.
	//  ------------------------------------------------------------------------

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API ProgramIDFromArgVA
	(
		LPCTSTR			plpszArg0							// Pointer to argv [0], which always contains the name of the program that started the process
	);

	LPTSTR LIBSPEC_NATIVESTRINGAIDS_API ProgramIDFromArgVW
	(
		LPCTSTR			plpszArg0							// Pointer to argv [0], which always contains the name of the program that started the process
	);

	//  ------------------------------------------------------------------------
	//  Function Name:      ReportSystemError
	//
	//  Abstract:           Use FormatMessage to translate the system status code
	//						returned by a system (Windows API) routine into a
	//						message for consumption by carbon units.
	//
	//  In:                 pintFinalReturnCode	= the value to pass through and
	//                                            report to Windows as the final
	//                                            status code of the program
	//
	//  Out:                This function always returns its input value.
	//
	//  Remarks:            Since this routine runs in a character mode host, it
	//						writes its result on the console output string, and
	//						returns a status code, which is expected to be zero.
	//  ------------------------------------------------------------------------

	int     LIBSPEC_NATIVESTRINGAIDS_API ReportSystemErrorA
	(
		CINT            pintFinalReturnCode ,
		RES_STRING_ID   puintResStringId
	);

	int     LIBSPEC_NATIVESTRINGAIDS_API ReportSystemErrorW
	(
		CINT            pintFinalReturnCode ,
		RES_STRING_ID   puintResStringId
	);
#if defined ( __cplusplus )
}   /* ... extern "C" */
#endif  /* #if defined ( __cplusplus )    */

#if defined ( UNICODE )
	#define FB_FindLineEnd			FB_FindLineEndW
	#define FB_FormatMessage		FB_FormatMessageW
	#define FB_FormatMessage2		FB_FormatMessage2W
	#define GetExeHameFromWindows	GetExeHameFromWindowsW
	#define GetFileVersion			GetFileVersionW
	#define GetStringPointer		GetUnicodeStringPointer
	#define GetStringFromNamedDll	GetStringFromNamedDllW
	#define ProgramIDFromArgV		ProgramIDFromArgVW
	#define ReportSystemError		ReportSystemErrorW
#else
	#define FB_FindLineEnd			FB_FindLineEndA
	#define FB_FormatMessage		FB_FormatMessageA
	#define FB_FormatMessage2		FB_FormatMessage2A
	#define GetExeHameFromWindows	GetExeHameFromWindowsA
	#define GetFileVersion			GetFileVersionA
	#define GetStringPointer		GetANSIStringPointer
	#define GetStringFromNamedDll	GetStringFromNamedDllA
	#define ProgramIDFromArgV		ProgramIDFromArgVA
	#define ReportSystemError		ReportSystemErrorA
#endif	/* #if defined ( UNICODE ) */
#endif /* #if !defined ( _NATIVESTRINGAIDS_DEFINED ) */