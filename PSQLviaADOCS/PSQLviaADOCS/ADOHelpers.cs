/*
    ============================================================================

    Module Name:        ADOHelpers.cs

    Assembly:           PSQLviaADOCS

    Root Namespace:     PSQLviaADOCS

    Class:              ADOHelpers

    Objective:          This class models a column name and its label,
                        optionally associating both with a database table.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version By Description
    ---------- ------- ---------------------------------------------------------
    2019/07/23 1.3.0.0 DG Initial implementation.
    ============================================================================
*/

using System;
using System.Text;

using ADODB;                                                // Use ADODB via COM interop.

using WizardWrx;

namespace PSQLviaADOCS
{
    /// <summary>
    /// This class exposes static methods for parsing string representations of
    /// data that is destined for a column (field) in an ADODB Recordset.
    /// </summary>
    public static class ADOHelpers
    {
        /// <summary>
        /// Use this with StringIsInList argument pfCaseSensitive to specify
        /// case sensitive string matching.
        /// </summary>
        /// <see cref="StringIsInList"/>
        /// <seealso cref="CASE_INSENSITIVE"/>
        public const bool CASE_SENSITIVE = true;


        /// <summary>
        /// Use this with StringIsInList argument pfCaseSensitive to specify
        /// case insensitive string matching.
        /// </summary>
        /// <see cref="StringIsInList"/>
        /// <seealso cref="CASE_SENSITIVE"/>
        public const bool CASE_INSENSITIVE = false;


        /// <summary>
        /// Given an input field value and the destination Field object, parse
        /// its value, returning the value in a form that is acceptable for a
        /// column value of its ADODB Type.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Use the ADODB Type of the <paramref name="pDBField"/> to determine
        /// which routine to call for further processing, returning through the
        /// called routine.
        /// </param>
        /// <param name="pDBField">
        /// Use the Type property on this ADODB Field object to determine which
        /// routine to call for further processing, returning through the
        /// called routine.
        /// </param>
        /// <returns>
        /// The value returned through the selected processing routine, though
        /// cast to Object, is expected to be transparently acceptable to the
        /// column to which <paramref name="pDBField"/> refers.
        /// </returns>
        public static object ParseAndConvert (
            string pstrInputValue ,
            Field pDBField ,
            string [ ] pastrTrueStrings = null ,
            string [ ] pastrFalseStrings = null ,
            bool pfThrowWhenInvalid = false ,
            bool pfTreatadNumericAsNumStr = true )
        {
            switch ( pDBField.Type )
            {   // Though several cases could be combined, I kept them segregated to make them eaiser to find visually, and to facilitate replacing the switch with a table-driven transfer of control to a delegate.
                case DataTypeEnum.adBigInt:
                    return ParseAndConvertBigInteger (
                        pstrInputValue );
                case DataTypeEnum.adBoolean:
                    return ParseAndConvertBoolean (
                        pstrInputValue ,
                        pastrTrueStrings ,
                        pastrFalseStrings );
                case DataTypeEnum.adBSTR:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adChar:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adCurrency:
                    return ParseAndConvertCurrency (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adDate:
                    return ParseAndConvertDate (
                        pstrInputValue );
                case DataTypeEnum.adDBDate:
                    return ParseAndConvertDBDate (
                        pstrInputValue ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adDBTime:
                    return ParseAndConvertDBTime (
                        pstrInputValue );
                case DataTypeEnum.adDBTimeStamp:
                    return ParseAndConvertDBTimeStamp (
                        pstrInputValue );
                case DataTypeEnum.adDecimal:
                    return ParseAndConvertDecimal (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adDouble:
                    return ParseAndConvertDouble (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adFileTime:
                    return ParseAndConvertDBTimeStamp (
                        pstrInputValue );
                case DataTypeEnum.adGUID:
                    return ParseAndConvertGuidString (
                        pstrInputValue );
                case DataTypeEnum.adInteger:
                    return ParseAndConvertInteger (
                        pstrInputValue );
                case DataTypeEnum.adLongVarBinary:
                    return ParseAndConvertVarBinary (
                        pstrInputValue ,
                        pDBField.DefinedSize );
                case DataTypeEnum.adLongVarChar:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adLongVarWChar:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adNumeric:
                    return ParseAndConvertNumeric (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision ,
                        pfTreatadNumericAsNumStr );
                case DataTypeEnum.adPropVariant:
                    return ParseAndConvertPropVariant (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adSingle:
                    return ParseAndConvertSingle (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adSmallInt:
                    return ParseAndConvertSmallInteger (
                        pstrInputValue );
                case DataTypeEnum.adTinyInt:
                    return ParseAndConvertTinyInteger (
                        pstrInputValue );
                case DataTypeEnum.adUnsignedBigInt:
                    return ParseAndConvertUnsignedBigInteger (
                        pstrInputValue );
                case DataTypeEnum.adUnsignedInt:
                    return ParseAndConvertUnsignedInteger (
                        pstrInputValue );
                case DataTypeEnum.adUnsignedSmallInt:
                    return ParseAndConvertUnsignedSmallInteger (
                        pstrInputValue );
                case DataTypeEnum.adUnsignedTinyInt:
                    return ParseAndConvertUnsignedTinyInteger (
                        pstrInputValue );
                case DataTypeEnum.adVarBinary:
                    return ParseAndConvertVarBinary (
                        pstrInputValue ,
                        pDBField.DefinedSize );
                case DataTypeEnum.adVarChar:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adVariant:
                    return ParseAndConvertVariant (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adVarNumeric:
                    return ParseAndConvertVarNumeric (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pDBField.NumericScale ,
                        pDBField.Precision );
                case DataTypeEnum.adVarWChar:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                case DataTypeEnum.adWChar:
                    return ParseAndConvertString (
                        pstrInputValue ,
                        pDBField.DefinedSize ,
                        pfThrowWhenInvalid );
                default:
                    throw new System.ComponentModel.InvalidEnumArgumentException (
                        nameof ( pDBField.Type ) ,
                        ( int ) pDBField.Type ,
                        pDBField.Type.GetType ( ) );
            }   // switch ( pDBField )
        }   // public static object ParseAndConvert


        /// <summary>
        /// Parse and convert a Big Integer input value, returning a value that is
        /// compatible with a Field of type adBigInt.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adBigInt columns.
        /// </returns>
        public static object ParseAndConvertBigInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertBigInteger


        /// <summary>
        /// Parse and convert a Big Integer input value, returning a value that is
        /// compatible with a Field of type adUnsignedBigInt.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adUnsignedBigInt columns.
        /// </returns>
        public static object ParseAndConvertUnsignedBigInteger (
            string pstrInputValue )
        {
            if ( ulong.TryParse ( pstrInputValue , out ulong rulngRetVal ) )
            {
                return rulngRetVal;
            }   // TRUE (anticipated outcome) block, if ( ulong.TryParse ( pstrInputValue , out ulong rulngRetVal ) )
            else
            {
                throw new ArgumentOutOfRangeException (
                    nameof ( pstrInputValue ) ,
                    pstrInputValue ,
                    Properties.Resources.ERRMSG_NUMERIC_CONVERSION );
            }   // FALSE (unanticipated outcome) block, if ( ulong.TryParse ( pstrInputValue , out ulong rulngRetVal ) )
        }   // public static object ParseAndConvertUnsignedBigInteger


        /// <summary>
        /// Parse and convert a Boolean input value, returning a value that is
        /// compatible with a Field of type aadBoolean.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pastrFalseStrings">
        /// Pass in the array of strings to treat as valid True values.
        /// </param>
        /// <param name="pastrTrueStrings">
        /// Pass in the array of strings to treat as valid False values.
        /// </param>
        /// <returns>
        /// The return value is a valid value for aadBoolean columns.
        /// </returns>
        public static object ParseAndConvertBoolean (
            string pstrInputValue ,
            string [ ] pastrTrueStrings ,
            string [ ] pastrFalseStrings )
        {
            if ( string.IsNullOrEmpty ( pstrInputValue ) )
            {   // Null references and empty string must be treated as implicitly FALSE.
                return false;
            }   // TRUE (Both null references and the empty string are implictly FALSE.) block, if ( string.IsNullOrEmpty ( pstrInputValue ) )
            else
            {   // Strings that contain characters are compared against two lists of strings, starting with strings that represent True.
                if ( StringIsInList ( pstrInputValue , pastrTrueStrings , CASE_INSENSITIVE ) )
                {   // The input string represents Boolean True.
                    return true;
                }   // TRUE (The input string is in the list of valid True strings, pastrTrueStrings.) block, if ( StringIsInList ( pstrInputValue , pastrTrueStrings , CASE_INSENSITIVE ) )
                else
                {   // The input string isn't in the list of valid True strings. Check the list of valid False strings.
                    if ( StringIsInList ( pstrInputValue , pastrFalseStrings , CASE_INSENSITIVE ) )
                    {   // The input string represents Boolean False.
                        return false;
                    }   // TRUE (The input string is in the list of valid False strings,pastrFalseStrings.), if ( StringIsInList ( pstrInputValue , pastrFalseStrings , CASE_INSENSITIVE ) )
                    else
                    {   // Since I don't trust returning a nullable Boolean in an Object, I have no choice but to throw an ArgumentOutOfRangeException exception, the only kind that lets me explicitly return the parameter name and its value.
                        throw new ArgumentOutOfRangeException (
                            nameof ( pstrInputValue ) ,
                            pstrInputValue ,
                            Properties.Resources.ERRMSG_INVALID_BOOLEAN_VALUE );
                    }   // FALSE (The input string is MOT in the list of valid False strings,pastrFalseStrings.), if ( StringIsInList ( pstrInputValue , pastrFalseStrings , CASE_INSENSITIVE ) )
                }   // FALSE (The input string is NOT in the list of valid True strings, pastrTrueStrings.) block, if ( StringIsInList ( pstrInputValue , pastrTrueStrings , CASE_INSENSITIVE ) )
            }   // FALSE (The string contains at least one character. block, if ( string.IsNullOrEmpty ( pstrInputValue ) )
        }   // public static object ParseAndConvertBoolean


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adCurrency.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adCurrency columns.
        /// </returns>
        public static object ParseAndConvertCurrency (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertCurrency


        /// <summary>
        /// Parse and convert a Date input value, returning a value that is
        /// compatible with a Field of type adDBDate.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pfThrowWhenInvalid">
        /// Specify TRUE to cause the method to throw when supplied with an 
        /// invalid date.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adDBDate columns.
        /// </returns>
        public static object ParseAndConvertDBDate (
            string pstrInputValue ,
            bool pfThrowWhenInvalid )
        {
            if ( string.IsNullOrEmpty ( pstrInputValue ) )
            {
                return null;
            }   // TRUE (degenerate case) block, if ( string.IsNullOrEmpty ( pstrInputValue ) )
            else
            {
                if ( DateTime.TryParse ( pstrInputValue , out DateTime rdtm ) )
                {
                    return rdtm.Date;
                }   // TRUE (anticipated outcome) block, if ( DateTime.TryParse ( pstrInputValue , out DateTime rdtm ) )
                else
                {
                    if ( pfThrowWhenInvalid )
                    {
                        throw new ArgumentOutOfRangeException (
                            nameof ( pstrInputValue ) ,
                            pstrInputValue ,
                            Properties.Resources.ERRMSG_INVALID_DATE_CONVERSION );
                    }   // TRUE (The caller wants an exception when the date won't parse.) block, if ( pfThrowWhenInvalid )
                    else
                    {
                        return null;
                    }   // FALSE (The caller wants invalid dates to be discarded silently.) block, if ( pfThrowWhenInvalid )
                }   // FALSE (unanticipated outcome) block, if ( DateTime.TryParse ( pstrInputValue , out DateTime rdtm ) )
            }   // FALSE (normal case) block, if ( string.IsNullOrEmpty ( pstrInputValue ) )
        }   // public static object ParseAndConvertDBDate


        /// <summary>
        /// Parse and convert a Time input value, returning a value that is
        /// compatible with a Field of type adDBTime.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adDBTime columns.
        /// </returns>
        public static object ParseAndConvertDBTime (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertDBTime


        /// <summary>
        /// Parse and convert a Time input value, returning a value that is
        /// compatible with a Field of type adDBTimeStamp and adFileTime.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adDBTimeStamp and adFileTime columns.
        /// </returns>
        public static object ParseAndConvertDBTimeStamp (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertDBTimeStamp


        /// <summary>
        /// Parse and convert a Date input value, returning a value that is
        /// compatible with a Field of type adDate.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adDate columns.
        /// </returns>
        public static object ParseAndConvertDate (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertDate


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adDecimal.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adDecimal columns.
        /// </returns>
        public static object ParseAndConvertDecimal (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertDecimal


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adDouble.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adDouble columns.
        /// </returns>
        public static object ParseAndConvertDouble (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertDouble


        /// <summary>
        /// Parse and convert a Big Integer input value, returning a value that is
        /// compatible with a Field of type adGUID.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adGUID columns.
        /// </returns>
        public static object ParseAndConvertGuidString (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertGuidString


        /// <summary>
        /// Parse and convert an Integer input value, returning a value that is
        /// compatible with a Field of type adInteger.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adInteger columns.
        /// </returns>
        public static object ParseAndConvertInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertInteger


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adNumeric.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adNumeric columns.
        /// </returns>
        public static object ParseAndConvertNumeric (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision ,
            bool pfTreatadNumericAsNumStr )
        {
            if ( pfTreatadNumericAsNumStr )
            {
                return ReturnOnlyNunNumericChractersInString (
                    pstrInputValue.Length > pintDefinedSize
                        ? pstrInputValue.Substring (
                            ListInfo.SUBSTR_BEGINNING ,
                            pintDefinedSize ) :
                        pstrInputValue );
            }   // TRUE (Treat the input as a numeric string.) block, if ( pfTreatadNumericAsNumStr )
            else
            {
                throw new NotImplementedException (
                    string.Format (
                        @"Method {0} is implemented only for the case when {1} is TRUE." ,
                        nameof ( ParseAndConvertNumeric ) ,
                        nameof ( pfTreatadNumericAsNumStr ) ) );
            }   // FALSE (Treat the input as a numeric value.) block, if ( pfTreatadNumericAsNumStr )            
        }   // public static object ParseAndConvertNumeric


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adPropVariant.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adPropVariant columns.
        /// </returns>
        public static object ParseAndConvertPropVariant (
            string pstrInputValue,
            int pintDefinedSize,
            byte pbytNumericScale,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertPropVariant


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adSingle.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adSingle columns.
        /// </returns>
        public static object ParseAndConvertSingle (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertSingle


        /// <summary>
        /// Parse and convert a Currency input value, returning a value that is
        /// compatible with a Field of type adSmallInt.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adSmallInt columns.
        /// </returns>
        public static object ParseAndConvertSmallInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertSmallInteger


        /// <summary>
        /// Parse and convert a Big Integer input value, returning a value that is
        /// compatible with a Field of type adBSTR, adChar, adLongVarChar,
        /// adLongVarWChar, adVarChar, adVarWChar, adWChar types of a size
        /// specified by the <paramref name="pintDefinedSize"/> argument.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adBSTR, adChar, adLongVarChar,
        /// adLongVarWChar, adVarChar, adVarWChar, and adWChar types.
        /// </returns>
        public static string ParseAndConvertString (
            string pstrInputValue ,
            int pintDefinedSize ,
            bool pfThrowWhenInvalid )
        {
            if ( pstrInputValue.Length <= pintDefinedSize )
            {
                return pstrInputValue;
            }   // TRUE (The supplied string fits.) block, if ( pstrInputValue.Length <= pintDefinedSize )
            else
            {
                if ( pfThrowWhenInvalid )
                {
                    throw new ArgumentOutOfRangeException (
                        nameof ( pstrInputValue ) ,                             // string paramName
                        pstrInputValue ,                                        // object paramValue
                        string.Format (                                         // string message
                            Properties.Resources.MSG_INPUT_TOO_LONG ,           // Format control string
                            new object [ ]
                            {
                                pstrInputValue ,                                // Format Item 0: Input string         = {0}
                                pstrInputValue.Length ,                         // Format Item 1: Input string length  = {1}
                                pintDefinedSize ,                               // Format Item 2: Maximum field length = {2}
                                pstrInputValue.Truncate ( pintDefinedSize ) ,   // Format Item 3: Truncated string     = {3}
                                Environment.NewLine                             // Format Item 4: The input string is too long.{4} .. etc.
                            } ) );
                }   // TRUE (Caller requested to see an exception when input is invalid.) block, if ( pfThrowWhenInvalid )
                else
                {
                    return pstrInputValue.Substring (
                        ListInfo.SUBSTR_BEGINNING ,
                        pstrInputValue.Length );
                }   // FALSE (Caller accepts silent truncation of excess length.) block, if ( pfThrowWhenInvalid )
            }   // FALSE (The supplied string is too long.) block, if ( pstrInputValue.Length <= pintDefinedSize )
        }   // public static object ParseAndConvertString


        /// <summary>
        /// Parse and convert a Big Integer input value, returning a value that is
        /// compatible with a Field of type adTinyInt types.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adTinyInt types.
        /// </returns>
        public static object ParseAndConvertTinyInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertTinyInteger


        /// <summary>
        /// Parse and convert a Big Integer input value, returning a value that is
        /// compatible with a Field of type adUnsignedInt types.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adUnsignedInt types.
        /// </returns>
        public static object ParseAndConvertUnsignedInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertUnsignedInteger


        /// <summary>
        /// Parse and convert an unsigned Smapp Integer input value, returning a value that is
        /// compatible with a Field of type adUnsignedSmallInt types.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adUnsignedSmallInt types.
        /// </returns>
        public static object ParseAndConvertUnsignedSmallInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertUnsignedSmallInteger


        /// <summary>
        /// Parse and convert an unsigned Tiny Integer input value, returning a value that is
        /// compatible with a Field of type adUnsignedTinyInt types.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adUnsignedTinyInt types.
        /// </returns>
        public static object ParseAndConvertUnsignedTinyInteger (
            string pstrInputValue )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertUnsignedTinyInteger


        /// <summary>
        /// Parse and convert a Variable Length Binary input value, returning a
        /// value that is compatible with a Field of type adLongVarBinary types
        /// of a size specified by the <paramref name="pintDefinedSize"/>
        /// argument.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adLongVarBinary types.
        /// </returns>
        public static object ParseAndConvertVarBinary (
            string pstrInputValue ,
            int definedSize )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertVarBinary


        /// <summary>
        /// Parse and convert a Variant input value, returning a value that is
        /// compatible with a Field of type adVariant.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adVariant columns.
        /// </returns>
        public static object ParseAndConvertVariant (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertVariant


        /// <summary>
        /// Parse and convert a Variant Numeric input value, returning a value that is
        /// compatible with a Field of type adVarNumeric.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string representation of the value to parse and convert.
        /// </param>
        /// <param name="pintDefinedSize">
        /// Pass in the DefinedSize property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <param name="pbytNumericScale"></param>
        /// Pass in the NumericScale property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// <param name="pbytPrecision">
        /// Pass in the Precision property from the Field object that
        /// represents the destination column of <paramref name="pstrInputValue"/>.
        /// </param>
        /// <returns>
        /// The return value is a valid value for adVarNumeric columns.
        /// </returns>
        public static object ParseAndConvertVarNumeric (
            string pstrInputValue ,
            int pintDefinedSize ,
            byte pbytNumericScale ,
            byte pbytPrecision )
        {
            throw new NotImplementedException ( );
        }   // public static object ParseAndConvertVarNumeric


        /// <summary>
        /// Scan a string and return only its numeric characters.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string to evaluate.
        /// </param>
        /// <returns>
        /// Scan the characters in the string, returning only its numeric
        /// characters, following a strict interpretation that numeric means a
        /// decimal digit.
        /// </returns>
        private static string ReturnOnlyNunNumericChractersInString (
            string pstrInputValue )
        {
            int intInputStringLength = pstrInputValue.Length;
            StringBuilder rsb = new StringBuilder ( intInputStringLength );

            for ( int intCurrCharPos = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                      intCurrCharPos < intInputStringLength ;
                      intCurrCharPos++ )
            {
                char chrCurr = pstrInputValue [ intCurrCharPos ];

                if ( char.IsDigit ( chrCurr ) )
                {
                    rsb.Append ( chrCurr );
                }   // if ( char.IsDigit ( chrCurr ) )
            }   // for ( int intCurrCharPos = ArrayInfo.ARRAY_FIRST_ELEMENT ; intCurrCharPos < intInputStringLength ; intCurrCharPos++ )
            return rsb.ToString ( );
        }   // private static string DiscardNunNumericChractersInString


        /// <summary>
        /// Evaluate a string against the list of strings in
        /// <paramref name="pastrValidStrings"/>, returning True if
        /// <paramref name="pstrInputValue"/> belongs to the list, and False
        /// otherwise.
        /// </summary>
        /// <param name="pstrInputValue">
        /// Pass in the string to evaluate against the list.
        /// </param>
        /// <param name="pastrValidStrings">
        /// Pass in a reference to the list of strings, an array, against which
        /// to compare <paramref name="pstrInputValue"/> according to the case
        /// sensitivity rule specified by <paramref name="pfCaseSensitive"/>.
        /// </param>
        /// <param name="pfCaseSensitive">
        /// Pass in True to evaluate case sensitive, otherwise FALSE.
        /// </param>
        /// <returns>
        /// This method returns True if string <paramref name="pstrInputValue"/>
        /// is in string array <paramref name="pastrValidStrings"/>. Otherwise,
        /// the return value is FALSE.
        /// </returns>
        /// <see cref="CASE_INSENSITIVE"/>
        /// <see cref="CASE_SENSITIVE"/>
        public static bool StringIsInList (
            string pstrInputValue ,
            string [ ] pastrValidStrings ,
            bool pfCaseSensitive )
        {
            if ( string.IsNullOrEmpty ( pstrInputValue ) )
            {
                return false;
            }   // TRUE (unanticipated degenerate case) block, if ( string.IsNullOrEmpty ( pstrInputValue ) )
            else
            {   // Case sensitive comparisons use the input string as is. Otherwise, it is converted to lower case in a culture-aware fashion.
                string strCompareThis = pfCaseSensitive ? pstrInputValue : pstrInputValue.ToLower ( );
                int intNStrings = pastrValidStrings.Length;

                for ( int intCurrString = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                          intCurrString < intNStrings ;
                          intCurrString++ )
                {   // Case sensitive comparisons use the input string as is. Otherwise, it is converted to lower case in a culture-aware fashion.
                    if ( strCompareThis.Equals ( pfCaseSensitive ? pastrValidStrings [ intCurrString ] : pastrValidStrings [ intCurrString ].ToLower ( ) ) )
                    {
                        return true;                        // Match found. Break out of the loop, and return True.
                    }   // if ( strCompareThis.Equals ( pfCaseSensitive ? pastrValidStrings [ intCurrString ] : pastrValidStrings [ intCurrString ].ToLower ( ) ) )
                }   // for ( int intCurrString = ArrayInfo.ARRAY_FIRST_ELEMENT ; intCurrString < intNStrings ; intCurrString++ )

                return false;                               // The string doesn't match anything in the list.
            }   // FALSE (anticipated case) block, if ( string.IsNullOrEmpty ( pstrInputValue ) )        
        }   // public static bool StringIsInList
    }   // public static class ADOHelpers
}   // partial namespace PSQLviaADOCS