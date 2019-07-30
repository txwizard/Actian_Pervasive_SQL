#pragma once
#include ".\PSQLviaADO.h"

class ADOHelpers
{
public:
	static _variant_t ParseAndConvert (IN _bstr_t pstrInputValue, IN FieldPtr pDBField);
};

