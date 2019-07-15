/*
    ============================================================================

    Assembly Name:        PSQLviaADOCS

    Root Namespace Name:  PSQLviaADOandVB

    Module Name:          Module1

    Module Objective:     This application demonstrates basic CRUD operations,
                          which were once also called ACID operations, on a 
                          Pervacive SQL (BTrieve) data base, using the ADODB
                          data provider through COM interop.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------
'
    Date       Version By Description
    ---------- ------- ---------------------------------------------------------
    2019/07/12 1.0.0.0 DG Initial implementation.

    2019/07/14 1.1.0.0 DG Make the implementation much more data driven.
    ============================================================================
*/


using System;

using System.IO;                                            // File and stream I/O routines come from this namespace.
using System.Text;                                          // Text encoders and string builders come from this namespace.

using ADODB;                                                // Use ADODB via COM interop.

using WizardWrx;                                            // Import functions from the Common and Core libraries that live in the root namespace.
using WizardWrx.ConsoleAppAids3;                            // This subsidiary namespace includes a handful of closely related specialized classes.

namespace PSQLviaADOCS
{
    class Program
    {
        enum OutputFileType
        {
            DetailListReport,
            DetailTabularReport
        }   // enum OutputFileType

        static ConsoleAppStateManager s_csm = ConsoleAppStateManager.GetTheSingleInstance ( );

        static readonly string s_strRecordLabelPrefix = Properties.Resources.MSG_RECORD_LABEL_PREFIX;

        static void Main ( string [ ] args )
        {
            s_csm.DisplayBOJMessage ( );
            s_csm.BaseStateManager.AppExceptionLogger.OptionFlags = s_csm.BaseStateManager.AppExceptionLogger.OptionFlags | WizardWrx.DLLConfigurationManager.ExceptionLogger.OutputOptions.Stack;

            try
            {
                DoTask ( args );
            }
            catch ( Exception ex )
            {
                s_csm.BaseStateManager.AppExceptionLogger.ReportException ( ex );
                s_csm.BaseStateManager.AppReturnCode = MagicNumbers.ERROR_RUNTIME;
            }
            finally
            {
                //  ------------------------------------------------------------
                //  Since both NormalExit and ErrorExit call DisplayEOJMessage,
                //  having the main routine do so produces duplicate messages.
                //  ------------------------------------------------------------

                if ( s_csm.BaseStateManager.AppReturnCode == MagicNumbers.ERROR_SUCCESS )
                {
                    s_csm.NormalExit ( ConsoleAppStateManager.NormalExitAction.Timed );
                }   // TRUE (anticipated outcome) block, if ( Environment.ExitCode == MagicNumbers.ERROR_SUCCESS )
                else
                {
                    s_csm.ErrorExit ( ( uint ) Environment.ExitCode );
                }   // FALSE (unanticipated outcome) block, if ( Environment.ExitCode == MagicNumbers.ERROR_SUCCESS )
            }   // Try/Catch/Finally block
        }   // static void Main


        private static void DoTask ( string [ ] pastrArgs )
        {
            const string CONNECTION_STRING = @"Provider=PervasiveOLEDB;Data Source=Demodata";
            const string TABLE_NAME_IS_BILLING = @"Billing";

            string strTableName = pastrArgs.Length > ListInfo.LIST_IS_EMPTY
                ? pastrArgs [ ArrayInfo.ARRAY_FIRST_ELEMENT ]
                : PromptForTableName ( );
            Connection cn = new Connection ( );
            Recordset rs = new Recordset ( );

            StreamWriter swDetailsList = null;
            StreamWriter swDetailsTable = null;

            long lngItemNumber = ListInfo.LIST_IS_EMPTY;

            //  --------------------------------------------------------------------
            //  This should always be adUseServer unless you specifically want touse
            //  use the Client Cursor Engine.
            //  --------------------------------------------------------------------

            cn.CursorLocation = CursorLocationEnum.adUseServer;
            cn.ConnectionString = CONNECTION_STRING;

            try
            {
                string strDetailListReportFQFN = AssembleReportFileName (
                        OutputFileType.DetailListReport ,
                        strTableName );
                string strDetailTabularReportFQFN = AssembleReportFileName (
                        OutputFileType.DetailTabularReport ,
                        strTableName );
                ColumnNamesAndLabels [ ] aobjColumnNamesAndLabels = CreateNameAndLabelArray ( strTableName );
                FixedConsoleWriter fcwProgress = new FixedConsoleWriter (
                    ConsoleColor.Yellow ,
                    ConsoleColor.Black );

                cn.Open ( );
                rs.Open (
                    TABLE_NAME_IS_BILLING ,
                    cn ,
                    CursorTypeEnum.adOpenDynamic ,
                    LockTypeEnum.adLockOptimistic ,
                    ( int ) CommandTypeEnum.adCmdTableDirect );
                rs.MoveFirst ( );
                swDetailsList = new StreamWriter (
                    strDetailListReportFQFN ,
                    FileIOFlags.FILE_OUT_CREATE ,
                    Encoding.UTF8 ,
                    MagicNumbers.CAPACITY_08KB );
                swDetailsTable = new StreamWriter (
                    strDetailTabularReportFQFN ,
                    FileIOFlags.FILE_OUT_CREATE ,
                    Encoding.UTF8 ,
                    MagicNumbers.CAPACITY_08KB );

                while ( !rs.EOF )
                {
                    ListAllFieldsOnConsole (
                        rs ,
                        aobjColumnNamesAndLabels ,
                        Utils.SetToIncrementedValue ( ref lngItemNumber ) ,
                        swDetailsList ,
                        swDetailsTable ,
                        fcwProgress );
                    rs.MoveNext ( );
                }   // while ( !rs.EOF )

                swDetailsList.WriteLine (
                    Properties.Resources.REPORT_FOOTER ,
                    lngItemNumber );

                //  ------------------------------------------------------------
                //  Without ScrollUp, the next line written by Console.WriteLine
                //  is appended to the last line written by FixedConsoleWriter
                //  object fcwProgress.
                //  ------------------------------------------------------------

                fcwProgress.ScrollUp ( );
                Console.WriteLine (
                    Properties.Resources.MSG_TASK_SUMMARY ,
                    Environment.NewLine ,
                    Properties.Resources.MSG_LABEL_FOR_LISTING ,
                    strDetailListReportFQFN );
                Console.WriteLine (
                    Properties.Resources.MSG_TASK_SUMMARY ,
                    SpecialStrings.EMPTY_STRING ,
                    Properties.Resources.MSG_LABEL_FOR_TABLE ,
                    strDetailTabularReportFQFN );
            }
            catch ( Exception ex )
            {
                s_csm.BaseStateManager.AppExceptionLogger.ReportException ( ex );
                s_csm.BaseStateManager.AppReturnCode = MagicNumbers.ERROR_RUNTIME;
            }
            finally
            {
                rs.Close ( );
                cn.Close ( );

                if ( swDetailsList.BaseStream.CanWrite )
                {   // The StreamWriter is open, as should be the case, since we dispensed with a Using block.
                    swDetailsList.Close ( );
                }   // if ( swDetailsList.BaseStream.CanWrite )

                if ( swDetailsTable.BaseStream.CanWrite )
                {   // The StreamWriter is open, as should be the case, since we dispensed with a Using block.
                    swDetailsTable.Close ( );
                }   // if ( swDetailsTable.BaseStream.CanWrite )

                swDetailsList.Dispose ( );
                swDetailsTable.Dispose ( );
            }
        }   // private static void DoTask


        private static string AssembleReportFileName (
            OutputFileType penmOutputFileType ,
            string pstrTableName )
        {
            const string ASSEMBLY_TITLE_TOKEN = @"$$AssemblyTitle$$";
            const string TABLE_NAME_TOKEN = @"$$TableName$$";

            string strReportFileNameTemplate = null;

            switch ( penmOutputFileType )
            {
                case OutputFileType.DetailListReport:
                    strReportFileNameTemplate = Properties.Settings.Default.DetailReportListFileNameTemplate;
                    break;
                case OutputFileType.DetailTabularReport:
                    strReportFileNameTemplate = Properties.Settings.Default.DetailTabularReportFileNameTemplate;
                    break;
                default:
                    throw new System.ComponentModel.InvalidEnumArgumentException (
                        nameof ( penmOutputFileType ) ,
                        ( int ) penmOutputFileType ,
                        penmOutputFileType.GetType ( ) );
            }   // switch ( penmOutputFileType )

            string strReportFileName = strReportFileNameTemplate.Replace (
                ASSEMBLY_TITLE_TOKEN ,
                s_csm.BaseStateManager.AppRootAssemblyFileBaseName ).Replace (
                TABLE_NAME_TOKEN ,
                pstrTableName );
            return FileNameTricks.MakeFQFN (
                strReportFileName ,
                Properties.Settings.Default.ReportsDirectoryName );
        }   // private static string AssembleReportFileName


        private static ColumnNamesAndLabels [ ] CreateNameAndLabelArray ( string pstrTableName )
        {
            const int POS_COLUMN_NAME = ArrayInfo.ARRAY_FIRST_ELEMENT;
            const int POS_COLUMN_LABEL = POS_COLUMN_NAME + ArrayInfo.NEXT_INDEX;
            const int EXPECTED_COLUMN_COUNT = POS_COLUMN_LABEL + ArrayInfo.NEXT_INDEX;

            string strTableSchemaFQFN = DeriveTableSchemaFQFN ( pstrTableName );
            string [ ] astrSchemaLines = File.ReadAllLines ( strTableSchemaFQFN );
            int intLineCount = astrSchemaLines.Length;
            ColumnNamesAndLabels [ ] raColumnNamesAndLabels = new ColumnNamesAndLabels [ ArrayInfo.IndexFromOrdinal ( intLineCount ) ];

            for ( int intLineNumber = ArrayInfo.ARRAY_SECOND_ELEMENT ;
                      intLineNumber < intLineCount ;
                      intLineNumber++ )
            {
                string [ ] astrColumnMetaData = astrSchemaLines [ intLineNumber ].Split ( SpecialCharacters.TAB_CHAR );

                if ( astrColumnMetaData.Length == EXPECTED_COLUMN_COUNT )
                {
                    raColumnNamesAndLabels [ ArrayInfo.IndexFromOrdinal ( intLineNumber ) ] = new ColumnNamesAndLabels (
                        new ColumnNamesAndLabels.UniqueColumnName (
                            astrColumnMetaData [ POS_COLUMN_NAME ] ,
                            pstrTableName ) ,
                        astrColumnMetaData [ POS_COLUMN_LABEL ] );
                }   // TRUE (anticipated outcome) block, if ( astrColumnMetaData.Length == EXPECTED_COLUMN_COUNT )
                else
                {
                    throw new InvalidOperationException (
                        string.Format (
                            Properties.Resources.ERRMSG_INVALID_SCHEMA_LINE ,   // Format Control String
                            new object [ ]
                            {
                                intLineNumber ,                                 // Format Item 0: Line {0}
                                pstrTableName ,                                 // Format Item 1: in {1}
                                strTableSchemaFQFN ,                            // Format Item 2: table schema file {2}
                                EXPECTED_COLUMN_COUNT ,                         // Format Item 3: Expected Column Count = {3}
                                astrColumnMetaData.Length ,                     // Format Item 4: Actual Column Count   = {4}
                                astrSchemaLines [ intLineNumber ] ,             // Format Item 5: Text of Invalid Line  = {5}
                                Environment.NewLine                             // Format Item 6: Embedded platform-dependent newline token
                            } ) );
                }   // FALSE (unanticipated outcome) block, if ( astrColumnMetaData.Length == EXPECTED_COLUMN_COUNT )
                //raColumnNamesAndLabels[ArrayInfo.IndexFromOrdinal(intLineNumber)]=new ColumnNamesAndLabels()
            }   // for ( int intLineNumber = ArrayInfo.ARRAY_SECOND_ELEMENT ; intLineNumber < intLineCount ; intLineNumber++ )

            return raColumnNamesAndLabels;
        }   // private static ColumnNamesAndLabels [ ] CreateNameAndLabelArray


        /// <summary>
        /// Derive the absolute (fully qualified) name of the file that contains
        /// the table schema metadata to process.
        /// </summary>
        /// <param name="pstrTableName">
        /// Pass in a string containing the name of the table, from which to
        /// derive the absolute name of the file that contains its schema data.
        /// </param>
        /// <returns>
        /// The return value is a string that contains the absolute (fully
        /// qualified) name of the file that contains the schema to process.
        /// </returns>
        private static string DeriveTableSchemaFQFN ( string pstrTableName )
        {
            return FileNameTricks.MakeFQFN (
                    string.Concat (
                        @"Table_" ,
                        pstrTableName ,
                        @".TSV" ) ,
                    Properties.Settings.Default.TableSchemasDirectoryName.ToString ( ) );
        }   // private static string DeriveTableSchemaFQFN


        /// <summary>
        /// List all columns (fields) in the Current record of a recordset.
        /// </summary>
        /// <param name="prs">
        /// Pass in a reference to an ADODB.Recordset that has a valid
        /// (not null) Current property.
        /// </param>
        /// <param name="paColumnInfo">
        /// Pass in a reference to the ColumnNamesAndLabels array that supplies
        /// column names and labels for the report.
        /// </param>
        /// <param name="plngItemNumber">
        /// Pass in the current value of the item number. Passing in the value
        /// returned by Utils.SetToIncrementedValue works well, as this single
        /// step also increments the item number. This value is safe to pass by
        /// value.
        /// </param>
        /// <param name="pswDetailsList">
        /// Pass in a reference to the open StreamWriter onto which the itemized
        /// list of billing items is written as sets of vertically aligned column
        /// names and values. Using <paramref name="plngItemNumber"/>, this routine
        /// looks after writing the label row.
        /// </param>
        /// <param name="pswDetailsTable">
        /// Pass in a reference to the open StreamWriter onto which the details are
        /// written as tab delimited rows. Using <paramref name="plngItemNumber"/>,
        /// this routine looks after writing the label row.
        /// </param>
        /// <param name="pfcwProgress">
        /// Pass in a reference to a working ConsoleAppAids3.FixedConsoleWriter
        /// object through which the program updates the console without
        /// scrolling the text above it off the screen.
        /// <para>
        /// FixedConsoleWriter never writes trailing newlines toat would defeat
        /// its purpose.
        /// </para>
        /// </param>
        private static void ListAllFieldsOnConsole (
            Recordset prs ,
            ColumnNamesAndLabels [ ] paColumnInfo ,
            long plngItemNumber ,
            StreamWriter pswDetailsList ,
            StreamWriter pswDetailsTable ,
            FixedConsoleWriter pfcwProgress )
        {
            const string LIST_REPORT_FORMAT_CONTROL_STRING = @"{0}{1}: {2}{3}";

            //  ----------------------------------------------------------------
            //  Explicitly initializing this to null resolves a fatal compiler
            //  error. Though the code initializes it before its first use, the
            //  compiler has no way of knowing that it does without some serious
            //  static analysis that probably won't happen until too late in the
            //  compilation process.
            //  ----------------------------------------------------------------

            string strLeadingWhiteSpace = null;
            string strListTokenZero = null;

            //  ----------------------------------------------------------------
            //  This property is referenced many times, including every 
            //  iteration of two FOR loops that make seven iterations each.
            //  Stashing it in a local variable trades 4 bytes of stack space to
            //  hold the value typed variable for fifteen or more calls into the
            //  array class to get the length.
            //
            //  Beware: The size of a C# array is one greater than the value of
            //          its upper bound. Hence, the last subscript is one less
            //          than the length of the array, ArrayInfo.IndexFromOrdinal
            //          makes this adjustment, while its inverse,
            //          ArrayInfo.OrdinalFromIndex, derives the length from the
            //          upper bound or converts any subscript to the equivalent
            //          ordinal position of an array element. Used correctly,
            //          these two bits of syntactic sugar are intended to 
            //          prevent off-by-one logic errors.
            //  ----------------------------------------------------------------

            int intLastIndex = ArrayInfo.IndexFromOrdinal ( paColumnInfo.Length );
            pfcwProgress.Write (
                Properties.Resources.MSG_PROGRESS_UPDATE ,
                plngItemNumber );

            //  ----------------------------------------------------------------
            //  The calling routine initializes plngItemNumber to one before the
            //  first call, and increments it on each subsequent call. Hence, a
            //  test for its value being 1 eliminates the need for a separate
            //  first-pass flag that would cost the same amount to test, at the
            //  expense of 4 bytes of stack space for the extra value type.
            //
            //  Before the first record is written, the report labels must be
            //  generated and written.
            //  ----------------------------------------------------------------

            if ( plngItemNumber == MagicNumbers.PLUS_ONE )
            {
                StringBuilder sbTableLabelRow = new StringBuilder ( MagicNumbers.CAPACITY_01KB );

                for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                          intJ <= intLastIndex ;
                          intJ++ )
                {
                    if ( intJ > ArrayInfo.ARRAY_FIRST_ELEMENT )
                    {   // All except the first element must be preceded by a TAB character.
                        sbTableLabelRow.Append ( SpecialCharacters.TAB_CHAR );
                    }   // if ( intJ > ArrayInfo.ARRAY_FIRST_ELEMENT )

                    sbTableLabelRow.Append ( paColumnInfo [ intJ ].ColumnName );
                }   // for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ; intJ <= intLastIndex ; intJ++ )

                pswDetailsList.WriteLine (
                    Properties.Resources.MSG_REPORT_HEADER ,
                    System.Diagnostics.Process.GetCurrentProcess ( ).StartTime ,
                    System.Diagnostics.Process.GetCurrentProcess ( ).StartTime.ToUniversalTime ( ) ,
                    Environment.NewLine );
                pswDetailsTable.WriteLine ( sbTableLabelRow.ToString ( ) );
            }   // if ( plngItemNumber == MagicNumbers.PLUS_ONE )

            //  ----------------------------------------------------------------
            //  Next, the detail record is processed. The tab-delimited report
            //  is assembled in a StringBuilder, which is written at the end of
            //  the final iteration. Meanwhile, a small FOR loop reads the
            //  column names and column labels from the array, appending a line
            //  to the list report print file for each column (field).
            //  ----------------------------------------------------------------

            StringBuilder sbTableDetailRow = new StringBuilder ( MagicNumbers.CAPACITY_01KB );

            for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                      intJ <= intLastIndex ;
                      intJ++ )
            {
                //  ------------------------------------------------------------
                //  The Visual Basic implementation used a Select Case block,
                //  which permits evaluation of variables within its subsidiary
                //  Case blocks. Alas, switch blocks in C, C++, and C# forbid
                //  case blocks that evaluate variables. Hence, the simpler
                //  switch must be replaced with a conventional cascading block
                //  of IF statements.
                //
                //  Before the first field is written, the leading space string
                //  must be constructed in strLeadingWhiteSpace, which is
                //  defined at method scope, so that the whole block sees it,
                //  and initialized in the block that handles the first column
                //  (field), using metadata from the first element in an array.
                //
                //  Subsequent elements are treated essentially alike, except
                //  that the last element has an extra format item, which gets a
                //  platform-dependent newline, so that a blank line follows
                //  each record.
                //
                //  This could be simplified by combining the second and third
                //  blocks, since the formatter ignores extra format items.
                //  Likewise, if the three block structure is retained, the
                //  WriteLine call on pswDetailsTable can be moved into the
                //  middle block.
                //  ------------------------------------------------------------

                if ( intJ == ArrayInfo.ARRAY_FIRST_ELEMENT )
                {   // Process the first column.
                    strListTokenZero = string.Format (
                        s_strRecordLabelPrefix ,
                        plngItemNumber );
                    strLeadingWhiteSpace = new string (
                        SpecialCharacters.SPACE_CHAR ,
                        strListTokenZero.IndexOf (
                            SpecialCharacters.COLON )
                            + MagicNumbers.PLUS_TWO );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                }   // TRUE block, if ( intJ == ArrayInfo.ARRAY_FIRST_ELEMENT )
                else if ( intJ == intLastIndex )
                {   // Process the last column.
                    strListTokenZero = strLeadingWhiteSpace;
                    sbTableDetailRow.Append ( SpecialCharacters.TAB_CHAR );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                    pswDetailsTable.WriteLine ( sbTableDetailRow.ToString ( ) );
                }   // TRUE block, else if ( intJ == intLastIndex )
                else
                {   // Process all but the first and last columns.
                    strListTokenZero = strLeadingWhiteSpace;
                    sbTableDetailRow.Append ( SpecialCharacters.TAB_CHAR );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                }   // FALSE block, else if ( intJ == intLastIndex )

                pswDetailsList.WriteLine (
                    LIST_REPORT_FORMAT_CONTROL_STRING ,
                    new object [ ]
                    {
                        strListTokenZero ,                                      // Format Item 0: Label Prefix
                        paColumnInfo[intJ].ColumnLabel ,                        // Format Item 1: Column Label
                        prs.Fields[paColumnInfo[intJ].ColumnName].Value ,       // Format Item 2: Column Value
                        Logic.IsLastForIterationLE ( intJ , intLastIndex )      // Format Item 3: Newline or Nothing
                            ? Environment.NewLine :
                            SpecialStrings.EMPTY_STRING
                    } );
            }   // for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ; intJ <= intLastIndex ; intJ++ )
        }   // private static void ListAllFieldsOnConsole


        /// <summary>
        /// Prompt for a table name when the command line is empty.
        /// </summary>
        /// <returns>
        /// The return value is the string entered at the command line, which
        /// must be the name of a valid table schema.
        /// </returns>
        private static string PromptForTableName ( )
        {
            WizardWrx.ConsoleStreams.ErrorMessagesInColor messagesInColor = null;
            string strErrorPrompt = null;

            string strPrompt = Properties.Resources.MSG_PROMPT_FOR_TABLE_NAME;

            while ( true )
            {
                Console.Error.Write ( strPrompt );
                Console.Beep ( 440 , 500 );
                string strTableNameCandidate = Console.ReadLine ( );

                if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
                {
                    return strTableNameCandidate;
                }   // TRUE (desired outcome) block, if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
                else
                {   // Perform just-in-time object initializations.
                    if ( strErrorPrompt == null )
                    {   // Defer loading until needed.
                        strErrorPrompt = Properties.Resources.ERRMSG_INVALID_NAME;
                    }   // if ( strErrorPrompt == null )

                    if ( messagesInColor == null )
                    {   // Defer creation until needed.
                        messagesInColor = new WizardWrx.ConsoleStreams.ErrorMessagesInColor (
                            ConsoleColor.White ,
                            ConsoleColor.DarkRed );
                    }   // if ( messagesInColor == null )

                    messagesInColor.WriteLine (
                        strErrorPrompt ,                                        // Format control string read from managed resource table
                        strTableNameCandidate.QuoteString ( ) ,                 // Format Item 0: Table name {0}
                        Environment.NewLine );                                  // Format Item 1: {1}Table ... is invalid.{1}
                }   // FALSE (undesired outcome) block, if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
            }   // while ( true )
        }   // private static string PromptForTableName
    }   // class Program
}   // partial amespace PSQLviaADOCS