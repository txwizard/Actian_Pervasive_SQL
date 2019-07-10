' ==============================================================================
'
' Assembly Name:        ConsoleApp1
'
' Root Namespace Name:  PSQLviaADOandVB
'
' Module Name:          Module1
'
' Module Objective:     This application demonstrates basic CRUD operations,
'                       which were once also called ACID operations, on a 
'                       Pervacive SQL (BTrieve) data base, using the ADODB data
'                       provider through COM interop.
'
'                       Sub Main() Of this Module Is the entry point routine of
'                       a Visual Basic console application.
'
' ------------------------------------------------------------------------------
' Revision History
' ------------------------------------------------------------------------------
'
' Date       By Description
' ---------- -- ----------------------------------------------------------------
' 2019/07/10 DG Initial implementation, including creation of a handful of core
'               helper routines that provide a Visual Basic implementation of my
'               tried and true console mode program skeleton.
' ==============================================================================

Imports PSQLviaADOandVB
Imports WizardWrx

''' <summary>
''' By convention, the Visual Basic module that defines the entry point routine
''' is called Module1, and is usually the only Module in a VB.NET application.
''' </summary>
Module Module1

    ''' <summary>
    ''' This routine defines the entry point of a character (console) mode VB
    ''' program.
    ''' </summary>
    Sub Main()

        Utils.DisplayStartupBanner()

        Try
            DoTask()
        Catch ex As Exception
            Utils.ReportException(ex)
        End Try

        Utils.DisplayShutdownBanner()

        If Environment.ExitCode = MagicNumbers.ERROR_SUCCESS Then
            Utils.ShutdownNormally()
        Else
            Utils.ShutdownAbnormally()
        End If

    End Sub     ' Main


    ''' <summary>
    ''' Assemble and return the array of column names and labels that drives the
    ''' routine that lists the field (column) values in one row of a table.
    ''' </summary>
    ''' <returns>
    ''' The return value is a populated array of ColumnNamesAndLabels objects.
    ''' </returns>
    Private Function CreateNameAndLabelArray() As ColumnNamesAndLabels()

        Const COLUMN_INDEX_STUDENT_ID As Integer = 0
        Const COLUMN_INDEX_TRANSACTION_NUMBER As Integer = 1
        Const COLUMN_INDEX_LOG As Integer = 2
        Const COLUMN_INDEX_AMOUNT_OWED As Integer = 3
        Const COLUMN_INDEX_AMOUNT_PAID As Integer = 4
        Const COLUMN_INDEX_REGISTRAR_ID As Integer = 5
        Const COLUMN_INDEX_COMMENTS As Integer = 6

        Const COLUMN_INDEX_ARRAY_SIZE As Integer = 6

        Dim objColName_Student_ID As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Student_ID")
        Dim objColName_Transaction_Number As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Transaction_Number")
        Dim objColName_Log As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Log")
        Dim objColName_Amount_Owed As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Amount_Owed")
        Dim objColName_Amount_Paid As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Amount_Paid")
        Dim objColName_Registrar_ID As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Registrar_ID")
        Dim objColName_Comments As ColumnNamesAndLabels.UniqueColumnName = New ColumnNamesAndLabels.UniqueColumnName("Comments")

        Dim objColumnNamesAndLabels_Student_ID As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Student_ID, My.Resources.MSG_COLUMN_LABEL_STRING_STUDENT_ID)
        Dim objColumnNamesAndLabels_Transaction_Number As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Transaction_Number, My.Resources.MSG_COLUMN_LABEL_STRING_TRANSACTION_NUMBER)
        Dim objColumnNamesAndLabels_Log As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Log, My.Resources.MSG_COLUMN_LABEL_STRING_LOG)
        Dim objColumnNamesAndLabels_Amount_Owed As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Amount_Owed, My.Resources.MSG_COLUMN_LABEL_STRING_AMOUNT_OWED)
        Dim objColumnNamesAndLabels_Amount_Paid As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Amount_Paid, My.Resources.MSG_COLUMN_LABEL_STRING_AMOUNT_PAID)
        Dim objColumnNamesAndLabels_Registrar_ID As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Registrar_ID, My.Resources.MSG_COLUMN_LABEL_STRING_REGISTRAR_ID)
        Dim objColumnNamesAndLabels_Comments As ColumnNamesAndLabels = New ColumnNamesAndLabels(objColName_Comments, My.Resources.MSG_COLUMN_LABEL_STRING_COMMENTS)

        Dim raobjColumnNamesAndLabels(COLUMN_INDEX_ARRAY_SIZE) As ColumnNamesAndLabels

        raobjColumnNamesAndLabels(COLUMN_INDEX_STUDENT_ID) = objColumnNamesAndLabels_Student_ID
        raobjColumnNamesAndLabels(COLUMN_INDEX_TRANSACTION_NUMBER) = objColumnNamesAndLabels_Transaction_Number
        raobjColumnNamesAndLabels(COLUMN_INDEX_LOG) = objColumnNamesAndLabels_Log
        raobjColumnNamesAndLabels(COLUMN_INDEX_AMOUNT_OWED) = objColumnNamesAndLabels_Amount_Owed
        raobjColumnNamesAndLabels(COLUMN_INDEX_AMOUNT_PAID) = objColumnNamesAndLabels_Amount_Paid
        raobjColumnNamesAndLabels(COLUMN_INDEX_REGISTRAR_ID) = objColumnNamesAndLabels_Registrar_ID
        raobjColumnNamesAndLabels(COLUMN_INDEX_COMMENTS) = objColumnNamesAndLabels_Comments

        Return raobjColumnNamesAndLabels

    End Function


    ''' <summary>
    ''' This method performs the task for which the program was created.
    ''' </summary>
    Private Sub DoTask()

        Const CONNECTION_STRING As String = "Provider=PervasiveOLEDB;Data Source=Demodata"
        Const TABLE_NAME_IS_BILLING As String = "Billing"

        Dim cn As New ADODB.Connection
        Dim rs As New ADODB.Recordset

        Dim swDetailsList As IO.StreamWriter = Nothing
        Dim swDetailsTable As IO.StreamWriter = Nothing

        Dim lngItemNumber As Long = ListInfo.LIST_IS_EMPTY

        ' ----------------------------------------------------------------------
        ' This should always be adUseServer unless you specifically want to use
        ' the Client Cursor Engine.
        ' ----------------------------------------------------------------------

        cn.CursorLocation = ADODB.CursorLocationEnum.adUseServer
        cn.ConnectionString = CONNECTION_STRING

        Try
            Dim aobjColumnNamesAndLabels As ColumnNamesAndLabels() = CreateNameAndLabelArray()
            Dim fcwProgress As ConsoleAppAids3.FixedConsoleWriter = New ConsoleAppAids3.FixedConsoleWriter(ConsoleColor.Yellow,
                                                                                                           ConsoleColor.Black)
            cn.Open()
            rs.Open(TABLE_NAME_IS_BILLING,
                cn,
                ADODB.CursorTypeEnum.adOpenDynamic,
                ADODB.LockTypeEnum.adLockOptimistic,
                ADODB.CommandTypeEnum.adCmdTableDirect)
            rs.MoveFirst()
            swDetailsList = New IO.StreamWriter(My.Settings.BillingDetailReportFileName,
                                                FileIOFlags.FILE_OUT_CREATE,
                                                Text.Encoding.UTF8,
                                                MagicNumbers.CAPACITY_08KB)
            swDetailsTable = New IO.StreamWriter(My.Settings.BillingDetailTabularReportFileName,
                                                 FileIOFlags.FILE_OUT_CREATE,
                                                 Text.Encoding.UTF8,
                                                 MagicNumbers.CAPACITY_08KB)

            Do  ' Until rs.EOF
                ListAllFieldsOnConsole(rs,
                                       aobjColumnNamesAndLabels,
                                       Utils.SetToIncrementedValue(lngItemNumber),
                                       swDetailsList,
                                       swDetailsTable,
                                       fcwProgress)
                rs.MoveNext()
            Loop Until rs.EOF   ' End of Do loop

            swDetailsList.WriteLine(My.Resources.REPORT_FOOTER,
                                    lngItemNumber)
            fcwProgress.ScrollUp()

            Console.WriteLine(My.Resources.MSG_TASK_SUMMARY,
                              Environment.NewLine,
                              My.Resources.MSG_LABEL_FOR_LISTING,
                              My.Settings.BillingDetailReportFileName)
            Console.WriteLine(My.Resources.MSG_TASK_SUMMARY,
                              SpecialStrings.EMPTY_STRING,
                              My.Resources.MSG_LABEL_FOR_TABLE,
                              My.Settings.BillingDetailTabularReportFileName)

        Catch ex As Exception
            Utils.ReportException(ex)
        Finally
            rs.Close()
            cn.Close()

            If swDetailsList.BaseStream.CanWrite Then
                swDetailsList.Close()
            End If  ' If swDetailsList.BaseStream.CanWrite Then

            If swDetailsTable.BaseStream.CanWrite Then
                swDetailsTable.Close()
            End If  ' If swDetailsList.BaseStream.CanWrite Then

            swDetailsList.Dispose()
            swDetailsTable.Dispose()
        End Try

    End Sub     ' DoTask


    ''' <summary>
    ''' List all columns (fields) in the Current record of a recordset.
    ''' </summary>
    ''' <param name="prs">
    ''' Pass in a reference to an ADODB.Recordset that has a valid (not null)
    ''' Current property.
    ''' </param>
    ''' <param name="paobjColumnNamesAndLabels">
    ''' Pass in the ColumnNamesAndLabels array that supplies column names and
    ''' labels for the report.
    ''' </param>
    ''' <param name="plngItemNumber">
    ''' Pass in the current value of the item number. Passing in the value
    ''' returned by Utils.SetToIncrementedValue works well, as this single step
    ''' also increments the item number. This value is safe to pass by value.
    ''' </param>
    ''' <param name="pswDetailsList">
    ''' Pass in a reference to the open StreamWriter onto which the itemized
    ''' list of billing items is written as sets of vertically aligned column
    ''' names and values. Using <paramref name="plngItemNumber"/>, this routine
    ''' looks after writing the label row.
    ''' </param>
    ''' <param name="pswDetailsTable">
    ''' Pass in a reference to the open StreamWriter onto which the details are
    ''' written as tab delimited rows. Using <paramref name="plngItemNumber"/>,
    ''' this routine looks after writing the label row.
    ''' </param>
    ''' <param name="pfcwProgress">
    ''' Pass in a reference to a working ConsoleAppAids3.FixedConsoleWriter
    ''' object through which the program updates the console without scrolling
    ''' the text above it off the screen.
    ''' </param>
    Private Sub ListAllFieldsOnConsole(ByRef prs As ADODB.Recordset,
                                       ByRef paobjColumnNamesAndLabels As ColumnNamesAndLabels(),
                                       ByVal plngItemNumber As Long,
                                       ByRef pswDetailsList As IO.StreamWriter,
                                       ByRef pswDetailsTable As IO.StreamWriter,
                                       ByRef pfcwProgress As ConsoleAppAids3.FixedConsoleWriter)

        pfcwProgress.Write(My.Resources.MSG_PROGRESS_UPDATE,
                           plngItemNumber)
        Dim intJ As Integer
        Dim intLastIndex = ArrayInfo.IndexFromOrdinal(paobjColumnNamesAndLabels.Length)
        Dim strLeadingWhiteSpace As String

        If plngItemNumber = MagicNumbers.PLUS_ONE Then
            Dim sbTableLabelRow As Text.StringBuilder = New Text.StringBuilder(MagicNumbers.CAPACITY_01KB)

            For intJ = ArrayInfo.ARRAY_FIRST_ELEMENT To intLastIndex
                If intJ > ArrayInfo.ARRAY_FIRST_ELEMENT Then
                    sbTableLabelRow.Append(SpecialCharacters.TAB_CHAR)
                End If  ' If intJ > ArrayInfo.ARRAY_FIRST_ELEMENT Then

                sbTableLabelRow.Append(paobjColumnNamesAndLabels(intJ).ColumnName)
            Next    ' For intJ = ArrayInfo.ARRAY_FIRST_ELEMENT To intLastIndex

            pswDetailsList.WriteLine(My.Resources.MSG_REPORT_HEADER,
                                     Process.GetCurrentProcess().StartTime,
                                     Process.GetCurrentProcess().StartTime.ToUniversalTime(),
                                     Environment.NewLine)
            pswDetailsTable.WriteLine(sbTableLabelRow.ToString())
        End If  ' If plngItemNumber = MagicNumbers.PLUS_ONE Then

        Dim sbTableDetailRow As Text.StringBuilder = New Text.StringBuilder(MagicNumbers.CAPACITY_01KB)

        For intJ = ArrayInfo.ARRAY_FIRST_ELEMENT To intLastIndex
            Select Case intJ
                Case ArrayInfo.ARRAY_FIRST_ELEMENT
                    pswDetailsList.WriteLine(paobjColumnNamesAndLabels(intJ).ColumnLabel,
                                         plngItemNumber,
                                         prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value)
                    strLeadingWhiteSpace = New String(SpecialCharacters.SPACE_CHAR,
                                                  paobjColumnNamesAndLabels(intJ).ColumnLabel.IndexOf(SpecialCharacters.COLON) + MagicNumbers.PLUS_TWO)
                    sbTableDetailRow.Append(prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value)
                Case intLastIndex
#Disable Warning BC42104 ' Variable is used before it has been assigned a value.
                    pswDetailsList.WriteLine(paobjColumnNamesAndLabels(intJ).ColumnLabel,
                                             strLeadingWhiteSpace,
                                             prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value,
                                             Environment.NewLine)
#Enable Warning BC42104 ' Variable is used before it has been assigned a value.
                    sbTableDetailRow.Append(SpecialCharacters.TAB_CHAR)
                    sbTableDetailRow.Append(prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value)
                Case Else
#Disable Warning BC42104 ' Variable is used before it has been assigned a value.
                    pswDetailsList.WriteLine(paobjColumnNamesAndLabels(intJ).ColumnLabel,
                                             strLeadingWhiteSpace,
                                             prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value)
#Enable Warning BC42104 ' Variable is used before it has been assigned a value.
                    sbTableDetailRow.Append(SpecialCharacters.TAB_CHAR)
                    sbTableDetailRow.Append(prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value)
            End Select
        Next    ' For intJ = Utils.ARRAY_SUBSCRIPT_FIRST To paobjColumnNamesAndLabels.Length

        pswDetailsTable.WriteLine(sbTableDetailRow.ToString())

    End Sub '   ListAllFieldsOnConsole

End Module  ' Module1