/*
    ============================================================================

    File Name:          StandardMacros_DAG.H

    File Synopsis:      This C/C++ header file defines some macros to simplify
                        some fairly simple, but frequently required, slightly
                        obscure operations.

    Remarks:            Since it is composed entirely of macros, there is no DLL
                        or link library associated with this header.

                        This new header was created around ForceIntoDEebugger,
                        but I expect to add other macros as the need arises.

    References:         DebugBreak function
                        https://msdn.microsoft.com/en-us/library/windows/desktop/ms679297(v=vs.85).aspx

    Date Created:       Tuesday, 22 September 2015

    License:            Copyright (C) 2015-2017, David A. Gray. All rights reserved.

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

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2015/09/22 DAG Header created and first used in StandardHandlesLab.exe.

    2015/09/30 DAG Document the ForceIntoDEebugger macro, which was added, but
                   undocumented, in the initial release. Since I have it open, I
                   may as well correct a technical error of fact in the remarks.

    2015/10/11 DAG Define MEMSET_ZERO_WW, for use with CRT function memset.

    2016/03/07 DAG 1) Complete the set of NULL constants designated for use when
                      an argument is either required to be set to NULL or is set
                      to NULL in lieu of support for optional arguments in the
                      Pascal (__stdcall) calling convention.

                   2) Move ZeroFillRestOfStruct from NetUseEngine__TestHarness.H
                      following preliminary tests in the like named program.

    2016/05/07 DAG Reverse the sense of the test that constrains definition of
                   _UNICODE to cases in which UNICODE is defined.

    2016/12/26 DAG Correct typographical errors discovered during a code review.

    2017/04/10 DAG Define the RCDATA_ constants, along with my basic integers.

    2017/04/12 DAG Add stdlib.h, the baseline CRT library.

    2017/05/11 DAG Add definitions of STATUS_CODE_FORMAT_WW and a const typedef.

    2017/05/24 DAG 1) Define SYSTEMTIME_INITIALIZER_WW, a set of four macros
                      that must be used together to initialize a SYSTEMTIME data
                      structure, at least when it occurs in the middle of a
                      structure that is otherwise comprised of machine-word
                      sized values.

                   2) Define Boolean symbolic constants MTX_CREATE_AND_ACQUIRE
                      and MTX_CREATE_WITHOUT_ACQUIRING for creating mutex
                      objects.

                   3) Define MTX_MUTEX_IS_AVAILABLE, which is patterned after
                      FB_MUTEX_AVAILABLE, and is intended for initializing a
                      DWORD location that will store the ID of the thread that
                      owns the mutex.

    2017/05/28 DAG 1) Define a pair of symbolic constants, along the lines of
                      SYSTEMTIME_INITIALIZER_WW_1 - SYSTEMTIME_INITIALIZER_WW_8,
                      for statically initializing a FILETIME structure that is
                      embedded in a larger structure that I am statically
                      initializing with some nonzero values.

                   2) Correct the comment above the SYSTEMTIME initializers.

    2017/06/15 DAG Complete the set by defining RCDATA_INVALID_RES_ID.
    ============================================================================
*/

#include <stdlib.h>
#include <malloc.h>                         // Required by macro ZeroFillBuffer, declares the malloc family of heap management routines

//  ----------------------------------------------------------------------------
//  Define character types and related macros.
//  ------------------------------------------
//
//  Among the objectives of these macros is to decrease the risk of off-by-one
//  errors.
//
//  If UNICODE is defined for the Win32 libraries, define its twin, _UNICODE,
//  for the CRT libraries, then include stdio.h, which defines the printf family
//  of routines, among others. TcharMacros_WW.H requires several of the printf
//  routines. Since it invokes them through the generic text mappings, I put it
//  in charge of importing TCHAR.H.
//  ----------------------------------------------------------------------------

#if defined ( _INC_STDIO )
    #pragma message ( __FILE__": stdio.h has already made it into the translation stream." )
#else
    #include <stdio.h>

    #if defined ( UNICODE )
        #pragma message ( __FILE__ ": This translation unit requires stdio.h. It is being included here, with _UNICODE defined." )
    #else
        #pragma message ( __FILE__ ": This translation unit requires stdio.h. It is being included here, without _UNICODE defined." )
    #endif  /* #if defined ( UNICODE ) */
#endif  /* #if defined ( _INC_STDIO ) */

//  ----------------------------------------------------------------------------
//  Define typedefs for const argument decorations that I use, but cannot find
//  defined in the Platform SDK headers, and a set of simple offset macros that
//  I use to decrease the risk of off-by-one errors.
//  ----------------------------------------------------------------------------

#include <MathMacros_WW.H>                  // Define symbolic constants for frequently used literals that are ambiguous, and macros, mostly for use with arrays.
#include <TcharMacros_WW.H>                 // Define macros for manipulating individual characters and strings, and for allocating correctly sized buffers into which to safely copy strings of known length.
#include <Const_Typedefs_WW.H>              // Typedefs for independent use in function prototyping.

#if !defined ( _MISCMACROS_DAG_DEFINED )
    #define _MISCMACROS_DAG_DEFINED

    #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
        #pragma once
    #endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

    #if defined ( UNICODE )
        #if !defined ( _UNICODE )
            #define _UNICODE
        #endif  /* #if !defined ( _UNICODE */
    #endif  /* #if defined ( UNICODE ) */

    #if !defined ( MINUS_ONE_WW )
        #define MINUS_ONE_WW                    ( -1 )
    #endif  /* #if !defined ( MINUS_ONE_WW ) */

    #if !defined ( PLUS_ONE_WW )
        #define PLUS_ONE_WW                     ( +1 )
    #endif  /* #if !defined ( PLUS_ONE_WW ) */

    #if !defined ( ZERO_WW )
        #define ZERO_WW                         ( 0 )
    #endif  /* #if !defined ( ZERO_WW ) */

    #if !defined ( RCDATA_INVALID_RES_ID )
        #define RCDATA_INVALID_RES_ID           ZERO_WW
    #endif  /* #if !defined ( RCDATA_INVALID_RES_ID ) */

    #if !defined ( RCDATA_INPLACE_POINTER )
        #define RCDATA_INPLACE_POINTER          ZERO_WW
    #endif  /* #if !defined ( RCDATA_INPLACE_POINTER ) */

    #if !defined ( RCDATA_LOOK_IN_STARTUP_PE_FILE )
        #define RCDATA_LOOK_IN_STARTUP_PE_FILE  LOOK_IN_THIS_EXE
    #endif  /* #if !defined ( RCDATA_LOOK_IN_STARTUP_PE_FILE ) */

    #if !defined ( RCDATA_HIDE_LENGTH )
        #define RCDATA_HIDE_LENGTH              ZERO_WW
    #endif /* #if !defined ( RCDATA_HIDE_LENGTH ) */

    #if !defined ( TRAILING_NULL_ALLOWANCE_P6C )
        #define TRAILING_NULL_ALLOWANCE_P6C     PLUS_ONE_WW
    #endif  /* #if !defined ( TRAILING_NULL_ALLOWANCE_P6C) */

    #ifndef RCDATA_MAX_LENGTH_P6C
        #define RCDATA_MAX_LENGTH_P6C           4097
        #define RCDATA_MAX_BUFFER_P6C           ( RCDATA_MAX_LENGTH_P6C + TRAILING_NULL_ALLOWANCE_P6C )
        #define RCDATA_MAX_BUFFER_BYTES_P6C     ( RCDATA_MAX_BUFFER_P6C * sizeof ( TCHAR ) )
    #endif  /* #ifndef RCDATA_MAX_LENGTH_P6C */

    //  ------------------------------------------------------------------------
    //  Use these tokens to initialize a SYSTEMTIME structure in one fell swoop.
    //  ------------------------------------------------------------------------

    #define SYSTEMTIME_INITIALIZER_WW_1         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_2         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_3         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_4         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_5         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_6         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_7         0x0000
    #define SYSTEMTIME_INITIALIZER_WW_8         0x0000

    //  ------------------------------------------------------------------------
    //  Use these tokens to initialize a FILETIME structure in one fell swoop.
    //  ------------------------------------------------------------------------

    #define FILETIME_INITIALIZER_WW_1           0x00000000
    #define FILETIME_INITIALIZER_WW_2           0x00000000

    #define LONGLONG_INTEGER_INITIALIZER_WW     0x0000000000000000  // Initialize a LongLong value in one go.

    #define TICKS_PER_SECOND_WW                 0x00989680          // Ticks per Second = 10,000,000, where 1 tick = 100 nanoseconds

    #define MTX_MUTEX_IS_AVAILABLE              0x00000000

    #define MTX_CREATE_AND_ACQUIRE              TRUE
    #define MTX_CREATE_WITHOUT_ACQUIRING        FALSE

    //  ------------------------------------------------------------------------
    //  All of my FormatMessage wrappers use this enumeration to direct the
    //  formatting of the status code.
    //  ------------------------------------------------------------------------

    #if ( ( !defined ( _FORMATMSGS_WW ) ) && ( !defined ( _FORMAT_FORMATMSGS_WW_TO_COME ) ) )
        typedef enum _STATUS_CODE_FORMAT_WW
        {
            STATUS_CODE_HEXADECIMAL ,   // 0
            STATUS_CODE_DECIMAL ,       // 1
            STATUS_CODE_OCTAL           // 2
        } STATUS_CODE_FORMAT_WW ;

        typedef const STATUS_CODE_FORMAT_WW  CSTATUS_CODE_FORMAT_WW;
    #endif  /* !defined ( _FORMATMSGS_WW ) ) && ( !defined ( _FORMAT_FORMATMSGS_WW_TO_COME ) ) ) */

    #define ERR_STRING_LOAD_ERROR_2     ( APPLICATION_ERROR_MASK | 0x0000C000 )

    /*
        ------------------------------------------------------------------------
        Name:           ForceIntoDEebugger

        Abstract:       Call the DebugBreak Windows API function, to force the
                        calling program into the Just-in-time debugger at a set
                        point.

        In:             Nothing

        Out:            Nothing

        Remarks:        A pragma directive generates a message in the compiler
                        output that reports how ForceIntoDEebugger expanded.

                        This macro expands in one of two ways, depending on the
                        settings of three preprocessor symbols, as detailed in
                        the following table.

                        ------------------------------------------------------------------
                        _DEBUG     _FORCE_DEBUGGER  _FORCE_RETAIL_DEBUGGER  Expansion
                        ---------  ---------------  ----------------------  --------------
                        Defined    Defined          Ignored                 DebugBreak ( )
                        Defined    Undefined        Ignored                 nothing
                        Undefined  Ignored          Defined                 DebugBreak ( )
                        Undefined  Ignored          Undefined               nothing
                        ------------------------------------------------------------------

                        I am considering a third option that would condition its
                        behavior on a configuration setting, but I need to give
                        more thought to how to implement it.
        ------------------------------------------------------------------------
    */

    #if defined ( _DEBUG )
        #if defined ( _FORCE_DEBUGGER )
            #pragma message ( __FILE__ ": Preprocessor symbols _DEBUG and _FORCE_DEBUGGER are defined. ForceIntoDEebugger expands into DebugBreak call.")
            #define ForceIntoDEebugger DebugBreak ( )
        #else
            #pragma message ( __FILE__ ": Preprocessor symbols _DEBUG and _FORCE_DEBUGGER are UNdefined. ForceIntoDEebugger does nothing.")
            #define ForceIntoDEebugger
        #endif  /* #if defined ( _FORCE_DEBUGGER ) */
    #else
        #if defined ( _FORCE_RETAIL_DEBUGGER )
            #pragma message ( __FILE__ ": Preprocessor symbol _FORCE_DEBUGGER is defined in a retail build. ForceIntoDEebugger expands into DebugBreak call.")
            #define ForceIntoDEebugger DebugBreak ( )
        #else
            #pragma message ( __FILE__ ": Preprocessor symbol _FORCE_DEBUGGER is UNdefined in a retail build does nothing.")
            #define ForceIntoDEebugger
        #endif  /* #if defined ( _FORCE_RETAIL_DEBUGGER ) */
    #endif  /* #if defined ( _DEBUG ) */

    #if !defined ( HEAP_ALL_FLAGS_OFF )
        #define HEAP_ALL_FLAGS_OFF              0x00000000L
    #endif  /* HEAP_ALL_FLAGS_OFF */

    #if !defined ( HEAP_ALL_FLAGS_OFF_WW )
        #define HEAP_ALL_FLAGS_OFF_WW           HEAP_ALL_FLAGS_OFF
    #endif /*HEAP_ALL_FLAGS_OFF_WW*/

    #if !defined ( HEAP_ALL_FLAGS_OFF_P6C )
        #define HEAP_ALL_FLAGS_OFF_P6C          HEAP_ALL_FLAGS_OFF
    #endif  /* HEAP_ALL_FLAGS_OFF_P6C */

    //  --------------------------------------------------------------------
    //  ASCII Code  124  = | = 0x7C - This is the only way to make it work
    //  as a #DEFINEd symbol.
    //  --------------------------------------------------------------------

    #if !defined ( PIPE_CHAR_P6C )
        #define PIPE_CHAR_P6C                   ( ( TCHAR ) '|' )
        #endif  /* PIPE_CHAR_P6C */

    #if !defined ( PIPE_CHAR_WW )
        #define PIPE_CHAR_WW                    PIPE_CHAR_P6C
    #endif  /* PIPE_CHAR_WW */

    #if defined ( MAX_PATH )
        #if !defined ( MAX_PATH_BUFFER_TCHARS_WW )
            #define MAX_PATH_BUFFER_TCHARS_WW   MAX_PATH
        #endif  /* MAX_PATH_BUFFER_TCHARS_WW */

        #if !defined ( MAX_PATH_BUFFER_BYTES_WW )
            #define MAX_PATH_BUFFER_BYTES_WW    ( MAX_PATH_BUFFER_TCHARS_WW * sizeof ( TCHAR ) )
        #endif  /* MAX_PATH_BUFFER_BYTES_WW */
    #endif /* #ifdef MAX_PATH */

    #if !defined ( EMPTY_STRING_P6C)
        #define EMPTY_STRING_P6C                ( _TEXT ( "" ) )
    #endif  /* EMPTY_STRING_P6C */

    #if !defined ( EMPTY_STRINGA_P6C )
        #define EMPTY_STRINGA_P6C               ""
    #endif  /* EMPTY_STRINGA_P6C */

    #if !defined ( EMPTY_STRINGW_P6C )
        #define EMPTY_STRINGW_P6C               L""
    #endif  /* EMPTY_STRINGW_P6C */

    //  --------------------------------------------------------------------
    //  Use these constants whenever a function takes a dummy DWORD or LP
    //  argument, whose value must be zero, OR to specify an intentionally
    //  unused (omitted) argument that is treated as optional, but must be
    //  supplied, since the pascal calling convention requires argument
    //  lists of a fixed length.
    //  --------------------------------------------------------------------

    #if !defined ( DW_RESERVED )
        #define DW_RESERVED                     0x00000000L
    #endif  /* DW_RESERVED */

    #if !defined ( DW_RESERVED_WW )
        #define DW_RESERVED_WW                  DW_RESERVED
    #endif  /* DW_RESERVED_WW */

    #if !defined ( DW_UNUSED )
        #define DW_UNUSED                       0x00000000L
    #endif /* DW_UNUSED */

    #if !defined ( DW_UNUSED_WW )
        #define DW_UNUSED_WW                    DW_UNUSED
    #endif /* DW_UNUSED_WW */

    #if !defined ( HANDLE_RESERVED )
        #define HANDLE_RESERVED                 0x00000000L
    #endif /* HANDLE_RESERVED */

    #if !defined ( HANDLE_RESERVED_WW )
        #define HANDLE_RESERVED_WW              HANDLE_RESERVED
    #endif /* HANDLE_RESERVED_WW */

    #if !defined ( HANDLE_UNUSED )
        #define HANDLE_UNUSED                   0x00000000L
    #endif  /* HANDLE_UNUSED */

    #if !defined ( HANDLE_UNUSED_WW )
        #define HANDLE_UNUSED_WW                HANDLE_UNUSED
    #endif  /* HANDLE_UNUSED_WW */

    #if !defined ( LP_RESERVED )
        #define LP_RESERVED                     0x00000000L
    #endif  /* LP_RESERVED */

    #if !defined ( LP_RESERVED_WW )
        #define LP_RESERVED_WW                  LP_RESERVED
    #endif  /* LP_RESERVED_WW */

    #if !defined ( LP_UNUSED )
        #define LP_UNUSED                       0x00000000L
    #endif  /* LP_UNUSED */

    #if !defined ( LP_UNUSED_WW )
        #define LP_UNUSED_WW                    LP_UNUSED
    #endif  /* LP_UNUSED_WW */

    #if !defined ( PLUS_ONE_P6C )
        #define PLUS_ONE_P6C                    1
    #endif  /* PLUS_ONE_P6C */

    #if !defined ( PLUS_TWO_P6C )
        #define PLUS_TWO_P6C                    2
    #endif /*PLUS_TWO_P6C*/

    #if !defined ( ZERO_P6C )
        #define ZERO_P6C                        0
    #endif  /* ZERO_P6C */

    #if !defined ( MEMSET_ZERO_WW )
        #define MEMSET_ZERO_WW                  ZERO_P6C
    #endif  /* MEMSET_ZERO_WW */

//  ----------------------------------------------------------------------------
//  Define constants for parsing command lines.
//  ----------------------------------------------------------------------------

    #if !defined ( _CMDLINE_CONSTANTS )
        #define _CMDLINE_CONSTANTS

        #define CMDLINE_HAS_TAIL_P6C            PLUS_TWO_P6C
        #define CMDLINE_FIRST_ARG_P6C           PLUS_ONE_P6C
        #define SWITCH_FLAG_POS_P6C             ZERO_P6C
        #define SWITCH_LETTER_POS_P6C           PLUS_ONE_P6C
        #define SWITCH_MODIFIER_POS_P6C         PLUS_TWO_P6C
        #define MIN_LEN_BARE_SWITH_P6C          PLUS_ONE_P6C
        #define MIN_LEN_MODIFIED_SWITH_P6C      PLUS_TWO_P6C
        #define SWITCH_FLAG_HYPHEN_P6C          ( ( TCHAR ) '-' )
        #define SWITCH_FLAG_FWD_SLASH_P6C       ( ( TCHAR ) '/' )
    #endif  /* _CMDLINE_CONSTANTS */

    #if !defined ( _SPECIAL_CHARACTERS )
        #define _SPECIAL_CHARACTERS

        //  ----------------------------------------------------------------
        //  Newline, Bell (Alarm) and Tab characters are often the sole
        //  content of a print format string. Likewise, null characters
        //  often appear as r-values in assignment statements.
        //
        //  IMPORTANT:  C and C++ source code must use LINEFEED_P6C (\n)
        //              because most compilers "do the right thing" by
        //              implementing \n in a platform dependent manner. For
        //              example, the Microsoft Visual C++ compiler, whether
        //              compiling C++ code, or downgraded to compile C code,
        //              substitutes LINE_ENDING_CHARS_WW for LINEFEED_P6C
        //              when the latter appears in a string literal.
        //  ----------------------------------------------------------------

        #define BELL_CHAR_WW                    ( ( TCHAR ) '\a' )
        #define BELL_STRING_WW                  ( _TEXT ( "\a" ) )

        #define CARRIAGE_RETURN_P6C             ( ( TCHAR ) '\r' )
        #define LINEFEED_P6C                    ( ( TCHAR ) '\n' )
        #define NEWLINE_CHAR_WW                 LINEFEED_P6C
        #define NEWLINE_STRING_WW               ( _TEXT ( "\n" ) )

        #define NULL_CHARACTER_P6C              ( ( TCHAR ) '\0' )

        #define TAB_CHAR_WW                     ( ( TCHAR ) '\t' )
        #define TAB_STRING_WW                   ( _TEXT ( "\t" ) )

        #define LINE_ENDING_CHARS_WW            ( _TEXT ( "\r\n" ) )
    #endif  /* _SPECIAL_CHARACTERS */

    #if !defined ( PRINTF_LAST_ERROR_WW )
        #define PRINTF_LAST_ERROR_WW            ( _TEXT ( "0x%08x" ) )
    #endif  /* PRINTF_LAST_ERROR_WW */

    //  --------------------------------------------------------------------
    //  Define constants for assorted obscure values.
    //  --------------------------------------------------------------------

    #if !defined ( ONE_SECOND_SLEEP_WW )
        #define ONE_SECOND_SLEEP_WW             1000
    #endif /* ONE_SECOND_SLEEP_WW */

    #if !defined ( FIVE_SECONDS_WW )
        #define FIVE_SECONDS_WW                 ( 5 * ONE_SECOND_SLEEP_WW )
    #endif  /* #if !defined ( FIVE_SECONDS_WW ) */

    #if !defined ( ZeroFillBuffer )
        #if defined ( _INC_MALLOC )
            /*
                ----------------------------------------------------------------

                Name:   ZeroFillBuffer = Fill a buffer with zeros (NULLs).

                In:     pMem           = Pointer to the buffer to be cleared.

                Out:    Nothing, since the underlying memset functions returns
                        void.

                Notes:  This macro eliminates a function call immediately
                        followed by another function call, to zero the contents
                        of a buffer that was returned by malloc or realloc.
                        Since it uses _msize to get the size of the buffer, it
                        clears a buffer of any size with one line of code.

                        Function memset exits gracefully if _msize ( pMem )
                        returns zero.

                        Analysis of working code has established that the
                        ZeroMemory() and FillMemory() functions, in the Windows
                        API, are implemented as wrappers around memset, a CRT
                        function. Although memset works just fine, whether or
                        not the calling process ran the CRT startup code, based
                        on observations of other functions, such as fopen, which
                        wraps a bunch of CRT overhead around a call to the
                        CreateFile Windows API function, I didn't expect
                        ZeroMemory and FillMemory to be implemented as
                        wrappers around CRT functions. The difference is that
                        the latter two are independent of the CRT startup code.

                        This macro is undefined unless preprocessor symbol
                        _INC_MALLOC is defined, indicating that malloc is
                        declared.
                ----------------------------------------------------------------
            */

            #define ZeroFillBuffer(pMem) ( memset ( pMem ,              \
                                                    ZERO_P6C ,          \
                                                    _msize ( pMem ) ) )
        #endif  /* _INC_MALLOC */
    #endif  /* ZeroFillBuffer */

    #if defined ( _INC_MEMORY ) || defined ( _INC_STRING ) || defined ( _INC_WCHAR )
        #if !defined ( ZeroFillRestOfStruct )
            /*
                ----------------------------------------------------------------

                Name:   ZeroFillRestOfStruct = Fill all but the first member of
                        a structure with zeros (NULLs).

                In:     plpStartHere                = pointer to second member
                                                      of the structure to be
                                                      initialized

                        pStructType                 = typename of structure, for
                                                      computing its size, in
                                                      bytes.

                        pInitializedSubstructType   = typename of first member,
                                                      for computing its size, in
                                                      bytes.

                Out:    Nothing, since the underlying memset functions returns
                        void.

                Notes:  1)  Arguments pStructType and pInitializedSubstructType
                            are fed to the sizeof pseudo-function, which returns
                            the size, in bytes, of each. The difference between
                            them is the number of bytes to initialize, the third
                            of three memset arguments.

                        2)  Argument plpStartHere points to the second member of
                            the structure, which you specify as you would to set
                            its value. Ideally, you would point to the start of
                            the entire structure, but I haven't yet worked out
                            the math to compute it from the first and second
                            arguments.
                ----------------------------------------------------------------
            */

            #define ZeroFillRestOfStruct(plpStartHere, pStructType, pInitializedSubstructType)  \
            (                                                                                   \
                memset ( &plpStartHere ,                                                        \
                         MEMSET_ZERO_WW ,                                                       \
                         sizeof ( pStructType ) - sizeof ( pInitializedSubstructType ) ) )
        #endif  /* #if !defined ( ZeroFillRestOfStruct ) */
    #endif  /* #if defined ( _INC_MEMORY ) || defined ( _INC_STRING ) || defined ( _INC_WCHAR ) */

    //  ------------------------------------------------------------------------
    //  Macro DllLoadAsData_WW is undefined unless _INC_WINDOWS is defined,
    //  implying that LoadLibraryEx is declared.
    //  ------------------------------------------------------------------------

    #if !defined ( DllLoadAsData_WW )
        #if defined ( _INC_WINDOWS )
            #define DllLoadAsData_WW(plpDllName)  ( LoadLibraryEx ( plpDllName ,                    \
                                                                    DW_RESERVED ,                   \
                                                                    LOAD_LIBRARY_AS_DATAFILE ) )
        #endif  /* _INC_WINDOWS */
    #endif  /* DllLoadAsData_WW */
#endif  /* ##if !defined (  _MISCMACROS_DAG_DEFINED */