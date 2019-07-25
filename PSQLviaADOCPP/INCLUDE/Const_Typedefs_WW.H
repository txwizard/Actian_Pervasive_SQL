//{{NO_DEPENDENCIES}}
/*
    ============================================================================

    Name:               Const_Typedefs_WW.H

    Library:            Any and all, not to mention user code

    Synopsis:           This header file defines established typedefs for use in
                        function prototypes.

    Dependencies:       To leverage the standard Win32 typedefs, include the
                        main Win32 header (windows.h) before this header.

    Remarks:            Additions to this header never require existing code to
                        be compiled, hence, the NO_DEPENDENCIES directive at the
                        top, as in machine generated Win32 resource scripts.

                        This header is designed to work transparently with or
                        without the main Win32 header, windows.h, although it is
                        pretty lame (not to mention pointless) without it.

                        The included typedefs were extracted from an existing
                        header, CommonConstants_P6C.H. This extraction is part
                        of a long term project to break it up into smaller, more
                        manageable pieces.

                        The simplified scheme is the outcome of investigating an
                        error related to my original test for the existence of a
                        BOOL typedef, and was inspired by a thread on the
                        StackOverflow bulletin board.

    Reference:          "How to check if a datatype is “defined” with typedef"
                        http://stackoverflow.com/questions/3517174/how-to-check-if-a-datatype-is-defined-with-typedef

    Author:             David A. Gray

    License:            Copyright (C) 2009-2017, David A. Gray. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    *   Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    *   Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    *   Neither the name of Simple Soft Services, Inc. nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Created:            Friday, 24 May 2013

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2013/05/25 DAG Create this header from typedefs extracted from existing
                   header CommonConstants_P6C.H.

    2013/06/18 DAG Define CHWND for passing a read only window handle.

    2014/09/06 DAG Define the following:

                            ======================
                            Name        Mapping
                            ----------  ----------
                            CHANDLE     HANDLE
                            CHINSTANCE  HINSTANCE
                            CHMODULE    HMODULE
                            ======================

    2015/02/01 DAG Map const TCHAR to CTCHAR.

    2015/02/23 DAG 1) Map the following: const WORD    to CWORD
                                         const LPDWORD to CLPDWORD
                                         const PUSHORT to CLPWORD
                                         const PUSHORT to CPUSHORT

                   2) Exclude this header from dependency tests.

    2015/07/09 DAG Insert my 3-clause BSD license, in preparation for eventual
                   publication with a forthcoming article.

    2015/10/08 DAG Define CLPUINT, a const pointer to unsigned integer, to use as
                   a pointer through which data can be passed back to the caller
                   while prohibiting the callee from changing the address to
                   which it points.

                   If this experiment works out as well as I hope, I may add a
                   few others.

    2016/01/12 DAG Define signed and unsigned 8, 16, and 64 bit integers (except
                   signed 8 bits, for which I see no practical use).

    2016/01/22 DAG Define const LPBYTE as CLPBYTE, for passing encoding-agnostic
                   chunks of data into functions.

    2016/02/15 DAG Define LPBOOLC, a const pointer to BOOL, to use as a pointer
                   through which a flag can be passed back to the caller while
                   prohibiting the callee from changing the address to which it
                   points.

                   See CLPUINT, which I defined and implemented in FB_LoadString
                   and FB_LoadStringFromDLL, declared in FixedStringBuffers.H,
                   and defined in FB_LoadString.INL and FB_LoadStringFromDLL.INL
                   respectively.

    2016/02/19 DAG Define a full set of immutable pointers to value types that
	               may be changed, e. g., to invalidate a pointer. This group
				   is differentiated from the traditional const pointer, whose
				   value is immutable from the perspective of the callee.

	2016/02/22 DAG Define RES_STRING_ID unless CPP symbol _GETMYRESOURCE_WW is
	               defined.

	2017/05/11 DAG Correct typographical errors found during a visual scan.
    ============================================================================
*/

#if !defined ( _CONST_TYPEDEFS_WW_INCLUDED )
    #define _CONST_TYPEDEFS_WW_INCLUDED

    #if defined (_MSC_VER) && (_MSC_VER >= 1020)
        #pragma once
    #endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

    #if !defined ( _GETMYRESOURCE_WW )
        typedef const unsigned int          RES_STRING_ID ;
    #endif	/* #if defined ( _GETMYRESOURCE_WW ) */

    #if defined ( _WINDEF_ ) && defined ( _WIN32 )
		//	--------------------------------------------------------------------
		//	The following types are constant with respect to the contents stored
		//	at the addresses to which they point, which is denoted by starting
		//	each name with a C.
		//	--------------------------------------------------------------------

		//	immutable scalars, mostly signed integers of various sizes

		typedef const BOOL					CBOOL ;
        typedef const DWORD					CDWORD ;
        typedef const INT					CINT ;
        typedef const LONG					CLONG ;
		typedef const ULONG					CULONG ;
        typedef const UINT					CUINT ;
        typedef const SHORT					CSHORT ;

		//	Immutable pointers

		typedef const LPBYTE		        CLPBYTE ;
		typedef const LPDWORD				CLPDWORD ;
		typedef TCHAR *						LPTCHAR ;
		typedef const LPTCHAR				CLPTCHAR ;
		typedef const TCHAR					CTCHAR ;
		
		//	Immutable integers, all unsigned

		typedef const USHORT				CUSHORT ;
        typedef const unsigned char			CUCHAR ;
        typedef const __int64				CINT64 ;
        typedef const unsigned __int64		CUINT64 ;
        typedef unsigned int * const		CLPUINT ;

		//	Immutable voids and void pointers

		typedef const VOID					CVOID ;
        typedef const VOID *				CLPVOID ;
        typedef const WORD					CWORD ;
        typedef const PUSHORT				CLPWORD ;
        typedef const PUSHORT			    CPUSHORT ;

		//	--------------------------------------------------------------------
		//	Immutable Windows handles of various types
		//
		//	Their intention was to prevent a called routine from being permitted
		//	to close a handle that belongs to a routine that runs above it in
		//	the call stack. Experiments with the new const handles defined below
		//	cast doubt on that assumption; I now believe that these should be
		//	marked as deprecated, to be superseded at the earliest opportunity
		//	by the ones defined in the next section.
		//	--------------------------------------------------------------------

		typedef const HANDLE				CHANDLE ;
		typedef const HINSTANCE				CHINSTANCE ;
		typedef const HKEY					CHKEY ;
		typedef const HMODULE				CHMODULE ;
		typedef const HWND					CHWND ;

		//	--------------------------------------------------------------------
		//	The following types are constant with respect to the addresses to
		//	which they point.
		//	--------------------------------------------------------------------

		//	Assorted scalars

		typedef BYTE *    const				LPBYTEC ;
		typedef BOOL *    const				LPBOOLC ;
		typedef CHAR *    const				LPCHARC ;
		typedef DWORD *   const				LPDWORDC ;

		//	--------------------------------------------------------------------
		//	Windows handles of various types
		//
		//	Use these to protect a handle against being closed prematurely. The
		//	compiler prohibits assigning to them; hence, if you reset handles
		//	after you close them (You do that, right?) the compiler will bark at
		//	you about it, although it won't prevent you from closing the handle.
		//	--------------------------------------------------------------------

		typedef HANDLE    const				HANDLEC ;
		typedef HINSTANCE const				HINSTANCEC ;
		typedef HKEY      const				HKEYC ;
		typedef HMODULE	  const				HMODULEC ;
		typedef HWND      const				HWNDC ;

		//	Mostly signed integer types

		typedef __int64 * const				LPINT64C ;
		typedef INT *     const				LPINTC ;
		typedef LONG *    const				LPLONGC ;
		typedef LPTSTR    const				LPTSTRC ;
		typedef SHORT *   const				LPSHORTC ;
		typedef TCHAR *   const				LPTCHARC ;

		// Unsigned integer types

		typedef UCHAR *   const				LPUCHARC ;
		typedef UINT *    const				LPUINTC ;
		typedef ULONG *   const				LPULONGC ;
		typedef USHORT *  const			    LPUSHORTC ;
		typedef UINT64 *  const	            LPUINT64C ;

		typedef VOID *    const				LPVOIDC ;
#else
        #pragma message ( "Standard Windows types must be defined. To make that happen, include windows.h, or at least windef.h." )
    #endif  /* #if defined ( _WINDEF_ ) && defined ( _WIN32 ) */
#endif  /* #if !defined ( _CONST_TYPEDEFS_WW_INCLUDED ) */