#define WINDOWS_LEAN_AND_MEAN

#include ".\MessageResourceHelpers.h"

void   __stdcall DisplayMessage ( HMODULE  phPEHandle , RES_STRING_ID puintResID )
{
	LPTSTR	lpMsgBuffer = NULL;

	if ( FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER 
		                 | FORMAT_MESSAGE_FROM_HMODULE ,		// DWORD   dwFlags		- Flags is a bit mask. FORMAT_MESSAGE_ALLOCATE_BUFFER requests a buffer of the required size to be allocated via LocalAlloc.
		phPEHandle ,											// LPCVOID lpSource		- This parameter is honored because FORMAT_MESSAGE_FROM_HMODULE.
		puintResID,												// DWORD   dwMessageId
		MAKELANGID  ( LANG_NEUTRAL , SUBLANG_NEUTRAL ),			// DWORD   dwLanguageId	- Since this is documented as an integral type, it appears that I'm stuck with the deprecated MAKELANGID macro.
		lpMsgBuffer,											// LPTSTR  lpBuffer		- FormatMessage initializes this because FORMAT_MESSAGE_ALLOCATE_BUFFER.
		0 ,														// DWORD   nSize		- FormatMessage ignores this because FORMAT_MESSAGE_ALLOCATE_BUFFER gives it free reign to determine how much memory it needs.
		NULL ) )												// va_list *Arguments	- System messages never use these.
	{
	}
}	// void   __stdcall DisplayMessage


LPTSTR __stdcall GetUserLocale ( )
{
	int intLocalInfoSize = GetLocaleInfoEx ( LOCALE_NAME_USER_DEFAULT ,			// LPCWSTR lpLocaleName
		                                     LOCALE_SLOCALIZEDLANGUAGENAME ,	// LCTYPE  LCType
		                                     NULL ,								// LPWSTR  lpLCData
		                                     0 );								// int     cchData

	if ( intLocalInfoSize )
	{
		LPWSTR lpLocaleName = HeapAlloc ( GetProcessHeap ( ),
			                              HEAP_ZERO_MEMORY,
			                              intLocalInfoSize);

		if ( lpLocaleName )
		{
			intLocalInfoSize = GetLocaleInfoEx ( LOCALE_NAME_USER_DEFAULT,		// LPCWSTR lpLocaleName
				                                 LOCALE_SLOCALIZEDLANGUAGENAME,	// LCTYPE  LCType
				                                 lpLocaleName,					// LPWSTR  lpLCData
				                                 intLocalInfoSize);				// int     cchData

			if ( intLocalInfoSize )
			{	// GetLocaleInfoEx succeeded.
				return lpLocaleName;
			}	// TRUE (anticipated outcome) block, if ( intLocalInfoSize )
			else
			{	// GetLocaleInfoEx failed, and is expected to explain why through SetLastError.
				return NULL;
			}	// FALSE (unanticipated outcome) block, if ( intLocalInfoSize )
		}	// TRUE (anticipated outcome) block, if ( lpLocaleName )
		else
		{	// HeapAlloc failed without calling SetLastError.
			SetLastError ( ERROR_OUTOFMEMORY );
			return NULL;
		}	// FALSE (unanticipated outcome) block, if ( lpLocaleName )
	}	// TRUE (anticipated outcome) block, if ( intLocalInfoSize )
	else
	{	// GetLocaleInfoEx failed, and is expected to explain why through SetLastError.
		return NULL;
	}	// FALSE (unanticipated outcome) block, if ( intLocalInfoSize )
}	// LPTSTR __stdcall GetUserLocale


LPTSTR __stdcall LoadMessage ( HMODULE phPEHandle , RES_STRING_ID puintResID )
{
	LPTSTR lpLocaleName					= GetUserLocale ( );

	if (lpLocaleName)
	{
		HRSRC hMsgResource				= FindResourceEx ( phPEHandle,
												           RT_MESSAGETABLE ,
														   MAKEINTRESOURCE ( puintResID ) ,
														   lpLocaleName );

		if ( hMsgResource )
		{
			HGLOBAL hResource			= LoadResource ( phPEHandle ,			// HMODULE hModule  - passed into the function
				                                         hMsgResource );		// HRSRC   hResInfo - returned by FindResourceExA

			if ( hResource )
			{
				return ( LPTSTR ) LockResource ( hResource );					// The returned LPVOID value must be cast to LPTSTR.
			}	// TRUE (anticipated outcome) block, if ( hResource )
			else
			{	// LoadResource failed, and is expected to explain why through SetLastError.
				return NULL;
			}	// FALSE (unanticipated outcome) block, if ( hResource )
		}	// TRUE (anticipated outcome) block, if ( hMsgResource )
		else
		{	// FindResourceEx failed, and is expected to explain why through SetLastError.
			return NULL;
		}	// FALSE (unanticipated outcome) block, if ( hMsgResource )
	}	// TRUE (anticipated outcome) block, if ( intLocalInfoSize )
	else
	{
		return NULL;
	}	// FALSE (unanticipated outcome) block, if ( intLocalInfoSize )
}	// LPTSTR __stdcall LoadMessage


int   __stdcall ReportSystemErrorOnConsole ( CHMODULE phPEHandle , CDWORD pdwLastError )
{
	LPTSTR lpMsgBuffer					= NULL;
	DWORD  dwSystemStatusCode			= pdwLastError ? pdwLastError : GetLastError ( );

	if ( FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER
							| FORMAT_MESSAGE_FROM_SYSTEM ,						// DWORD   dwFlags		- Flags is a bit mask. FORMAT_MESSAGE_ALLOCATE_BUFFER requests a buffer of the required size to be allocated via LocalAlloc.
		                 NULL ,													// LPCVOID lpSource		- This parameter is ignored for system messages.
		                 dwSystemStatusCode ,									// DWORD   dwMessageId	- For system messages, the system status code is the message ID.
		                 MAKELANGID ( LANG_NEUTRAL , SUBLANG_NEUTRAL ) ,		// DWORD   dwLanguageId	- Since this is documented as an integral type, it appears that I'm stuck with the deprecated MAKELANGID macro.
						 lpMsgBuffer ,											// LPTSTR  lpBuffer		- FormatMessage initializes this because FORMAT_MESSAGE_ALLOCATE_BUFFER.
		                 0 ,													// DWORD   nSize		- FormatMessage ignores this because FORMAT_MESSAGE_ALLOCATE_BUFFER gives it free reign to determine how much memory it needs.
		                 NULL ) )												// va_list *Arguments	- System messages never use these.
	{
		printf ( "A Windows system error was encountered.\n\n    Status code = 0x%08x (%i decimal)\n    Message     = %s\n\n",
			     dwSystemStatusCode ,											// Status code = 0x%08x (
			     dwSystemStatusCode ,											// (%i decimal)
			     lpMsgBuffer );													// Message     = %s
		return dwSystemStatusCode;
	}	// TRUE (anticipated outcome) block, if ( FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM , NULL , dwSystemStatusCode , MAKELANGID ( LANG_NEUTRAL, SUBLANG_NEUTRAL ) , lpMsgBuffer , 0 , NULL ) )
	else
	{	// In the unlikely event of a FormatMessage failure, return the status code without further action, rather than risk an infinite loop.
		return GetLastError ( );
	}	// FALSE (unanticipated outcome) block, if ( FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM , NULL , dwSystemStatusCode , MAKELANGID ( LANG_NEUTRAL, SUBLANG_NEUTRAL ) , lpMsgBuffer , 0 , NULL ) )
}	// void   __stdcall ReportSystemErrorOnConsole