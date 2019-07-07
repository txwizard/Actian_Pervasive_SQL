Module Module1

    Sub Main()
        Dim cn As New ADODB.Connection
        Dim rs As New ADODB.Recordset

        'This should always be adUseServer unless you
        'specifically want to use the Client Cursor Engine

        cn.CursorLocation = ADODB.CursorLocationEnum.adUseServer

        cn.ConnectionString = "Provider=PervasiveOLEDB;Data Source=Demodata"
        cn.Open()
        rs.Open("Billing",
                cn,
                ADODB.CursorTypeEnum.adOpenDynamic,
                ADODB.LockTypeEnum.adLockOptimistic,
                ADODB.CommandTypeEnum.adCmdTableDirect)
        rs.MoveFirst()
        Console.WriteLine("Student ID: {0}",
                          rs.Fields("Student_ID").Value)
        rs.Close()
        cn.Close()

    End Sub

End Module
