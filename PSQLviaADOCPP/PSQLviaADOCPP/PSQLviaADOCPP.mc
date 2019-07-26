; ==============================================================================
;
; Name:                 PSQLviaADOCPP_Messages.mc
;
; Synopsis:             Define messages for use in place of string resources, so
;                       that FormatMessage can be used to format them, rather
;                       than relying on printf.
;
; Remarks:              This file was created from the managed resources stored
;                       in the C# implementation of this program.
;
;                       The Visual Studio ResXResourceManager extension was used
;                       to export the strings into an Excel worksheet. A formula
;                       transforms the composite format item tokens into the
;                       simpler format supported by the Message Compiler and the
;                       native Windows FormatMessage function.
;
; Author:               David A. Gray
;
; ------------------------------------------------------------------------------
; Revision History
; ------------------------------------------------------------------------------
;
; Date       By Synopsis
; ---------- -- ----------------------------------------------------------------
; 2019/07/25 DG Create and compile the initial English language message file.
; ==============================================================================

;-------------------------------------------------------------------------
; HEADER SECTION
;
; The header section defines names and language identifiers for use
; by the message definitions later in this file. The MessageIdTypedef,
; SeverityNames, FacilityNames, and LanguageNames keywords are
; optional and not required.
;
;
MessageIdTypedef=DWORD
;
; The MessageIdTypedef keyword gives a typedef name that is used in a
; type cast for each message code in the generated include file. Each
; message code appears in the include file with the format: #define
; name ((type) 0xnnnnnnnn) The default value for type is empty, and no
; type cast is generated. It is the programmer's responsibility to
; specify a typedef statement in the application source code to define
; the type. The type used in the typedef must be large enough to
; accommodate the entire 32-bit message code.
;
;
SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
              )
;
; The SeverityNames keyword defines the set of names that are allowed
; as the value of the Severity keyword in the message definition. The
; set is delimited by left and right parentheses. Associated with each
; severity name is a number that, when shifted left by 30, gives the
; bit pattern to logical-OR with the Facility value and MessageId
; value to form the full 32-bit message code. The default value of
; this keyword is:
;
; SeverityNames=(
;   Success=0x0
;   Informational=0x1
;   Warning=0x2
;   Error=0x3
;   )
;
; Severity values occupy the high two bits of a 32-bit message code.
; Any severity value that does not fit in two bits is an error. The
; severity codes can be given symbolic names by following each value
; with :name
;
;
FacilityNames=(System=0x0:FACILITY_SYSTEM
               Runtime=0x2:FACILITY_RUNTIME
               Stubs=0x3:FACILITY_STUBS
               Io=0x4:FACILITY_IO_ERROR_CODE
              )
;
; The FacilityNames keyword defines the set of names that are allowed
; as the value of the Facility keyword in the message definition. The
; set is delimited by left and right parentheses. Associated with each
; facility name is a number that, when shift it left by 16 bits, gives
; the bit pattern to logical-OR with the Severity value and MessageId
; value to form the full 32-bit message code. The default value of
; this keyword is:
;
; FacilityNames=(
;   System=0x0FF
;   Application=0xFFF
;   )
;
; Facility codes occupy the low order 12 bits of the high order
; 16-bits of a 32-bit message code. Any facility code that does not
; fit in 12 bits is an error. This allows for 4,096 facility codes.
; The first 256 codes are reserved for use by the system software. The
; facility codes can be given symbolic names by following each value
; with :name
;
;
; The LanguageNames keyword defines the set of names that are allowed
; as the value of the Language keyword in the message definition. The
; set is delimited by left and right parentheses. Associated with each
; language name is a number and a file name that are used to name the
; generated resource file that contains the messages for that
; language. The number corresponds to the language identifier to use
; in the resource table. The number is separated from the file name
; with a colon.
;
; This doesn't work, because the MC system doesn't fall back the way I expected it to do.
; LanguageNames=(English=0x07f:MSG0007f)
;
; For now, use this.
LanguageNames=(English=0x409:MSG00409)
;
; Any new names in the source file which don't override the built-in
; names are added to the list of valid languages. This allows an
; application to support private languages with descriptive names.
;
;
;-------------------------------------------------------------------------
; MESSAGE DEFINITION SECTION
;
; Following the header section is the body of the Message Compiler
; source file. The body consists of zero or more message definitions.
; Each message definition begins with one or more of the following
; statements:
;
; MessageId = [number|+number]
; Severity = severity_name
; Facility = facility_name
; SymbolicName = name
;
; The MessageId statement marks the beginning of the message
; definition. A MessageID statement is required for each message,
; although the value is optional. If no value is specified, the value
; used is the previous value for the facility plus one. If the value
; is specified as +number then the value used is the previous value
; for the facility, plus the number after the plus sign. Otherwise, if
; a numeric value is given, that value is used. Any MessageId value
; that does not fit in 16 bits is an error.
;
; The Severity and Facility statements are optional. These statements
; specify additional bits to OR into the final 32-bit message code. If
; not specified they default to the value last specified for a message
; definition. The initial values prior to processing the first message
; definition are:
;
; Severity=Success
; Facility=Application
;
; The value associated with Severity and Facility must match one of
; the names given in the FacilityNames and SeverityNames statements in
; the header section. The SymbolicName statement allows you to
; associate a C/C++ symbolic constant with the final 32-bit message
; code.
; */

; // ================================
; // Messages, one for each valid ID:
; // ================================

MessageId=0x65
Facility=Application
Severity=Success
SymbolicName=IDS_MSG_RECORD_LABEL_PREFIX
Language=English
Record Number %0:
.
MessageId=0x66
Facility=Application
Severity=Success
SymbolicName=MSG_COLUMNNAMESANDLABELS_TOSTRING
Language=English
TableName = %0, ColumnIndex = %1, ColumnName = %2, ColumnValue = %3, ColumnLabel = %4, IsAutoNumberKeyColumn = %5, IsPrimaryKeyColumn = %6
.
MessageId=0x67
Facility=Application
Severity=Success
SymbolicName=MSG_COLUMN_PROPERTIES_LABEL_ROW
Language=English
Index\tName\tActualSize\tAttributes\tDataFormat\tDefinedSize\tNumericScale\tPrecision\tProperties_Count\tStatus\tType
.
MessageId=0x68
Facility=Application
Severity=Success
SymbolicName=MSG_DELETED_RECORDS_SUMMARY
Language=English
Operation completed: total records deleted = %0
.
MessageId=0x69
Facility=Application
Severity=Success
SymbolicName=MSG_DELETION_ABORTED
Language=English
Record deletion aborted by operator.
.
MessageId=0x6A
Facility=Application
Severity=Success
SymbolicName=MSG_DISPLAY_TABLE_NAME_AND_VERB
Language=English
Processing PSQL database table %0%2                Action Taken = %1%2
.
MessageId=0x6B
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_DUPLICATE_COLUMN_NAME
Language=English
Duplicate column name
.
MessageId=0x6C
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_INTERNAL_SQL_ERROR
Language=English
Internal error: The value in column zero of the result set returned by SQL query %0 is %1, which cannot be converted to a long integer.
.
MessageId=0x6D
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_INVALID_BOOLEAN_VALUE
Language=English
The specified value is not a valid Boolean string value.
.
MessageId=0x6E
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_INVALID_DATE_CONVERSION
Language=English
The specified input value cannot be converted to the specified numeric type.
.
MessageId=0x6F
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_INVALID_IN_THIS_CONTEXT
Language=English
Input value '%0' is invalid during %1 operations.%2Please input a valid value.
.
MessageId=0x70
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_INVALID_NAME
Language=English
%1Table name %0 is invalid.%1
.
MessageId=0x71
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_INVALID_SCHEMA_LINE
Language=English
Line %0 in %1 table schema file %2 is invalid.%6    Expected Column Count = %3%6    Actual Column Count   = %4%6    Text of Invalid Line  = %5%6
.
MessageId=0x72
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_MATCH_STRING_IS_REQUIRED
Language=English
There is no reasonable default value; the match string is required.
.
MessageId=0x73
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_NUMERIC_CONVERSION
Language=English
The specified input value cannot be converted to the specified numeric type.
.
MessageId=0x74
Facility=Application
Severity=Success
SymbolicName=MSG_ERR_PREFIX_INVALID_VERB
Language=English
is not a valid value for CrudVerb.
.
MessageId=0x75
Facility=Application
Severity=Success
Language=English
SymbolicName=MSG_INFO_ASSIGNED_COLUMN_VALUE
Language=English
        %0: %1 value assigned by system = %2
.
MessageId=0x76
Facility=Application
Severity=Success
SymbolicName=MSG_INPUT_TOO_LONG
Language=English
The input string is too long.%4    Input string         = %0%4    Input string length  = %1%4    Maximum field length = %2%4    Truncated string     = %3%4
.
MessageId=0x77
Facility=Application
Severity=Success
SymbolicName=MSG_LABEL_FOR_LISTING
Language=English
Listing
.
MessageId=0x78
Facility=Application
Severity=Success
SymbolicName=MSG_LABEL_FOR_PROPERTIES_LIST
Language=English
Column Properties
.
MessageId=0x79
Facility=Application
Severity=Success
SymbolicName=MSG_LABEL_FOR_TABLE
Language=English
Table
.
MessageId=0x7A
Facility=Application
Severity=Success
SymbolicName=MSG_PROGRESS_UPDATE
Language=English
    Listing record # %0 of %1
.
MessageId=0x7B
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_COLUMN_NAME
Language=English
Column Neme against which to match (CR for default value, ID): --->>
.
MessageId=0x7C
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_CRITERION
Language=English
Enter selection criterion (CR for default value, IsEqualTo):   --->>
.
MessageId=0x7D
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_FOR_FIELD_VALUE
Language=English
        %0: Enter value for field %1:
.
MessageId=0x7E
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_FOR_NEW_FIELD_VALUE
Language=English
       %0: Current value of field %1 = %2%4           Enter new value, or '%3' to keep the existing value. --->>
.
MessageId=0x7F
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_FOR_NEW_VALUES
Language=English
    Enter values for the new record in response to the following prompts.%0
.
MessageId=0x80
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_FOR_TABLE_NAME
Language=English
    Specify which table to process.
.
MessageId=0x81
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_MATCH_STRING
Language=English
Column Value (There is no default. You must enter a value.):   --->>
.
MessageId=0x82
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_ONE_ROW_ONLY
Language=English
The update routine supports updating only one row at a time. Your query returned %0 rows.
.
MessageId=0x83
Facility=Application
Severity=Success
SymbolicName=MSG_PROMPT_TRUNCATE_OK
Language=English
The input string is too long.%1    To make it fit, it must be truncated to %0.%1    Is that OK (Y/N)?
.
MessageId=0x84
Facility=Application
Severity=Success
SymbolicName=MSG_REPORT_HEADER
Language=English
Report Name: Listing of Everything in a PSQL Table%4Run Date: %0 (%1 UTC)%4%4Table Name       = %2%4Records in Table = %3%4
.
MessageId=0x85
Facility=Application
Severity=Success
SymbolicName=MSG_SCHEMA_PROGRESS
Language=English
    Listing Column # %0, %1 of table %2
.
MessageId=0x86
Facility=Application
Severity=Success
SymbolicName=MSG_SELECTION_COUNT_AND_PROMPT
Language=English
%0 records meet the selection criteria? OK to delete them? (Y/N) --->>
.
MessageId=0x87
Facility=Application
Severity=Success
SymbolicName=MSG_SELECTION_CRITERIA
Language=English
%3Selection Criteria:%3%3    Column (Field) Name = %0%3    Criterion Value     = %2%3    Criterion Condition = %1%3
.
MessageId=0x88
Facility=Application
Severity=Success
SymbolicName=MSG_SELECT_QUERY
Language=English
    SQL SELECT Query    = %0%1
.
MessageId=0x89
Facility=Application
Severity=Success
SymbolicName=MSG_TASK_SUMMARY
Language=English
%0%1 File Name = %2
.
MessageId=0x8A
Facility=Application
Severity=Success
SymbolicName=PROMPT_NO_ROWS_SELECTED
Language=English
Your selection matched no records. Nothing will happen.
.
MessageId=0x8B
Facility=Application
Severity=Success
SymbolicName=REPORT_FOOTER
Language=English
End of report, Total records = %0
.
MessageId=0x8C
Facility=Application
Severity=Success
SymbolicName=UNIQUE_COLUMN_NAME_TOSTRING
Language=English
TableName = %1, ColumnName = %0
.

; ==============================================================================
;                                T h e   E n d
; ==============================================================================
