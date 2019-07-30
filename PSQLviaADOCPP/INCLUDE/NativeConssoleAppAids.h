#if !defined ( _NATIVECONSSOLEAPPAIDS_DEFINED )
#define _NATIVECONSSOLEAPPAIDS_DEFINED

/*
	============================================================================

	File Name:          NativeConssoleAppAids.h

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
	2019/03/21 1.0.0.1 DAG Created and first used in VSProjectSettingsTester.exe

	2019/03/22 1.0.0.2 DAG WaitForCarbonUnit added, ProgramIDFromArgV
						   implemented for both ANSI and wide character
						   (Unicode) strings, everything else implemented for
						   ANSI and Unicode strings and all function arguments
						   documented

	2019/03/23 1.0.0.3 DAG GetFileVersion now uses the Windows heap allocators
						   directly, while ProgramIDFromArgV returns through
						   memcpy. The first change eliminates a reliance on the
						   CRT memory allocators, which I seldom use, to avoid
						   the overhead of having the CRT library turn around
						   and call the Windows heap allocators, adding nothing
						   of value. The second change eliminates wasted machine
						   instructions that load a value into the EAX register
						   that memcpy already put there.

	2019/04/03 1.0.0.4 DAG ShowPlatform and ShowProgramInfo get a Boolean flag
						   that is set to TRUE to send its output to the
						   standaard error stream, for use with programs that
						   always write only to the standard output stream.

	2019/04/09 1.0.0.5 DAG Correct a misspelled routine name; WaitForCarbounUnit
						   is intended to be WaitForCarbonUnit. Move symbolic
						   constants for setting CRTWaitForCarbonUnit members to
						   this public header; they were in a privat header.

	2019/07/26 1.0.0.6 DAG Correct typographical errors in the comments. Though
	                       the library is unchanged, this version is built
						   against the tools that ship with Visual Studio 2019.
	============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#if defined ( NATIVECONSSOLEAPPAIDS_EXPORTS )
	#define LIBSPEC_NATIVECONSSOLEAPPAIDS_API __declspec(dllexport) __stdcall
#else
	#define LIBSPEC_NATIVECONSSOLEAPPAIDS_API __declspec(dllimport) __stdcall
#endif	/* NATIVECONSSOLEAPPAIDS_EXPORTS */

//	----------------------------------------------------------------------------
//	Define the CRTWaitForCarbonUnit data structure and a pointer to it for use
//	by calling routines to pass parameters to WaitForCarbonUnit.
//
//	2019/03/22 - DAG - Since pointers are 64-bit entities when the platform is a
//                     64 bit platform, such as x64, but are 32-bit entities on
//                     a classic Win32 (32-bit) platform, I moved lpszMessage
//                     from the top to the bottom of the list, so that the byte
//                     offsets are the same on both platforms.
//	----------------------------------------------------------------------------

#pragma pack ( push , 1 )               // Make the structure as compact as possible.
typedef struct _CRTWaitForCarbonUnit
{
	DWORD   dwDuration;
	DWORD   dwFreqquency;
	int     intReturnCode;
	TCHAR * lpszMessage;
}   CRTWaitForCarbonUnit , FAR * LPCRTWaitForCarbonUnit;
#pragma pack ( pop )

//	----------------------------------------------------------------------------
//	Define symbolic constants for setting the CRTWaitForCarbonUnit members.
//	----------------------------------------------------------------------------

#if defined ( _WIN64 )
#define CONSOLE_INPUT_BUFFER_SIZE   0x0000000000000064

#define WFCU_BELL_DFLT_DURATION     0x00000000000002EE  // 750 milliseconds, for pdwDuration

#define WFCU_BELL_DFLT_FREQUENCY    0x0000000000000370  //    880 hertz, for pdwFreqquency default
#define WFCU_BELL_MAX_FREQUENCY     0x0000000000007FFF  // 32,767 hertz, for pdwFreqquency maximum
#define WFCU_BELL_MIN_FREQUENCY     0x0000000000000025  //     37 hertz, for pdwFreqquency minimum
#else
#define CONSOLE_INPUT_BUFFER_SIZE   0x00000064L

#define WFCU_BELL_DFLT_DURATION     0x000002EEL         // 750 milliseconds, for pdwDuration

#define WFCU_BELL_DFLT_FREQUENCY    0x00000370L         //    880 hertz, for pdwFreqquency default
#define WFCU_BELL_MAX_FREQUENCY     0x00007FFFL         // 32,767 hertz, for pdwFreqquency maximum
#define WFCU_BELL_MIN_FREQUENCY     0x00000025L         //     37 hertz, for pdwFreqquency minimum
#endif  /* #if defined ( _WIN64 ) ) */

#if defined ( __cplusplus )
extern "C" {
#endif  /* #if defined ( __cplusplus ) */
	//  ========================================================================
	//
	//  Function Name:  IsBufFerFromHeap
	//
	//  Synopsis:       Determine whether a pointer belongs to a specified heap.
	//
	//  Status:         Beginning with version 1, 9, 0, 4, this function is no
	//                  longer used internally, and external use is deprecated.
	//                  Please see the Remarks for an explanation of why this is
	//					so.
	//
	//  In:             plpvBuf     = Pointer to buffer to test.
	//
	//                  phHeap      = Handle to heap to be examined. If phHeap
	//                                is NULL, get a handle to the process heap,
	//                                and evaluate it.
	//
	//  Out:            TRUE if buffer plpvBuf belongs to heap phHeap.
	//                  FALSE if buffer plpvBuf belongs to heap phHeap.
	//
	//                  To be on the safe side, return FALSE if any exception
	//                  occurs. See Remarks.
	//
	//                  If IsBufFromHeap_WW returns FALSE, call GetLastError(),
	//                  report the error directly or through FormatMessage(),
	//                  and terminate.
	//
	//  Remarks:        DEPRECATED: The original intent of this function was to
	//                              validate a heap pointer before treating it
	//                              as such. The behavior of the heap routines
	//                              in Windows 7 makes this a bad idea, because
	//                              it runs the risk of raising avoidable
	//                              breakpoint exceptions, even in retail builds
	//                              of the calling code. Since HeapAlloc and
	//                              HeapReAlloc fail with a trappable exception,
	//                              it seems more prudent to go ahead and call
	//                              them, and forgo the pointer sanity check.
	//
	//                  Call this function before you attempt to treat any
	//                  pointer as a heap pointer (e. g., to free the associated
	//                  memory, or reallocate the associated buffer.
	//
	//                  IMPORTANT:  Unless plpvBuf is the address of a memory
	//                              block that was allocated from the default
	//                              process heap, this routine generate the
	//                              following message, when the routine runs in
	//                              a debugger.
	//
	//                                      User breakpoint called from code
	//
	//                              This message cannot be suppressed. However,
	//                              when you acknowledge the message box, your
	//                              code continues to execute normally, but the
	//                              exception is noted in the Debug output
	//                              window.
	//
	//                              Outside a debugger, there is no outward sign
	//                              of this first-chance exception, and the code
	//                              behaves as expected and intended, UNLESS the
	//                              code runs on Windows 7 and newer, which is
	//                              why its use is deprecated, and it has been
	//                              written out of the other routines in this
	//                              library that used it.
	//  ============================================================================

	BOOL LIBSPEC_NATIVECONSSOLEAPPAIDS_API IsBufFerFromHeap
	(
		HANDLE phHeap ,
		LPVOID plpvBuf
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      ShowPlatform
	//
	//  Abstract:           Display the platform (Win32, Win64, ARM, or ARM64 if
	//						the information is supplied through a preprocessor
	//						symbol.
	//
	//  In:                 plpszFormatString	= template (format control)
	//                                            string to use to display the
	//											  platform if it is known
	//
	//  Out:                This function reports via the caller's console
	//						output stream, and has no return value.
	//
	//  Remarks:            Since plpszFormatString is expected to point to the
	//						buffer allocated by GetANSIStringPointer to hold the
	//						message template, this routine  performs at most one
	//                      call to wprintf. If all of the expected preprocessor
	//						symbols are undefined, it displays a message to that
	//                      effect.
	//  ------------------------------------------------------------------------

	void    LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowPlatformA
	(
		LPCTSTR			plpszFormatString ,
		BOOL            pfDirectToStandardError
	);

	void    LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowPlatformW
	(
		LPCTSTR			plpszFormatString,
		BOOL            pfDirectToStandardError
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      ShowProgramInfo
	//
	//  Abstract:           Get a pointer to a null terminated string resource
	//                      for use, in situ, by any routine that deals in such
	//                      strings.
	//
	//  Out:                If it succeeds, the return value is a pointer to a
	//						string that contains the program name. Otherwise, it
	//						returns a NULL pointer to indicate failure.
	//
	//  Remarks:            Since this routine runs in a character mode host, it
	//						writes its result on the console output string, and
	//						returns a status code, which is expected to be zero.
	//  ------------------------------------------------------------------------

	LPTSTR     LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowProgramInfoA
	(
		BOOL pfDirectToStandardError
	);


	LPTSTR     LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowProgramInfoW
	(
		BOOL pfDirectToStandardError
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      WaitForCarbonUnit
	//
	//  Abstract:           Display a prompt, then suspend execution of the
	//						calling routine until a carbon unit (a human being)
	//						presses the RETURN (Enter) key on the keyboard.
	//
	//  In:                 plpCRTWaitForCarbonUnit	= const pointer to the
	//                                                CRTWaitForCarbonUnit data
	//												  structure that provides
	//												  its operating parameters
	//
	//  Out:                If it succeeds, the return value is zero. Otherwise,
	//						it returns a system status code, which may be fed to
	//						the FormatMessage Windows API routine, directly or
	//						through sibling routine FB_FormatMessage.
	//
	//  Remarks:            Since this routine supports ANSI and wide character
	//						prompt strings, it has two implementations which are
	//						otherwise identical.
	//
	//                      The following table describes the values of the four
	//						CRTWaitForCarbonUnit members, of which three are
	//						inputs, while the fourth is a copy of the output.
	//
	//                          ------------------------------------------------
	//                          Type    Name          Usage and Default
	//							------- ------------- --------------------------
	//							TCHAR * lpszMessage   pointer to prompt string,
	//												  for which a default, 
	//												  "Please press the Return 
	//												  (ENTER) key to exit the
	//												  program." is used when
	//                                                lpszMessage is NULL
	//
	//							DWORD   dwDuration    time, in milliseconds, for
	//                                                which to emit the beep
	//                                                that accompanies the
	//                                                prompt, which defaults to
	//                                                750 milliseconds if zero
	//
	//							DWORD   dwFreqquency  frequency, in hertz, of
	//                                                the beep that is emitted
	//                                                to alert an operator to
	//                                                the prompt, which defaults
	//												  to 880 hertz if zero
	//
	//							int     intReturnCode copy of the return code in
	//                                                case the calling routine
	//                                                discarded the return value
	//  ------------------------------------------------------------------------

	int        LIBSPEC_NATIVECONSSOLEAPPAIDS_API WaitForCarbonUnitA
	(
		const LPCRTWaitForCarbonUnit plpCRTWaitForCarbonUnit
	);
	int        LIBSPEC_NATIVECONSSOLEAPPAIDS_API WaitForCarbonUnitW
	(
		const LPCRTWaitForCarbonUnit plpCRTWaitForCarbonUnit
	);
#if defined ( __cplusplus )
}   /* ... extern "C" */
#endif  /* #if defined ( __cplusplus ) */

//	----------------------------------------------------------------------------
//	Map the ANSI and Unicode (wide character) routines to common names by which 
//	they may be called in the context of either encoding.
//	----------------------------------------------------------------------------

#if defined ( UNICODE )
	#define ReportSystemError		ReportSystemErrorW
	#define ShowPlatform			ShowPlatformW
	#define ShowProgramInfo			ShowProgramInfoW
	#define WaitForCarbonUnit		WaitForCarbonUnitW
#else
	#define ReportSystemError		ReportSystemErrorA
	#define ShowPlatform			ShowPlatformA
	#define ShowProgramInfo			ShowProgramInfoA
	#define WaitForCarbonUnit		WaitForCarbonUnitA
#endif	/* #if defined ( UNICODE ) */
#endif	/* _NATIVECONSSOLEAPPAIDS_DEFINED */