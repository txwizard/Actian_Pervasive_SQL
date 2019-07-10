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

        DoTask()

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

        'This should always be adUseServer unless you
        'specifically want to use the Client Cursor Engine

        cn.CursorLocation = ADODB.CursorLocationEnum.adUseServer
        cn.ConnectionString = CONNECTION_STRING

        Try
            cn.Open()
            rs.Open(TABLE_NAME_IS_BILLING,
                cn,
                ADODB.CursorTypeEnum.adOpenDynamic,
                ADODB.LockTypeEnum.adLockOptimistic,
                ADODB.CommandTypeEnum.adCmdTableDirect)
            rs.MoveFirst()
            Dim aobjColumnNamesAndLabels As ColumnNamesAndLabels() = CreateNameAndLabelArray()
            ListAllFieldsOnConsole(rs,
                                   aobjColumnNamesAndLabels)


        Catch ex As Exception
            Console.WriteLine(My.Resources.MSG_EXCEPTION_TYPE_AND_MESSAGE,      ' Format control string containing 3 tokens
                              ex.GetType().FullName,                            ' Format Item 0: An {0} exception arose.
                              ex.Message,                                       ' Format Item 1: Exception Message: {1}"
                              Environment.NewLine)                              ' Format Item 2: arose.{2}{2}Exception
            Console.WriteLine(My.Resources.MSG_EXCEPTION_HRESULT,               ' Format control string containing 1 token
                              ex.HResult)                                       ' Format Item 0: HResult: 0
            Console.WriteLine(My.Resources.MSG_EXCEPTION_SOURCE,                ' Format control string containing 1 token
                              ex.Source)                                        ' Format Item 0: Exception Source: {0}
            Console.WriteLine(My.Resources.MSG_EXCEPTION_TARGETSITE,            ' Format control string containing 1 token
                              ex.TargetSite)                                    ' Format Item 0: Exception TargetSite: {0}
            Console.WriteLine(My.Resources.MSG_EXCEPTION_STACKTRACE,            ' Format control string containing 2 tokenS
                              Utils.BeautifyStackTrace(ex.StackTrace,           ' Format Item 0: Exception StackTrace:{1}{0}
                                                       My.Resources.MSG_EXCEPTION_STACKTRACE),
                              Environment.NewLine)                              ' Format Item 1: Exception StackTrace:{1}{0}

            Environment.ExitCode = MagicNumbers.ERROR_RUNTIME
        Finally
            rs.Close()
            cn.Close()
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
    Private Sub ListAllFieldsOnConsole(ByRef prs As ADODB.Recordset,
                                       ByRef paobjColumnNamesAndLabels As ColumnNamesAndLabels())

        Dim intJ As Integer
        Dim intLastIndex = ArrayInfo.IndexFromOrdinal(paobjColumnNamesAndLabels.Length)

        For intJ = ArrayInfo.ARRAY_FIRST_ELEMENT To intLastIndex
            Console.WriteLine(paobjColumnNamesAndLabels(intJ).ColumnLabel,
                              prs.Fields(paobjColumnNamesAndLabels(intJ).ColumnName).Value)
        Next    ' For intJ = Utils.ARRAY_SUBSCRIPT_FIRST To paobjColumnNamesAndLabels.Length

    End Sub '   ListAllFieldsOnConsole

End Module  ' Module1