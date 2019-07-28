 ==============================================================================

 Name:                 PSQLviaADO.mc

 Synopsis:             Define messages for use in place of string resources, so
                       that FormatMessage can be used to format them, rather
                       than relying on printf.

 Remarks:              This file was created from the managed resources stored
                       in the C# implementation of this program.

                       The Visual Studio ResXResourceManager extension was used
                       to export the strings into an Excel worksheet. A formula
                       transforms the composite format item tokens into the
                       simpler format supported by the Message Compiler and the
                       native Windows FormatMessage function.

 Author:               David A. Gray

 ------------------------------------------------------------------------------
 Revision History
 ------------------------------------------------------------------------------

 Date       By Synopsis
 ---------- -- ----------------------------------------------------------------
 2019/07/25 DG Create and compile the initial English language message file.
 2019/07/27 DG Rename to match the shorter name of the new project.
 ==============================================================================
-------------------------------------------------------------------------
 HEADER SECTION

 The header section defines names and language identifiers for use
 by the message definitions later in this file. The MessageIdTypedef,
 SeverityNames, FacilityNames, and LanguageNames keywords are
 optional and not required.



 The MessageIdTypedef keyword gives a typedef name that is used in a
 type cast for each message code in the generated include file. Each
 message code appears in the include file with the format: #define
 name ((type) 0xnnnnnnnn) The default value for type is empty, and no
 type cast is generated. It is the programmer's responsibility to
 specify a typedef statement in the application source code to define
 the type. The type used in the typedef must be large enough to
 accommodate the entire 32-bit message code.



 The SeverityNames keyword defines the set of names that are allowed
 as the value of the Severity keyword in the message definition. The
 set is delimited by left and right parentheses. Associated with each
 severity name is a number that, when shifted left by 30, gives the
 bit pattern to logical-OR with the Facility value and MessageId
 value to form the full 32-bit message code. The default value of
 this keyword is:

 SeverityNames=(
   Success=0x0
   Informational=0x1
   Warning=0x2
   Error=0x3
   )

 Severity values occupy the high two bits of a 32-bit message code.
 Any severity value that does not fit in two bits is an error. The
 severity codes can be given symbolic names by following each value
 with :name



 The FacilityNames keyword defines the set of names that are allowed
 as the value of the Facility keyword in the message definition. The
 set is delimited by left and right parentheses. Associated with each
 facility name is a number that, when shift it left by 16 bits, gives
 the bit pattern to logical-OR with the Severity value and MessageId
 value to form the full 32-bit message code. The default value of
 this keyword is:

 FacilityNames=(
   System=0x0FF
   Application=0xFFF
   )

 Facility codes occupy the low order 12 bits of the high order
 16-bits of a 32-bit message code. Any facility code that does not
 fit in 12 bits is an error. This allows for 4,096 facility codes.
 The first 256 codes are reserved for use by the system software. The
 facility codes can be given symbolic names by following each value
 with :name


 The LanguageNames keyword defines the set of names that are allowed
 as the value of the Language keyword in the message definition. The
 set is delimited by left and right parentheses. Associated with each
 language name is a number and a file name that are used to name the
 generated resource file that contains the messages for that
 language. The number corresponds to the language identifier to use
 in the resource table. The number is separated from the file name
 with a colon.

 This doesn't work, because the MC system doesn't fall back the way I expected it to do.
 LanguageNames=(English=0x07f:MSG0007f)

 For now, use this.

 Any new names in the source file which don't override the built-in
 names are added to the list of valid languages. This allows an
 application to support private languages with descriptive names.


-------------------------------------------------------------------------
 MESSAGE DEFINITION SECTION

 Following the header section is the body of the Message Compiler
 source file. The body consists of zero or more message definitions.
 Each message definition begins with one or more of the following
 statements:

 MessageId = [number|+number]
 Severity = severity_name
 Facility = facility_name
 SymbolicName = name

 The MessageId statement marks the beginning of the message
 definition. A MessageID statement is required for each message,
 although the value is optional. If no value is specified, the value
 used is the previous value for the facility plus one. If the value
 is specified as +number then the value used is the previous value
 for the facility, plus the number after the plus sign. Otherwise, if
 a numeric value is given, that value is used. Any MessageId value
 that does not fit in 16 bits is an error.

 The Severity and Facility statements are optional. These statements
 specify additional bits to OR into the final 32-bit message code. If
 not specified they default to the value last specified for a message
 definition. The initial values prior to processing the first message
 definition are:

 Severity=Success
 Facility=Application

 The value associated with Severity and Facility must match one of
 the names given in the FacilityNames and SeverityNames statements in
 the header section. The SymbolicName statement allows you to
 associate a C/C++ symbolic constant with the final 32-bit message
 code.
 */
 // ================================
 // Messages, one for each valid ID:
 // ================================
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_RUNTIME                 0x2
#define FACILITY_STUBS                   0x3
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: IDS_MSG_RECORD_LABEL_PREFIX
//
// MessageText:
//
// Record Number %0:
//
#define IDS_MSG_RECORD_LABEL_PREFIX      ((DWORD)0x00000065L)

//
// MessageId: MSG_COLUMNNAMESANDLABELS_TOSTRING
//
// MessageText:
//
// TableName = %0, ColumnIndex = %1, ColumnName = %2, ColumnValue = %3, ColumnLabel = %4, IsAutoNumberKeyColumn = %5, IsPrimaryKeyColumn = %6
//
#define MSG_COLUMNNAMESANDLABELS_TOSTRING ((DWORD)0x00000066L)

//
// MessageId: MSG_COLUMN_PROPERTIES_LABEL_ROW
//
// MessageText:
//
// Index\tName\tActualSize\tAttributes\tDataFormat\tDefinedSize\tNumericScale\tPrecision\tProperties_Count\tStatus\tType
//
#define MSG_COLUMN_PROPERTIES_LABEL_ROW  ((DWORD)0x00000067L)

//
// MessageId: MSG_DELETED_RECORDS_SUMMARY
//
// MessageText:
//
// Operation completed: total records deleted = %0
//
#define MSG_DELETED_RECORDS_SUMMARY      ((DWORD)0x00000068L)

//
// MessageId: MSG_DELETION_ABORTED
//
// MessageText:
//
// Record deletion aborted by operator.
//
#define MSG_DELETION_ABORTED             ((DWORD)0x00000069L)

//
// MessageId: MSG_DISPLAY_TABLE_NAME_AND_VERB
//
// MessageText:
//
// Processing PSQL database table %0%2                Action Taken = %1%2
//
#define MSG_DISPLAY_TABLE_NAME_AND_VERB  ((DWORD)0x0000006AL)

//
// MessageId: MSG_ERR_DUPLICATE_COLUMN_NAME
//
// MessageText:
//
// Duplicate column name
//
#define MSG_ERR_DUPLICATE_COLUMN_NAME    ((DWORD)0x0000006BL)

//
// MessageId: MSG_ERR_INTERNAL_SQL_ERROR
//
// MessageText:
//
// Internal error: The value in column zero of the result set returned by SQL query %0 is %1, which cannot be converted to a long integer.
//
#define MSG_ERR_INTERNAL_SQL_ERROR       ((DWORD)0x0000006CL)

//
// MessageId: MSG_ERR_INVALID_BOOLEAN_VALUE
//
// MessageText:
//
// The specified value is not a valid Boolean string value.
//
#define MSG_ERR_INVALID_BOOLEAN_VALUE    ((DWORD)0x0000006DL)

//
// MessageId: MSG_ERR_INVALID_DATE_CONVERSION
//
// MessageText:
//
// The specified input value cannot be converted to the specified numeric type.
//
#define MSG_ERR_INVALID_DATE_CONVERSION  ((DWORD)0x0000006EL)

//
// MessageId: MSG_ERR_INVALID_IN_THIS_CONTEXT
//
// MessageText:
//
// Input value '%0' is invalid during %1 operations.%2Please input a valid value.
//
#define MSG_ERR_INVALID_IN_THIS_CONTEXT  ((DWORD)0x0000006FL)

//
// MessageId: MSG_ERR_INVALID_NAME
//
// MessageText:
//
// %1Table name %0 is invalid.%1
//
#define MSG_ERR_INVALID_NAME             ((DWORD)0x00000070L)

//
// MessageId: MSG_ERR_INVALID_SCHEMA_LINE
//
// MessageText:
//
// Line %0 in %1 table schema file %2 is invalid.%6    Expected Column Count = %3%6    Actual Column Count   = %4%6    Text of Invalid Line  = %5%6
//
#define MSG_ERR_INVALID_SCHEMA_LINE      ((DWORD)0x00000071L)

//
// MessageId: MSG_ERR_MATCH_STRING_IS_REQUIRED
//
// MessageText:
//
// There is no reasonable default value; the match string is required.
//
#define MSG_ERR_MATCH_STRING_IS_REQUIRED ((DWORD)0x00000072L)

//
// MessageId: MSG_ERR_NUMERIC_CONVERSION
//
// MessageText:
//
// The specified input value cannot be converted to the specified numeric type.
//
#define MSG_ERR_NUMERIC_CONVERSION       ((DWORD)0x00000073L)

//
// MessageId: MSG_ERR_PREFIX_INVALID_VERB
//
// MessageText:
//
// is not a valid value for CrudVerb.
//
#define MSG_ERR_PREFIX_INVALID_VERB      ((DWORD)0x00000074L)

//
// MessageId: 0x00000075L (No symbolic name defined)
//
// MessageText:
//
// SymbolicName=MSG_INFO_ASSIGNED_COLUMN_VALUE
// Language=English
//         %0: %1 value assigned by system = %2
//


//
// MessageId: MSG_INPUT_TOO_LONG
//
// MessageText:
//
// The input string is too long.%4    Input string         = %0%4    Input string length  = %1%4    Maximum field length = %2%4    Truncated string     = %3%4
//
#define MSG_INPUT_TOO_LONG               ((DWORD)0x00000076L)

//
// MessageId: MSG_LABEL_FOR_LISTING
//
// MessageText:
//
// Listing
//
#define MSG_LABEL_FOR_LISTING            ((DWORD)0x00000077L)

//
// MessageId: MSG_LABEL_FOR_PROPERTIES_LIST
//
// MessageText:
//
// Column Properties
//
#define MSG_LABEL_FOR_PROPERTIES_LIST    ((DWORD)0x00000078L)

//
// MessageId: MSG_LABEL_FOR_TABLE
//
// MessageText:
//
// Table
//
#define MSG_LABEL_FOR_TABLE              ((DWORD)0x00000079L)

//
// MessageId: MSG_PROGRESS_UPDATE
//
// MessageText:
//
//     Listing record # %0 of %1
//
#define MSG_PROGRESS_UPDATE              ((DWORD)0x0000007AL)

//
// MessageId: MSG_PROMPT_COLUMN_NAME
//
// MessageText:
//
// Column Neme against which to match (CR for default value, ID): --->>
//
#define MSG_PROMPT_COLUMN_NAME           ((DWORD)0x0000007BL)

//
// MessageId: MSG_PROMPT_CRITERION
//
// MessageText:
//
// Enter selection criterion (CR for default value, IsEqualTo):   --->>
//
#define MSG_PROMPT_CRITERION             ((DWORD)0x0000007CL)

//
// MessageId: MSG_PROMPT_FOR_FIELD_VALUE
//
// MessageText:
//
//         %0: Enter value for field %1:
//
#define MSG_PROMPT_FOR_FIELD_VALUE       ((DWORD)0x0000007DL)

//
// MessageId: MSG_PROMPT_FOR_NEW_FIELD_VALUE
//
// MessageText:
//
//        %0: Current value of field %1 = %2%4           Enter new value, or '%3' to keep the existing value. --->>
//
#define MSG_PROMPT_FOR_NEW_FIELD_VALUE   ((DWORD)0x0000007EL)

//
// MessageId: MSG_PROMPT_FOR_NEW_VALUES
//
// MessageText:
//
//     Enter values for the new record in response to the following prompts.%0
//
#define MSG_PROMPT_FOR_NEW_VALUES        ((DWORD)0x0000007FL)

//
// MessageId: MSG_PROMPT_FOR_TABLE_NAME
//
// MessageText:
//
//     Specify which table to process.
//
#define MSG_PROMPT_FOR_TABLE_NAME        ((DWORD)0x00000080L)

//
// MessageId: MSG_PROMPT_MATCH_STRING
//
// MessageText:
//
// Column Value (There is no default. You must enter a value.):   --->>
//
#define MSG_PROMPT_MATCH_STRING          ((DWORD)0x00000081L)

//
// MessageId: MSG_PROMPT_ONE_ROW_ONLY
//
// MessageText:
//
// The update routine supports updating only one row at a time. Your query returned %0 rows.
//
#define MSG_PROMPT_ONE_ROW_ONLY          ((DWORD)0x00000082L)

//
// MessageId: MSG_PROMPT_TRUNCATE_OK
//
// MessageText:
//
// The input string is too long.%1    To make it fit, it must be truncated to %0.%1    Is that OK (Y/N)?
//
#define MSG_PROMPT_TRUNCATE_OK           ((DWORD)0x00000083L)

//
// MessageId: MSG_REPORT_HEADER
//
// MessageText:
//
// Report Name: Listing of Everything in a PSQL Table%4Run Date: %0 (%1 UTC)%4%4Table Name       = %2%4Records in Table = %3%4
//
#define MSG_REPORT_HEADER                ((DWORD)0x00000084L)

//
// MessageId: MSG_SCHEMA_PROGRESS
//
// MessageText:
//
//     Listing Column # %0, %1 of table %2
//
#define MSG_SCHEMA_PROGRESS              ((DWORD)0x00000085L)

//
// MessageId: MSG_SELECTION_COUNT_AND_PROMPT
//
// MessageText:
//
// %0 records meet the selection criteria? OK to delete them? (Y/N) --->>
//
#define MSG_SELECTION_COUNT_AND_PROMPT   ((DWORD)0x00000086L)

//
// MessageId: MSG_SELECTION_CRITERIA
//
// MessageText:
//
// %3Selection Criteria:%3%3    Column (Field) Name = %0%3    Criterion Value     = %2%3    Criterion Condition = %1%3
//
#define MSG_SELECTION_CRITERIA           ((DWORD)0x00000087L)

//
// MessageId: MSG_SELECT_QUERY
//
// MessageText:
//
//     SQL SELECT Query    = %0%1
//
#define MSG_SELECT_QUERY                 ((DWORD)0x00000088L)

//
// MessageId: MSG_TASK_SUMMARY
//
// MessageText:
//
// %0%1 File Name = %2
//
#define MSG_TASK_SUMMARY                 ((DWORD)0x00000089L)

//
// MessageId: PROMPT_NO_ROWS_SELECTED
//
// MessageText:
//
// Your selection matched no records. Nothing will happen.
//
#define PROMPT_NO_ROWS_SELECTED          ((DWORD)0x0000008AL)

//
// MessageId: REPORT_FOOTER
//
// MessageText:
//
// End of report, Total records = %0
//
#define REPORT_FOOTER                    ((DWORD)0x0000008BL)

//
// MessageId: UNIQUE_COLUMN_NAME_TOSTRING
//
// MessageText:
//
// TableName = %1, ColumnName = %0
//
#define UNIQUE_COLUMN_NAME_TOSTRING      ((DWORD)0x0000008CL)

 ==============================================================================
                                T h e   E n d
 ==============================================================================
