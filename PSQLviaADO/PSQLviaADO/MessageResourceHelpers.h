#pragma once

#include <Windows.h>
#include <Const_Typedefs_WW.H>

LPTSTR __stdcall GetUserLocale ( );
void   __stdcall DisplayMessage             ( HMODULE  phPEHandle , RES_STRING_ID puintResID   );
LPTSTR __stdcall LoadMessage                ( HMODULE  phPEHandle , RES_STRING_ID puintResID   );
int    __stdcall ReportSystemErrorOnConsole ( CHMODULE phPEHandle , CDWORD        pdwLastError );