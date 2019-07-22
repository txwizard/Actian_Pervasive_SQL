/*
    ============================================================================

    Module Name:        ColumnNamesAndLabels.cs

    Assembly Name:      PSQLviaADOCS

    Root Namespace:     PSQLviaADOCS

    Module Name:        Program

    Module Objective:   This application demonstrates basic CRUD operations,
                        which were once also called ACID operations, on a 
                        Pervacive SQL (BTrieve) data base, using the ADODB data
                        provider through COM interop.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------
'
    Date       Version By Description
    ---------- ------- ---------------------------------------------------------
    2019/07/12 1.0.0.0 DG Initial implementation.

    2019/07/14 1.1.0.0 DG Make the implementation much more data driven.

    2019/07/16 1.2.0.0 DG Sanity check the table name when it is read from the
                          command line.

    2019/07/22 1.3.0.0 DG Implement the rest of the CRUD model.
    ============================================================================
*/


using System;

using System.Collections.Generic;                           // Generics live here.
using System.IO;                                            // File and stream I/O routines come from this namespace.
using System.Text;                                          // Text encoders and string builders come from this namespace.

using ADODB;                                                // Use ADODB via COM interop.

using WizardWrx;                                            // Import functions from the Common and Core libraries that live in the root namespace.
using WizardWrx.ConsoleAppAids3;                            // This subsidiary namespace includes a handful of closely related specialized classes.
using WizardWrx.FormatStringEngine;                         // Import functions to generate capacity-aware format items at run time.


namespace PSQLviaADOCS
{
    /// <summary>
    /// By convention, the Program class defines Main, the entry point routine
    /// of all console mode applications implemented in C#.
    /// </summary>
    class Program
    {
        #region Module Constants, Enumerations, and Structures
        /// <summary>
        /// The status code returned for an invalid verb is one greater than the
        /// value returned for a garden variety runtime exception.
        /// </summary>
        const int ERROR_BAD_VERB = MagicNumbers.ERROR_RUNTIME + ArrayInfo.NEXT_INDEX;

        const int BEEP_DURATION = 500;
        const int BEEP_FREQUENCY = 440;

        /// <summary>
        /// The verb fed into the command line must map to one of these values.
        /// </summary>
        enum CrudVerb
        {
            /// <summary>
            /// List is the default value.
            /// <para>
            /// This helper routine has no equivalent in the ACID and CRUD
            /// design patterns.
            /// </para>
            /// </summary>
            List,

            /// <summary>
            /// Create is equivalent to Add in the old ACID model.
            /// </summary>
            Create,

            /// <summary>
            /// Read is equivalent to Inquire in the old ACID model.
            /// </summary>
            Read,

            /// <summary>
            /// Update is equivalent to Change in the old ACID model.
            /// </summary>
            Update,

            /// <summary>
            /// Delete is the same in both the old ACID model and the new CRUD
            /// model.
            /// </summary>
            Delete ,

            /// <summary>
            /// List the properties of the specified table.
            /// <para>
            /// This helper routine has no equivalent in the ACID and CRUD
            /// design patterns.
            /// </para>
            /// </summary>
            TableProperties
        }   // enum CrudVerb


        /// <summary>
        /// OutputFileType is used internally to give directions to private
        /// method AssembleReportFileName, the routine that assembles a file
        /// name from various configuration settings.
        /// </summary>
        enum OutputFileType
        {
            /// <summary>
            /// Instruct AssembleReportFileName to construct the name for the
            /// list report covering all rows in a table.
            /// </summary>
            DetailListReport,

            /// <summary>
            /// Instruct AssembleReportFileName to construct the name for the
            /// tabular report covering all rows in a table.
            /// </summary>
            DetailTabularReport ,

            /// <summary>
            /// Instruct AssembleReportFileName to construct the name for the
            /// tabular report covering the properties of all columns in a
            /// table.
            /// </summary>
            TablePropertiesReport
        }   // enum OutputFileType


        /// <summary>
        /// Organizing the operating parameters into a small structure enables a
        /// method to return all settings.
        /// </summary>
        struct OperatingParameters
        {
            /// <summary>
            /// String representation of the name of the database table to process
            /// </summary>
            public string TableName;

            /// <summary>
            /// Enumeration representation of the operation to perform on the table
            /// </summary>
            public CrudVerb Verb;
        }   // struct OperatingParameters
        #endregion  // Module Constants, Enumerations, and Structures


        #region Module Static Members
        static ConsoleAppStateManager s_csm = ConsoleAppStateManager.GetTheSingleInstance ( );

        //  --------------------------------------------------------------------
        //  Method ListAllFieldsOnConsole, which is called in a While loop, uses
        //  these variables, all of which acquire values during the first pass
        //  that never change thereafter. Combining these statics with null-
        //  coalescing operators enables these values to be reused on subsequent
        //  iterations, saving a good deal of complex data manipulation.
        //  --------------------------------------------------------------------

        static string s_strFinalRecordLabelPrefix = null;
        static string s_strLeadingWhiteSpace = null;
        static string s_strDynamicListReportFormatString = null;
        static string s_strDispMsgNRecs = null;
        static int? s_intLastIndex;
        #endregion  // Module Static Members


        #region Module Main Routines
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
                    //s_csm.ErrorExit ( ( uint ) Environment.ExitCode );                            // This line assumes that BaseStateManager updated Environment.ExitCode, which it did not.
                    s_csm.ErrorExit ( ( uint ) s_csm.BaseStateManager.AppReturnCode );              // ErrorExit expects a uint, while both AppReturnCode and Environment.ExitCode are signed.
                }   // FALSE (unanticipated outcome) block, if ( Environment.ExitCode == MagicNumbers.ERROR_SUCCESS )
            }   // Try/Catch/Finally block
        }   // static void Main


        /// <summary>
        /// Perform the task for which the program was designed.
        /// </summary>
        /// <param name="pastrArgs">
        /// Feed in the argument list that was passed into the command line.
        /// </param>
        /// <returns>
        /// If the routine succeeds, its return value is TRUE. Otherwise, the
        /// return value is FALSE, signaling the calling routine to behave
        /// accordingly.
        /// </returns>
        private static void DoTask ( string [ ] pastrArgs )
        {
            StreamWriter swDetailsList = null;
            StreamWriter swDetailsTable = null;
            FixedConsoleWriter fcwProgress = null;

            OperatingParameters operatingParameters;

            Connection cn = null;
            Recordset rs = null;

            //  ----------------------------------------------------------------
            //  Pretty much anything that can throw exceptions is inside this
            //  Try/Catch/Finally block. Defining constants and initialized
            //  integers cannot throw; neither should declaring an uninitialized
            //  StreamWriter, Connection, Recordset, or FixedConsoleWriter. 
            //  Everything above this comment needs method scope so that it is
            //  visible to the Finally block.
            //  ----------------------------------------------------------------

            try
            {
                operatingParameters = GetOperatingParamerters ( pastrArgs );

                switch ( operatingParameters.Verb )
                {
                    case CrudVerb.List:
                        ListAllRowsInTable (
                            out swDetailsList ,
                            out swDetailsTable ,
                            out fcwProgress ,
                            out cn ,
                            out rs ,
                            operatingParameters.TableName );
                        return;

                    case CrudVerb.TableProperties:
                        ListTableColumnProperties (
                            out swDetailsTable ,
                            out fcwProgress ,
                            out cn ,
                            out rs ,
                            operatingParameters.TableName );
                        return;

                    case CrudVerb.Create:
                        AddNewRows (
                            out cn ,
                            out rs ,
                            operatingParameters.TableName );
                        return;
                    case CrudVerb.Update:
                        UpdateRows (
                            out cn ,
                            out rs ,
                            operatingParameters.TableName );
                        return;
                    case CrudVerb.Delete:
                        DeleteRows (
                            out cn ,
                            out rs ,
                            operatingParameters.TableName );
                        return;
                    case CrudVerb.Read:
                        ReadSomeRows (
                            out cn ,
                            out rs ,
                            operatingParameters.TableName );
                        return;
                    default:
                        throw new System.ComponentModel.InvalidEnumArgumentException (
                            nameof ( operatingParameters.Verb ) ,
                            ( int ) operatingParameters.Verb ,
                            operatingParameters.Verb.GetType ( ) );
                }   // switch ( operatingParameters.Verb )
            }
            catch ( Exception ex )
            {
                if ( fcwProgress != null )
                {   // Skip the ScrollUp call when fcwProgress is unitialized (null).
                    fcwProgress.ScrollUp ( );
                }   // if ( fcwProgress != null )

                s_csm.BaseStateManager.AppExceptionLogger.ReportException ( ex );
                s_csm.BaseStateManager.AppReturnCode = MagicNumbers.ERROR_RUNTIME;
            }
            finally
            {
                if ( s_csm.BaseStateManager.AppReturnCode != ERROR_BAD_VERB )
                {
                    rs.Close ( );
                    cn.Close ( );

                    CloseStreamWriterSafely ( swDetailsList );
                    CloseStreamWriterSafely ( swDetailsTable );
                }   // if ( s_csm.BaseStateManager.AppReturnCode != ERROR_BAD_VERB )
            }
        }   // private static void DoTask


        /// <summary>
        /// Add one or more rows to the table.
        /// </summary>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static void AddNewRows (
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            Console.WriteLine (
                Properties.Resources.MSG_PROMPT_FOR_NEW_VALUES ,                // Format control string
                Environment.NewLine );                                          // Format Item 0: prompts.{0}

            //  ----------------------------------------------------------------
            //  In addition to opening the connection and the recordset, static
            //  method OpenTableRecordset creates and initializes the array of
            //  ColumnNamesAndLabels objects. Since every iteration of a classic
            //  FOR loop tests it and two arrays of strings, each of which must
            //  be the same size, are dimensioned accordingly, the length of the
            //  array goes into an integer, intColumnCount.
            //  ----------------------------------------------------------------

            ColumnNamesAndLabels [ ] acolNamesAndLabels = OpenTableRecordset (
                out pdbConnection ,
                out pdbRecordSet ,
                pstrTableName );

            int intColumnCount = acolNamesAndLabels.Length;
            bool fRingTheBell = true;

            string [ ] astrNameList = new string [ intColumnCount ];
            object [ ] astrValueList = new object [ intColumnCount ];

            for ( int intCurrentColumn = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                      intCurrentColumn < intColumnCount ;
                      intCurrentColumn++ )
            {
                if ( acolNamesAndLabels [ intCurrentColumn ].ColumnValue == null )
                {
                    Console.Write (
                        Properties.Resources.MSG_PROMPT_FOR_FIELD_VALUE ,       // Format control string
                        ArrayInfo.OrdinalFromIndex ( intCurrentColumn ) ,       // Format Item 0: {0}: Enter value
                        acolNamesAndLabels [ intCurrentColumn ].ColumnLabel );  // Format Item 1: for field {1}:

                    if ( fRingTheBell )
                    {   // One beep only.
                        Console.Beep (
                            BEEP_FREQUENCY ,
                            BEEP_DURATION );
                        fRingTheBell = false;
                    }   // if ( fRingTheBell )

                    acolNamesAndLabels [ intCurrentColumn ].ColumnValue = EvaluateField (
                        Console.ReadLine ( ) ,                                                          // string pstrFieldValue
                        pdbRecordSet.Fields [ acolNamesAndLabels [ intCurrentColumn ].ColumnName ] );   // Field  pdbField
                }    // TRUE (The user must supply a value.) block, if ( acolNamesAndLabels [ intCurrentColumn ].ColumnValue == null )
                else
                {
                    Console.WriteLine (
                        Properties.Resources.MSG_INFO_ASSIGNED_COLUMN_VALUE ,   // Format control string
                        ArrayInfo.OrdinalFromIndex ( intCurrentColumn ) ,       // Format Item 0: {0}: 
                        acolNamesAndLabels [ intCurrentColumn ].ColumnLabel ,   // Format Item 1: : {1} value assigned
                        acolNamesAndLabels [ intCurrentColumn ].ColumnValue );  // Format Item 2: by system = {2}
                }   // FALSE (The program generates a value.) block, if ( acolNamesAndLabels [ intCurrentColumn ].ColumnValue == null )

                astrNameList [ intCurrentColumn ] = acolNamesAndLabels [ intCurrentColumn ].ColumnName;
                astrValueList [ intCurrentColumn ] = acolNamesAndLabels [ intCurrentColumn ].ColumnValue;
            }   // for ( int intCurrentColumn = ArrayInfo.ARRAY_FIRST_ELEMENT ; ; intCurrentColumn < intColumnCount ; intCurrentColumn++ )

            pdbRecordSet.AddNew (
                astrNameList ,
                astrValueList );
            pdbRecordSet.Update ( );
        }   // private static void AddNewRows


        /// <summary>
        /// Evaluate the input field, providing translation and other services
        /// as needed.
        /// </summary>
        /// <param name="pstrFieldValue">
        /// Pass in the string representation of the proposed value to assign to
        /// the column (field). Data from the <paramref name="pdbField"/>
        /// determines the rules that govern editing of it.
        /// </param>
        /// <param name="pdbField">
        /// Pass in a reference to the ADODB.Field object that corresponds to
        /// the value supplied in <paramref name="pstrFieldValue"/>.
        /// </param>
        /// <returns></returns>
        private static object EvaluateField (
            string pstrFieldValue ,
            Field pdbField )
        {
            return ADOHelpers.ParseAndConvert (
                pstrFieldValue ,                                                // string pstrInputValue
                pdbField ,                                                      // Field pDBField
                Properties.Settings.Default.BooleanTrueList.Split (             // string [ ] pastrTrueStrings = null
                    SpecialCharacters.SEMICOLON ) ,
                Properties.Settings.Default.BooleanFalseList.Split (            // string [ ] pastrFalseStrings = null
                    SpecialCharacters.SEMICOLON ) ,
                true );                                                         // bool pfThrowWhenInvalid = false
        }   // private static object EvaluateField


        /// <summary>
        /// Delete rows that meet specified criteria.
        /// </summary>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// </param>
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static void DeleteRows (
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            throw new NotImplementedException ( );
        }   // private static void DeleteRows


        /// <summary>
        /// List all columns of all rows in the table named in <paramref name="pswDetailsTable"/>
        /// </summary>
        /// <param name="pswDetailsList">
        /// Pass in a reference to a StreamWriter object that receives the
        /// vertically aligned list report, which is initially null.
        /// <para>
        /// Since the absolute name of the output file is derived internally by
        /// calling a method that assembles it from the table name and a couple
        /// of application-scoped settings, the Streamwriter is passed in as a
        /// null reference. This method initializes it, and returns the open
        /// StreamWriter for further processing, closure, and disposition by the
        /// calling routine. Though it could have been kept entirely internal,
        /// doing so would have prevented using a Finally block to clean it up,
        /// since the calling routine takes responsibility for handling most of
        /// the exceptions that may arise during execution.
        /// </para>
        /// </param>
        /// <param name="pswDetailsTable">
        /// Pass in a reference to a StreamWriter object that receives the
        /// tab delimited list report, which is initially null.
        /// <para>
        /// Since the absolute name of the output file is derived internally by
        /// calling a method that assembles it from the table name and a couple
        /// of application-scoped settings, the Streamwriter is passed in as a
        /// null reference. This method initializes it, and returns the open
        /// StreamWriter for further processing, closure, and disposition by the
        /// calling routine. Though it could have been kept entirely internal,
        /// doing so would have prevented using a Finally block to clean it up,
        /// since the calling routine takes responsibility for handling most of
        /// the exceptions that may arise during execution.
        /// </para>
        /// </param>
        /// <param name="pfcwProgress">
        /// Pass in a reference to a FixedConsoleWriter that is used to report
        /// progress during execution, which is initially null.
        /// </param>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static void ListAllRowsInTable (
            out StreamWriter pswDetailsList ,
            out StreamWriter pswDetailsTable ,
            out FixedConsoleWriter pfcwProgress ,
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            long lngItemNumber = ListInfo.LIST_IS_EMPTY;
            string strDetailListReportFQFN = AssembleReportFileName (
                    OutputFileType.DetailListReport ,
                    pstrTableName );
            string strDetailTabularReportFQFN = AssembleReportFileName (
                    OutputFileType.DetailTabularReport ,
                    pstrTableName );
            pfcwProgress = new FixedConsoleWriter (
                ConsoleColor.Yellow ,
                ConsoleColor.Black );
            ColumnNamesAndLabels [ ] aobjColumnNamesAndLabels = OpenTableRecordset (
                out pdbConnection ,
                out pdbRecordSet ,
                pstrTableName );
            pswDetailsList = new StreamWriter (
                strDetailListReportFQFN ,
                FileIOFlags.FILE_OUT_CREATE ,
                Encoding.UTF8 ,
                MagicNumbers.CAPACITY_08KB );
            pswDetailsTable = new StreamWriter (
                strDetailTabularReportFQFN ,
                FileIOFlags.FILE_OUT_CREATE ,
                Encoding.UTF8 ,
                MagicNumbers.CAPACITY_08KB );
            pdbRecordSet.MoveFirst ( );

            while ( !pdbRecordSet.EOF )
            {
                ListAllFieldsOnConsole (
                    pdbRecordSet ,
                    aobjColumnNamesAndLabels ,
                    MoreMath.IncrementAndReturnNewValue ( ref lngItemNumber ) ,
                    pswDetailsList ,
                    pswDetailsTable ,
                    pfcwProgress );
                pdbRecordSet.MoveNext ( );
            }   // while ( !rs.EOF )

            pswDetailsList.WriteLine (
                Properties.Resources.REPORT_FOOTER ,
                lngItemNumber );

            //  ------------------------------------------------------------
            //  Without ScrollUp, the next line written by Console.WriteLine
            //  is appended to the last line written by FixedConsoleWriter
            //  object fcwProgress.
            //  ------------------------------------------------------------

            pfcwProgress.ScrollUp ( );
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
        }   // private static void ListAllRowsInTable


        /// <summary>
        /// Generate a list of the properties of all columns in a table. Since
        /// the list is generated from the properties that are visible to the
        /// ADO Recordset object, the list is incomplete, because it omits the
        /// IsNullable column property and any column constraints defined on the
        /// table. Nevertheless, the list affords useful options for data driven
        /// column editing.
        /// </summary>
        /// <param name="pswDetailsTable">
        /// Pass in a reference to a StreamWriter object that receives the
        /// tab delimited list report, which is initially null.
        /// <para>
        /// Since the absolute name of the output file is derived internally by
        /// calling a method that assembles it from the table name and a couple
        /// of application-scoped settings, the Streamwriter is passed in as a
        /// null reference. This method initializes it, and returns the open
        /// StreamWriter for further processing, closure, and disposition by the
        /// calling routine. Though it could have been kept entirely internal,
        /// doing so would have prevented using a Finally block to clean it up,
        /// since the calling routine takes responsibility for handling most of
        /// the exceptions that may arise during execution.
        /// </para>
        /// </param>
        /// <param name="pfcwProgress">
        /// Pass in a reference to a FixedConsoleWriter that is used to report
        /// progress during execution, which is initially null.
        /// </param>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static void ListTableColumnProperties (
            out StreamWriter pswDetailsTable ,
            out FixedConsoleWriter pfcwProgress ,
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            string strDetailTabularReportFQFN = AssembleReportFileName (
                    OutputFileType.TablePropertiesReport ,
                    pstrTableName );
            pfcwProgress = new FixedConsoleWriter (
                ConsoleColor.Yellow ,
                ConsoleColor.Black );
            ColumnNamesAndLabels [ ] aobjColumnNamesAndLabels = OpenTableRecordset (
                out pdbConnection ,
                out pdbRecordSet ,
                pstrTableName );
            pswDetailsTable = new StreamWriter (
                strDetailTabularReportFQFN ,
                FileIOFlags.FILE_OUT_CREATE ,
                Encoding.UTF8 ,
                MagicNumbers.CAPACITY_08KB );

            for ( int intColumnIndex = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                      intColumnIndex < aobjColumnNamesAndLabels.Length ;
                      intColumnIndex++ )
            {
                ListPropertiesOfColumn (
                    pdbRecordSet ,
                    aobjColumnNamesAndLabels ,
                    intColumnIndex ,
                    pswDetailsTable ,
                    pfcwProgress );
            }   // for ( int intColumnIndex = ArrayInfo.ARRAY_FIRST_ELEMENT ; intColumnIndex < aobjColumnNamesAndLabels.Length ; intColumnIndex++ )

            pfcwProgress.ScrollUp ( );

            Console.WriteLine (
                Properties.Resources.MSG_TASK_SUMMARY ,
                Environment.NewLine ,
                Properties.Resources.MSG_LABEL_FOR_PROPERTIES_LIST ,
                strDetailTabularReportFQFN );
        }  // private static void ListTableColumnProperties


        /// <summary>
        /// Read rows that meet specified criteria.
        /// </summary>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static void ReadSomeRows (
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            throw new NotImplementedException ( );
        }   // private static void ReadSomeRows


        /// <summary>
        /// Update selected rows.
        /// </summary>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static void UpdateRows (
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            throw new NotImplementedException ( );
        }   // private static void UpdateRows
        #endregion  // Module Main Routines


        #region Module Subroutines
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
                case OutputFileType.TablePropertiesReport:
                    strReportFileNameTemplate = Properties.Settings.Default.TableColumnPropertiesFileNameTemplate;
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


        /// <summary>
        /// The ColumnNamesAndLabels constructor registers this routine as the
        /// ColumnValueSetter delegate to call as needed to assign the next ID
        /// column value.
        /// </summary>
        /// <param name="pdbConnection">
        /// Pass in a reference to the open ADODB.Connection through which to access
        /// the database.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="paobjInputs">
        /// Pass in am optional array of object variables from which to derive the
        /// return value. If there are none, the array may be null or empty.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <returns>
        /// The return value is an objectified representation of the value to assign
        /// to the column.
        /// </returns>
        private static object AssignNextID (
            Connection pdbConnection ,
            object [ ] paobjInputs )
        {
            const string SQL = "SELECT MAX(ID) FROM \"Person\"";

            Recordset rs = new Recordset ( );
            rs.Open (
                SQL ,                                                           // Table or query name
                pdbConnection ,                                                 // Connection object, which must be open
                CursorTypeEnum.adOpenForwardOnly ,                              // Cursor type: See "ADO CursorType Property" at https://www.w3schools.com/asp/prop_rs_cursortype.asp
                LockTypeEnum.adLockOptimistic ,                                 // Locking scheme
                ( int ) CommandTypeEnum.adCmdText );                            // Flags: CommandTypeEnum specifies adCmdText, which corresponds to a SQL query.
            rs.MoveFirst ( );

            if ( long.TryParse ( rs.Fields [ ArrayInfo.ARRAY_FIRST_ELEMENT ].Value.ToString ( ) , out long lngNextId ) )
            {
                return lngNextId + MagicNumbers.PLUS_ONE;
            }   // TRUE (anticipated outcome) block, if ( long.TryParse ( rs.Fields [ ArrayInfo.ARRAY_FIRST_ELEMENT ].Value.ToString ( ) , out long lngNextId ) )
            else
            {
                throw new InvalidOperationException (
                    string.Format (
                        Properties.Resources.ERRMSG_INTERNAL_SQL_ERROR ,                                                // Format control string
                        SQL ,                                                                                           // Format Item 0: returned by SQL query {0}
                        rs.Fields [ ArrayInfo.ARRAY_FIRST_ELEMENT ].Value.ToString ( ).QuoteString ( ) ) );             // Format Item 1: is {1}, which
            }   // FALSE (unanticipated outcome) block, if ( long.TryParse ( rs.Fields [ ArrayInfo.ARRAY_FIRST_ELEMENT ].Value.ToString ( ) , out long lngNextId ) )
        }   // private static object AssignNextID


        /// <summary>
        /// Close and dispose a StreamWriter safely under all conditions.
        /// </summary>
        /// <param name="psw">
        /// Pass in a reference to the StreamWriter to be safely closed and
        /// disposed.
        /// </param>
        private static void CloseStreamWriterSafely ( StreamWriter psw )
        {
            if ( psw != null )
            {   // When a StreamWriter exists, but its BaseStream property is null, the stream is already closed.
                if ( psw.BaseStream != null )
                {   // If the CanWrite property of the BaseStream is TRUE, the stream remains open. This sanity check is probably redundant.
                    if ( psw.BaseStream.CanWrite )
                    {   // The StreamWriter is open, as should be the case, since we dispensed with a Using block.
                        psw.Close ( );
                    }   // if ( swDetailsList.BaseStream.CanWrite )
                }   // if ( swDetailsList.BaseStream != null )

                psw.Dispose ( );                                      // Unless the stream reference is null, it must always be disposed.
            }   // if ( swDetailsList != null )
        }   // private static void CloseStreamWriter


        /// <summary>
        /// Sibling method OpenTableRecordset calls this routine to create and
        /// populate the array of ColumnNamesAndLabels objects.
        /// </summary>
        /// <param name="pstrTableName">
        /// Pass in the string that contains the unqualified name of the table,
        /// from which the abssolute (fully qualifed) name of the file that has
        /// the list of names and properties, is derived.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <param name="pdbConnection">
        /// Pass in a reference to the data base connection object, which is
        /// fed to the constructor of the first element in the array along with
        /// AssignNextID, the name of the sibling routine to establish as the
        /// callback routine that the constructor will use when invoked to set
        /// the column value.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <returns>
        /// The return value is an array of ColumnNamesAndLabels, in the order
        /// of the lines in the input file that defines the column names and
        /// labels of the table specified by <paramref name="pstrTableName"/>.
        /// </returns>
        private static ColumnNamesAndLabels [ ] CreateNameAndLabelArray ( 
            string pstrTableName , 
            Connection pdbConnection )
        {
            const int POS_COLUMN_NAME = ArrayInfo.ARRAY_FIRST_ELEMENT;
            const int POS_COLUMN_LABEL = POS_COLUMN_NAME + ArrayInfo.NEXT_INDEX;
            const int EXPECTED_COLUMN_COUNT = POS_COLUMN_LABEL + ArrayInfo.NEXT_INDEX;

            string strTableSchemaFQFN = DeriveTableSchemaFQFN ( pstrTableName );
            string [ ] astrSchemaLines = File.ReadAllLines ( strTableSchemaFQFN );
            int intLineCount = astrSchemaLines.Length;
            ColumnNamesAndLabels [ ] raColumnNamesAndLabels = new ColumnNamesAndLabels [ ArrayInfo.IndexFromOrdinal ( intLineCount ) ];

            for ( int intLineNumber = CSVFileInfo.FIRST_RECORD ;
                      intLineNumber < intLineCount ;
                      intLineNumber++ )
            {
                string [ ] astrColumnMetaData = astrSchemaLines [ intLineNumber ].Split ( SpecialCharacters.TAB_CHAR );

                if ( astrColumnMetaData.Length == EXPECTED_COLUMN_COUNT )
                {
                    if ( intLineNumber == CSVFileInfo.FIRST_RECORD )
                    {
                        raColumnNamesAndLabels [ ArrayInfo.IndexFromOrdinal ( intLineNumber ) ] = new ColumnNamesAndLabels (
                            new ColumnNamesAndLabels.UniqueColumnName (
                                astrColumnMetaData [ POS_COLUMN_NAME ] ,
                                pstrTableName ) ,
                            astrColumnMetaData [ POS_COLUMN_LABEL ] ,
                            AssignNextID ,
                            null ,
                            pdbConnection );
                    }   // TRUE (special case) block, if ( intLineNumber == CSVFileInfo.FIRST_RECORD )
                    else
                    {
                        raColumnNamesAndLabels [ ArrayInfo.IndexFromOrdinal ( intLineNumber ) ] = new ColumnNamesAndLabels (
                            new ColumnNamesAndLabels.UniqueColumnName (
                                astrColumnMetaData [ POS_COLUMN_NAME ] ,
                                pstrTableName ) ,
                            astrColumnMetaData [ POS_COLUMN_LABEL ] );
                    }   // FALSE (regular case) block, if ( intLineNumber == CSVFileInfo.FIRST_RECORD )
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
            }   // for ( int intLineNumber = CSVFileInfo.FIRST_RECORD ; intLineNumber < intLineCount ; intLineNumber++ )

            return raColumnNamesAndLabels;
        }   // private static ColumnNamesAndLabels [ ] CreateNameAndLabelArray


        /// <summary>
        /// Derive the absolute (fully qualified) name of the file that contains
        /// the table schema metadata to process.
        /// </summary>
        /// <param name="pstrTableName">
        /// Pass in a string containing the name of the table, from which to
        /// derive the absolute name of the file that contains its schema data.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
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


        private static CrudVerb EvaluateCrudVerb ( string pstrVerb )
        {
            try
            {
                return pstrVerb.EnumFromString<CrudVerb> ( );
            }
            catch ( InvalidOperationException exInvOper )
            {
                string strExpectedMessageText = Properties.Resources.ERRMSG_PREFIX_INVALID_VERB;
                int intExpectedMessageStartPos = exInvOper.Message.IndexOf ( strExpectedMessageText );

                if ( intExpectedMessageStartPos > ListInfo.INDEXOF_NOT_FOUND )
                {   // The exception message contains the expected phrase, preceded by the verb. Report it and consume the exception.
                    s_csm.BaseStateManager.AppReturnCode = ERROR_BAD_VERB;

                    WizardWrx.ConsoleStreams.ErrorMessagesInColor messagesInColor = new WizardWrx.ConsoleStreams.ErrorMessagesInColor (
                        s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageForegroundColor ,
                        s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageBackgroundColor );
                    messagesInColor.WriteLine (
                        exInvOper.Message.Substring (
                            ListInfo.SUBSTR_BEGINNING ,                         // Start at beginning of string
                            intExpectedMessageStartPos                          // Take characters to position of phrase
                            + strExpectedMessageText.Length ) );                //      plus its length.
                }   // TRUE (anticipated outcome) block, if ( intExpectedMessageStartPos > ListInfo.INDEXOF_NOT_FOUND )
                else
                {   // The exception message text is unexpected. Pass it up the call stack for reporting and program abort.
                    throw exInvOper;
                }   // FALSE (unanticipated outcome) block, if ( intExpectedMessageStartPos > ListInfo.INDEXOF_NOT_FOUND )
            }   // Try/Catch block

            return CrudVerb.List;
        }   // private static CrudVerb EvaluateCrudVerb


        /// <summary>
        /// Construct a list of column labels from an array of
        /// ColumnNamesAndLabels objects.
        /// </summary>
        /// <param name="paColumnInfo">
        /// Pass in a reference to the ColumnNamesAndLabels from which labels
        /// are needed.
        /// </param>
        /// <returns>
        /// The return value is a list containing the labels found in the
        /// <paramref name="paColumnInfo"/> array. The list is unsorted, since
        /// it is used only to compute the length of the longest string in it,
        /// after which the list is discarded.
        /// </returns>
        private static List<string> GetAllColumnLabels ( ColumnNamesAndLabels [ ] paColumnInfo )
        {
            int intColumnCount = paColumnInfo.Length;
            List<string> rlstOfLabels = new List<string> ( intColumnCount );

            for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                      intJ < intColumnCount ;
                      intJ++ )
            {
                rlstOfLabels.Add ( paColumnInfo [ intJ ].ColumnLabel );
            }   // for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ; intJ < intColumnCount ; intJ++ )

            return rlstOfLabels;
        }   // private static List<string> GetAllColumnLabels


        /// <summary>
        /// Prompt for a table name when the command line is empty.
        /// </summary>
        /// <returns>
        /// The return value is the operating parameters obtained from either
        /// the command line or console inputs.
        /// </returns>
        private static OperatingParameters GetOperatingParamerters ( string [ ] pastrArgs )
        {
            const int ARG_COUNT_NONE = ListInfo.LIST_IS_EMPTY;
            const int ARG_COUNT_TABLE_NAME = ArrayInfo.ARRAY_FIRST_ELEMENT + ArrayInfo.ORDINAL_FROM_INDEX;
            const int ARG_COUNT_CRUD_VERB= ARG_COUNT_TABLE_NAME + ArrayInfo.ORDINAL_FROM_INDEX;

            const int ARG_TABLE_NAME = ArrayInfo.ARRAY_FIRST_ELEMENT;
            const int ARG_CRUD_VERB = ARG_TABLE_NAME + ArrayInfo.NEXT_INDEX;

            string strErrorPrompt = null;
            string strPrompt = null;
            string strTableNameCandidate = null;
            string strVerbCandidate = null;
            WizardWrx.ConsoleStreams.ErrorMessagesInColor messagesInColor = null;

            OperatingParameters rparameters = new OperatingParameters ( );

            switch ( pastrArgs.Length )
            {
                case ARG_COUNT_NONE:
                    break;
                case ARG_COUNT_TABLE_NAME:
                    strTableNameCandidate = pastrArgs [ ARG_TABLE_NAME ];
                    break;
                case ARG_COUNT_CRUD_VERB:
                    strTableNameCandidate = pastrArgs [ ARG_TABLE_NAME ];
                    strVerbCandidate = pastrArgs [ ARG_CRUD_VERB ];
                    break;
                default:
                    strTableNameCandidate = pastrArgs [ ARG_TABLE_NAME ];
                    strVerbCandidate = pastrArgs [ ARG_CRUD_VERB ];
                    break;
            }   // switch ( pastrArgs.Length )

            if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
            {
                rparameters.TableName = strTableNameCandidate;
            }
            else
            {
                messagesInColor = new WizardWrx.ConsoleStreams.ErrorMessagesInColor (
                    s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageForegroundColor ,
                    s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageBackgroundColor );

                if ( strErrorPrompt == null )
                {   // Defer loading until needed.
                    strErrorPrompt = Properties.Resources.ERRMSG_INVALID_NAME;
                }   // if ( strErrorPrompt == null )

                messagesInColor.WriteLine (
                    strErrorPrompt ,                                        // Format control string read from managed resource table
                    strTableNameCandidate.QuoteString ( ) ,                 // Format Item 0: Table name {0}
                    Environment.NewLine );                                  // Format Item 1: {1}Table ... is invalid.{1}
            }   // if ( messagesInColor == null )

            while ( rparameters.TableName == null )
            {
                strPrompt = strPrompt ?? Properties.Resources.MSG_PROMPT_FOR_TABLE_NAME;
                Console.Error.Write ( strPrompt );
                Console.Beep (
                    BEEP_FREQUENCY ,
                    BEEP_DURATION );
                strTableNameCandidate = Console.ReadLine ( );

                if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
                {
                    rparameters.TableName = strTableNameCandidate;
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
                            s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageForegroundColor ,
                            s_csm.BaseStateManager.AppExceptionLogger.ErrorMessageColors.MessageBackgroundColor );
                    }   // if ( messagesInColor == null )

                    messagesInColor.WriteLine (
                        strErrorPrompt ,                                        // Format control string read from managed resource table
                        strTableNameCandidate.QuoteString ( ) ,                 // Format Item 0: Table name {0}
                        Environment.NewLine );                                  // Format Item 1: {1}Table ... is invalid.{1}
                }   // FALSE (undesired outcome) block, if ( File.Exists ( DeriveTableSchemaFQFN ( strTableNameCandidate ) ) )
            }   // while ( true )

            if ( pastrArgs.Length > ARG_CRUD_VERB )
            {
                rparameters.Verb = EvaluateCrudVerb ( pastrArgs [ ARG_CRUD_VERB ] );

                if ( s_csm.BaseStateManager.AppReturnCode == ERROR_BAD_VERB )
                {
                    return rparameters;
                }   // if ( s_csm.BaseStateManager.AppReturnCode == ERROR_BAD_VERB )
            }   // TRUE (The verb is in the command tail.) block, if ( pastrArgs.Length > CRUD_VERB )
            else
            {   // ToDo: Add code to prompt for verb.
            }   // FALSE (The command tail omits a verb.) block, if ( pastrArgs.Length > CRUD_VERB )

            Console.WriteLine (
                Properties.Resources.MSG_DISPLAY_TABLE_NAME_AND_VERB ,          // Format control string read from managed resource table
                rparameters.TableName ,                                         // Format Item 0: Processing PSQL database table {0}
                rparameters.Verb ,                                              // Format Item 1: Action Taken = {1}
                Environment.NewLine );                                          // Format Item 1: Platform depdent newline database table {0}{2} AND Action Taken = {1}{2}

            return rparameters;
        }   // private static string GetOperatingParamerters


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
        /// returned by MoreMath.IncrementAndReturnNewValue works well, as this
        /// single step also increments the item number. This value is safe to
        /// pass by value.
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

            string strListTokenZero = null;

            //  ----------------------------------------------------------------
            //  The null-coalescing operator in the following statement causes 
            //  s_strDynamicListReportFormatString to be initialized on first
            //  use, and avoids wasting the effort, which would yield identical
            //  results, on subsequent loop iterations.
            //  ----------------------------------------------------------------

            s_strDynamicListReportFormatString = s_strDynamicListReportFormatString ?? FormatItem.UpgradeFormatItem (
                LIST_REPORT_FORMAT_CONTROL_STRING ,                             // System.String        pstrFormat          Specify a valid format string to upgrade. The string must contain a token of the form {n}, where n is equal to pintItemIndex.
                ArrayInfo.ARRAY_SECOND_ELEMENT ,                                // System.Int32         pintItemIndex       Specify the index of the item to be upgraded. The integer must be positive, and pstrFormat must contain at least once instance of a correspondingly numbered format item.
                FormatItem.Alignment.Left ,                                     // FormatItem.Alignment penmAlignment       Specify Left or Right.Center alignment is unsupported , although it could be achieved with custom code.
                SpecialStrings.EMPTY_STRING ,                                   // System.String        pstrFormatString    Specify a standard or custom Numeric or DateTime format string.Contrast this with pstrUpgrade , which expects you to supply the entire format item , ready for substitution.
                GetAllColumnLabels ( paColumnInfo ) );                          // List<System.String>  pastrValueArray     Specify an array of strings, all of which are values intended to be formatted by the upgraded format item. This routine determines the length of the longest string, which becomes the basis of the alignment parameter inserted into the upgraded format item.

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

            s_intLastIndex = s_intLastIndex ?? ArrayInfo.IndexFromOrdinal ( paColumnInfo.Length );
            s_strDispMsgNRecs = s_strDispMsgNRecs ?? prs.RecordCount.ToString ( // An open ADO recordset bound to a table reports its record count.
                DisplayFormats.NUMBER_PER_REG_SETTINGS_0D );                    // Format the integer with thousands separators per the Regional Settings in the Windows Control Panel.
            pfcwProgress.Write (                                                // Update the status shown on the console.
                Properties.Resources.MSG_PROGRESS_UPDATE ,                      // Format Item 0: Listing record # {0}
                plngItemNumber.ToString (                                       // Argument plngItemNumber is the current record number.
                    DisplayFormats.NUMBER_PER_REG_SETTINGS_0D ) ,               // Format the integer with thousands separators per the Regional Settings in the Windows Control Panel.
                s_strDispMsgNRecs );                                            // Format Item 1: of {1}

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
                          intJ <= s_intLastIndex ;
                          intJ++ )
                {
                    if ( intJ > ArrayInfo.ARRAY_FIRST_ELEMENT )
                    {   // All except the first element must be preceded by a TAB character.
                        sbTableLabelRow.Append ( SpecialCharacters.TAB_CHAR );
                    }   // if ( intJ > ArrayInfo.ARRAY_FIRST_ELEMENT )

                    sbTableLabelRow.Append ( paColumnInfo [ intJ ].ColumnName );
                }   // for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ; intJ <= s_intLastIndex ; intJ++ )

                pswDetailsList.WriteLine (
                    Properties.Resources.MSG_REPORT_HEADER ,                    // Format control string
                    s_csm.BaseStateManager.AppStartupTimeLocal ,                // Format Item 0: Run Date: {0}
                    s_csm.BaseStateManager.AppStartupTimeUtc ,                  // Format Item 1: ({1} UTC)
                    prs.Source ,                                                // Format Item 2: Table Name       = {2}
                    s_strDispMsgNRecs ,                                         // Format Item 3: Records in Table = {3}
                    Environment.NewLine );                                      // Format Item 4: Platform-dependent newline at end of each output line
                pswDetailsTable.WriteLine ( sbTableLabelRow.ToString ( ) );     // Since WriteLine won't convert this implicitly, ToString must be called by name.
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
                      intJ <= s_intLastIndex ;
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
                    s_strFinalRecordLabelPrefix = s_strFinalRecordLabelPrefix ??
                        FormatItem.UpgradeFormatItem (
                            Properties.Resources.MSG_RECORD_LABEL_PREFIX ,      // System.String        pstrFormat          Specify a valid format string to upgrade. The string must contain a token of the form {n}, where n is equal to pintItemIndex.
                            ArrayInfo.ARRAY_FIRST_ELEMENT ,                     // System.Int32         pintItemIndex       Specify the index of the item to be upgraded. The integer must be positive, and pstrFormat must contain at least once instance of a correspondingly numbered format item.
                            FormatItem.AdjustToMaximumWidth (                   // System.String        pstrFormatString    Specify a standard or custom Numeric or DateTime format string.Contrast this with pstrUpgrade , which expects you to supply the entire format item , ready for substitution.
                                ArrayInfo.ARRAY_FIRST_ELEMENT ,                 // System.Int32         pintItemIndex       The index is a standard zero based array subscript which corresponds to the position of an item in a list of objects.The list happens to be the items that correspond to the format items in a format string.
                                prs.RecordCount.ToString (                      // System.Int32         pintMaximumWidth    The maximum width is a positive integer that specifies the desired width of the item.
                                    DisplayFormats.NUMBER_PER_REG_SETTINGS_0D ).Length ,
                                FormatItem.Alignment.Right ,                    // FormatItem.Alignment penmAlignment       Specify Left or Right. Center alignment is unsupported, although it could be achieved with custom code.   
                                DisplayFormats.NUMBER_PER_REG_SETTINGS_0D ) );
                    strListTokenZero = string.Format (                          // Establish the maximum possible width given the number of records in the recordset.
                        s_strFinalRecordLabelPrefix ,                           // Format control string
                        prs.RecordCount.ToString (                              // An open ADO recordset bound to a table reports its record count.
                            DisplayFormats.NUMBER_PER_REG_SETTINGS_0D ) );      // Format the integer with thousands separators per the Regional Settings in the Windows Control Panel.
                    s_strLeadingWhiteSpace = s_strLeadingWhiteSpace ?? new string (
                        SpecialCharacters.SPACE_CHAR ,
                        strListTokenZero.IndexOf (
                            SpecialCharacters.COLON )                           // IndexOf returns the position of the colon, which is the number of characters that precede it.
                            + MagicNumbers.PLUS_TWO );                          // The extra spaces account for the positions occupied by the colon and the space that follows it.
                    strListTokenZero = string.Format (                          // Format the current item number to the same width.
                        s_strFinalRecordLabelPrefix ,                           // Format control string
                        plngItemNumber.ToString (                               // An open ADO recordset bound to a table reports its record count.
                            DisplayFormats.NUMBER_PER_REG_SETTINGS_0D ) );      // Format the integer with thousands separators per the Regional Settings in the Windows Control Panel.
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                }   // TRUE block, if ( intJ == ArrayInfo.ARRAY_FIRST_ELEMENT )
                else if ( intJ == s_intLastIndex )
                {   // Process the last column.
                    sbTableDetailRow.Append ( SpecialCharacters.TAB_CHAR );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );
                    pswDetailsTable.WriteLine ( sbTableDetailRow.ToString ( ) );
                }   // TRUE block, else if ( intJ == s_intLastIndex )
                else
                {   // Process all but the first and last columns.
                    sbTableDetailRow.Append ( SpecialCharacters.TAB_CHAR );
                    sbTableDetailRow.Append ( prs.Fields [ paColumnInfo [ intJ ].ColumnName ].Value );

                    if ( intJ == ArrayInfo.ARRAY_SECOND_ELEMENT )
                    {   // After the second iteration, this never changes.
                        strListTokenZero = s_strLeadingWhiteSpace;
                    }   // if ( intJ == ArrayInfo.ARRAY_SECOND_ELEMENT )
                }   // FALSE block, else if ( intJ == s_intLastIndex )

                pswDetailsList.WriteLine (
                    s_strDynamicListReportFormatString ,                        // Format Control String
                    new object [ ]                                              // Array of format items
                    {
                        strListTokenZero ,                                      // Format Item 0: Label Prefix
                        paColumnInfo [ intJ ].ColumnLabel ,                     // Format Item 1: Column Label
                        prs.Fields[paColumnInfo[intJ].ColumnName].Value ,       // Format Item 2: Column Value
                        Logic.IsLastForIterationLE (                            // Format Item 3: Newline or Nothing
                            intJ ,                                              // System.Int32 pintLoopIndex   Specify the integer loop index.
                            ( int ) s_intLastIndex )                            // System.Int32 pintLimit       Specify the integer limit value. (For now, nullable type s_intLastIndex must be cast to an ordinary int.)
                            ? Environment.NewLine                               // The last line gets a newline.
                            : SpecialStrings.EMPTY_STRING                       // All other lines get nothing.
                    } );
            }   // for ( int intJ = ArrayInfo.ARRAY_FIRST_ELEMENT ; intJ <= intLastIndex ; intJ++ )
        }   // private static void ListAllFieldsOnConsole


        /// <summary>
        /// Record the properties of a column in a tab-delimited report that can
        /// be imported into a Microsoft Excel worksheet.
        /// </summary>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// <param name="paColumnInfo">
        /// Pass in a reference to the ColumnNamesAndLabels from which labels
        /// are needed.
        /// </param>
        /// <param name="plngItemNumber">
        /// Pass in the current value of the item number. Passing in the value
        /// returned by MoreMath.IncrementAndReturnNewValue works well, as this
        /// single step also increments the item number. This value is safe to
        /// pass by value.
        /// </param>
        /// <param name="pswDetailsTable">
        /// Pass in a reference to a StreamWriter object that receives the
        /// tab delimited list report, which is initially null.
        /// </param>
        /// <param name="pfcwProgress">
        /// Pass in a reference to a FixedConsoleWriter that is used to report
        /// progress during execution, which is initially null.
        /// </param>
        private static void ListPropertiesOfColumn (
            Recordset pdbRecordSet ,                                            // The column properties are in the Fields collection.
            ColumnNamesAndLabels [ ] paColumnInfo ,                             // Array of column names, each of which should have an item in the Fields collection of the Recordset
            long plngItemNumber ,                                               // Subscript of current item in ColumnNamesAndLabels array
            StreamWriter pswDetailsTable ,                                      // Write the report into this open StreamWriter.
            FixedConsoleWriter pfcwProgress )                                   // Use this special object to update the console without scrolling its buffer up.
        {
            pfcwProgress.Write (                                                // Create or update the progress report on the console.
                Properties.Resources.MSG_SCHEMA_PROGRESS ,                      // Format control string
                plngItemNumber + ArrayInfo.ORDINAL_FROM_INDEX ,                 // Format Item 0: Listing Column # {0} - Since plngItemNumber is a long integer, ArrayInfo.OrdinalFromIndex requires a downcast. Inline addition is safer.
                paColumnInfo [ plngItemNumber ].ColumnName ,                    // Format Item 1: , {1} of
                pdbRecordSet.Source );                                          // Format Item 2: table {2}

            if ( plngItemNumber == ArrayInfo.ARRAY_FIRST_ELEMENT )
            {   // Create the label row. Argument plngItemNumber is the index (subscript) of the array subscript.
                string strLabelRow = Properties.Resources.MSG_COLUMN_PROPERTIES_LABEL_ROW.ReplaceEscapedTabsInStringFromResX ( );
                pswDetailsTable.WriteLine ( strLabelRow );
                s_strDynamicListReportFormatString = ReportHelpers.DetailTemplateFromLabels ( strLabelRow );
            }   // if ( plngItemNumber == ArrayInfo.ARRAY_FIRST_ELEMENT )

            Field field = pdbRecordSet.Fields [ paColumnInfo [ plngItemNumber ].ColumnName ];
            pswDetailsTable.WriteLine (
                s_strDynamicListReportFormatString ,
                new object [ ]
                {
                    plngItemNumber ,
                    paColumnInfo [ plngItemNumber ].ColumnName ,
                    field.ActualSize ,
                    field.Attributes ,
                    field.DataFormat ,
                    field.DefinedSize ,
                    field.NumericScale ,
                    field.Precision ,
                    field.Properties.Count ,
                    field.Status ,
                    field.Type
                } );
        }   // private static void ListPropertiesOfColumn


        /// <summary>
        /// Create and initialize the array of column names and labels, and open
        /// the Connection and Recordset objects.
        /// </summary>
        /// <param name="pdbConnection">
        /// Pass in a reference to the uninitialised Connection object that
        /// manages the connection to the Pervasive data base via an ADODB COM
        /// Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pdbRecordSet">
        /// Pass in a reference to the uninitialised Recordset object that
        /// returns the rows (records) from a Pervasive data base table via an
        /// ADODB COM Interop wrapper.
        /// <para>
        /// This object is passed in uninitialized, this method calls static
        /// method OpenTableRecordset to initialize it and return the array of
        /// ColumnNamesAndLabels objects that drive it. Since the method would
        /// otherwise need an additional argument to pass in the array, in
        /// addition to the Connection and Recordset objects, this slighly
        /// decreases the call overhead.
        /// </para>
        /// </param>
        /// <param name="pstrTableName">
        /// Pass in a reference to the string that contains the table name, for
        /// opening the table and displaying its name in console messages and on
        /// reports.
        /// <para>
        /// The table name is either extracted from the command line or a prompt
        /// is displayed to the operator. The main routine is responsible for
        /// completing this task before it calls this routine.
        /// </para>
        /// </param>
        /// <returns>
        /// The return value is the populated array of ColumnNamesAndLabels
        /// objects returned by private method CreateNameAndLabelArray, through
        /// which this method returns.
        /// </returns>
        /// <remarks>
        /// Difference between ref and out parameters in .NET: They're pretty
        /// much the same - the only difference is that a variable you pass as
        /// an out parameter doesn't need to be initialized but passing it as a
        /// ref parameter it has to be set to something.
        /// </remarks>
        /// <see href="https://stackoverflow.com/questions/135234/difference-between-ref-and-out-parameters-in-net"/>
        private static ColumnNamesAndLabels [ ] OpenTableRecordset (
            out Connection pdbConnection ,
            out Recordset pdbRecordSet ,
            string pstrTableName )
        {
            pdbConnection = new Connection ( );
            pdbRecordSet = new Recordset ( );

            //  ------------------------------------------------------------
            //  This should always be adUseServer unless you specifically
            //  want to use the Client Cursor Engine.
            //  ------------------------------------------------------------

            pdbConnection.CursorLocation = CursorLocationEnum.adUseServer;
            pdbConnection.ConnectionString = Properties.Settings.Default.ConnectionString;

            pdbConnection.Open ( );
            pdbRecordSet.Open (
                pstrTableName ,                                                 // Table or query name
                pdbConnection ,                                                 // Connection object, which must be open
                CursorTypeEnum.adOpenDynamic ,                                  // Cursor type
                LockTypeEnum.adLockOptimistic ,                                 // Locking scheme
                ( int ) CommandTypeEnum.adCmdTableDirect );                     // Flags: CommandTypeEnum specifies a Table

            return CreateNameAndLabelArray (
                pstrTableName ,
                pdbConnection );
        }   // private static ColumnNamesAndLabels [ ] OpenTableRecordset
        #endregion  // Module Subroutines
    }   // class Program
}   // partial namespace PSQLviaADOCS