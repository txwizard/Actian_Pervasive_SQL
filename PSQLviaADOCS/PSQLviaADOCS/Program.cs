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
    Date       By Description
    ---------- -- --------------------------------------------------------------
    2019/07/13 DG Initial implementation.
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
        static ConsoleAppStateManager s_csm = ConsoleAppStateManager.GetTheSingleInstance ( );

        static void Main ( string [ ] args )
        {
            s_csm.DisplayBOJMessage ( );
            s_csm.BaseStateManager.AppExceptionLogger.OptionFlags = s_csm.BaseStateManager.AppExceptionLogger.OptionFlags | WizardWrx.DLLConfigurationManager.ExceptionLogger.OutputOptions.Stack;

            try
            {
                DoTask ( );
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


        private static void DoTask ( )
        {
            const string CONNECTION_STRING = @"Provider=PervasiveOLEDB;Data Source=Demodata";
            const string TABLE_NAME_IS_BILLING = @"Billing";

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
                ColumnNamesAndLabels [ ] aobjColumnNamesAndLabels = CreateNameAndLabelArray ( );
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
                    Properties.Settings.Default.BillingDetailReportFileName ,
                    FileIOFlags.FILE_OUT_CREATE ,
                    Encoding.UTF8 ,
                    MagicNumbers.CAPACITY_08KB );
                swDetailsTable = new StreamWriter (
                    Properties.Settings.Default.BillingDetailTabularReportFileName ,
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
                    Properties.Settings.Default.BillingDetailReportFileName );
                Console.WriteLine (
                    Properties.Resources.MSG_TASK_SUMMARY ,
                    SpecialStrings.EMPTY_STRING ,
                    Properties.Resources.MSG_LABEL_FOR_TABLE ,
                    Properties.Settings.Default.BillingDetailTabularReportFileName );
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


        private static ColumnNamesAndLabels [ ] CreateNameAndLabelArray ( )
        {
            const int COLUMN_INDEX_STUDENT_ID = 0;
            const int COLUMN_INDEX_TRANSACTION_NUMBER = 1;
            const int COLUMN_INDEX_LOG = 2;
            const int COLUMN_INDEX_AMOUNT_OWED = 3;
            const int COLUMN_INDEX_AMOUNT_PAID = 4;
            const int COLUMN_INDEX_REGISTRAR_ID = 5;
            const int COLUMN_INDEX_COMMENTS = 6;

            //  ----------------------------------------------------------------
            //  Beware: When you dimension a Visual Basic array, you specify its
            //          size in terms of its upper bound. However, when you set
            //          the size of a C# array, you specify the maximum number
            //          of elements that it contains.
            //
            //  On reflection, this difference is reasonable because a Visual
            //  Basic array MAY have a nonzero lower bound, whereas a C# array
            //  always has a lower bound of zero, befitting its origin as a
            //  derivative of the C and C++ languages.
            //  ----------------------------------------------------------------

            const int COLUMN_INDEX_ARRAY_SIZE = 7;

            ColumnNamesAndLabels.UniqueColumnName objColName_Student_ID = new ColumnNamesAndLabels.UniqueColumnName ( @"Student_ID" );
            ColumnNamesAndLabels.UniqueColumnName objColName_Transaction_Number = new ColumnNamesAndLabels.UniqueColumnName ( @"Transaction_Number" );
            ColumnNamesAndLabels.UniqueColumnName objColName_Log = new ColumnNamesAndLabels.UniqueColumnName ( @"Log" );
            ColumnNamesAndLabels.UniqueColumnName objColName_Amount_Owed = new ColumnNamesAndLabels.UniqueColumnName ( @"Amount_Owed" );
            ColumnNamesAndLabels.UniqueColumnName objColName_Amount_Paid = new ColumnNamesAndLabels.UniqueColumnName ( @"Amount_Paid" );
            ColumnNamesAndLabels.UniqueColumnName objColName_Registrar_ID = new ColumnNamesAndLabels.UniqueColumnName ( @"Registrar_ID" );
            ColumnNamesAndLabels.UniqueColumnName objColName_Comments = new ColumnNamesAndLabels.UniqueColumnName ( @"Comments" );

            ColumnNamesAndLabels objColumnNamesAndLabels_Student_ID = new ColumnNamesAndLabels (
                objColName_Student_ID ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_STUDENT_ID );
            ColumnNamesAndLabels objColumnNamesAndLabels_Transaction_Number = new ColumnNamesAndLabels (
                objColName_Transaction_Number ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_TRANSACTION_NUMBER );
            ColumnNamesAndLabels objColumnNamesAndLabels_Log = new ColumnNamesAndLabels (
                objColName_Log ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_LOG );
            ColumnNamesAndLabels objColumnNamesAndLabels_Amount_Owed = new ColumnNamesAndLabels (
                objColName_Amount_Owed ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_AMOUNT_OWED );
            ColumnNamesAndLabels objColumnNamesAndLabels_Amount_Paid = new ColumnNamesAndLabels (
                objColName_Amount_Paid ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_AMOUNT_PAID );
            ColumnNamesAndLabels objColumnNamesAndLabels_Registrar_ID = new ColumnNamesAndLabels (
                objColName_Registrar_ID ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_REGISTRAR_ID );
            ColumnNamesAndLabels objColumnNamesAndLabels_Comments = new ColumnNamesAndLabels (
                objColName_Comments ,
                Properties.Resources.MSG_COLUMN_LABEL_STRING_COMMENTS );

            ColumnNamesAndLabels [ ] raobjColumnNamesAndLabels = new ColumnNamesAndLabels [ COLUMN_INDEX_ARRAY_SIZE ];

            raobjColumnNamesAndLabels [ COLUMN_INDEX_STUDENT_ID ] = objColumnNamesAndLabels_Student_ID;
            raobjColumnNamesAndLabels [ COLUMN_INDEX_TRANSACTION_NUMBER ] = objColumnNamesAndLabels_Transaction_Number;
            raobjColumnNamesAndLabels [ COLUMN_INDEX_LOG ] = objColumnNamesAndLabels_Log;
            raobjColumnNamesAndLabels [ COLUMN_INDEX_AMOUNT_OWED ] = objColumnNamesAndLabels_Amount_Owed;
            raobjColumnNamesAndLabels [ COLUMN_INDEX_AMOUNT_PAID ] = objColumnNamesAndLabels_Amount_Paid;
            raobjColumnNamesAndLabels [ COLUMN_INDEX_REGISTRAR_ID ] = objColumnNamesAndLabels_Registrar_ID;
            raobjColumnNamesAndLabels [ COLUMN_INDEX_COMMENTS ] = objColumnNamesAndLabels_Comments;

            return raobjColumnNamesAndLabels;
        }   // private static ColumnNamesAndLabels [ ] CreateNameAndLabelArray


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
            //  ----------------------------------------------------------------
            //  Explicitly initializing this to null resolves a fatal compiler
            //  error. Though the code initializes it before its first use, the
            //  compiler has no way of knowing that it does without some serious
            //  static analysis that probably won't happen until too late in the
            //  compilation process.
            //  ----------------------------------------------------------------

            string strLeadingWhiteSpace = null;

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
            //  is assembled in a StringBuilder, which is written on the way out
            //  of the routine. Meanwhile, a small FOR loop reads the format
            //  control strings, column names, and column labels from the array,
            //  appending a line to the list report print file for each field.
            //  ----------------------------------------------------------------

            StringBuilder sbTableDetailRow = new StringBuilder ( MagicNumbers.CAPACITY_01KB );

            for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                      intJ <= intLastIndex ;
                      intJ++ )
            {   //  ------------------------------------------------------------
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
                    pswDetailsList.WriteLine (
                        paColumnInfo [ intJ ].ColumnLabel ,
                        plngItemNumber ,
                        prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                    strLeadingWhiteSpace = new string (
                        SpecialCharacters.SPACE_CHAR ,
                        paColumnInfo [ intJ ].ColumnLabel.IndexOf (
                            SpecialCharacters.COLON ) + MagicNumbers.PLUS_TWO );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                }   // TRUE block, if ( intJ == ArrayInfo.ARRAY_FIRST_ELEMENT )
                else if ( intJ == intLastIndex )
                {   // Process the last column.
                    pswDetailsList.WriteLine (
                        paColumnInfo [ intJ ].ColumnLabel ,                     // Format Control String
                        strLeadingWhiteSpace ,                                  // {0}Comments
                        prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value , // Comments: {1}
                        Environment.NewLine );                                  // {1}{2}
                    sbTableDetailRow.Append ( SpecialCharacters.TAB_CHAR );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                    pswDetailsTable.WriteLine ( sbTableDetailRow.ToString ( ) );
                }   // TRUE block, else if ( intJ == intLastIndex )
                else
                {   // Process all but the first and last columns.
                    pswDetailsList.WriteLine (
                        paColumnInfo [ intJ ].ColumnLabel ,
                        strLeadingWhiteSpace ,
                        prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value);
                    sbTableDetailRow.Append ( SpecialCharacters.TAB_CHAR );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                }   // FALSE block, else if ( intJ == intLastIndex )
            }   // for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ; intJ <= intLastIndex ; intJ++ )
        }   // private static void ListAllFieldsOnConsole
    }   // class Program
}   // partial amespace PSQLviaADOCS