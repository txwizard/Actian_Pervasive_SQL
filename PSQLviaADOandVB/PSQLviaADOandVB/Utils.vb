' ==============================================================================
'
' Assembly Name:        ConsoleApp1
'
' Root Namespace Name:  PSQLviaADOandVB
'
' Module Name:          Utils
'
' Module Objective:     This class exposes static helper methods intended to
'                       meet the needs of a character mode (console) program.
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

Imports WizardWrx

''' <summary>
''' This class exposes static helper methods intended to meet the needs of a
''' character mode (console) program.
''' </summary>
Public Class Utils

    '''<summary>
    '''Format the lines of a stacktrace so that they align vertically under the
    '''first line.
    '''</summary>
    '''<param name="pstrStackTrace">
    '''Pass in the StackTrace property of an exception.
    '''</param>
    '''<param name="pstrMessageTemplate">
    '''Pass in the message template, which must contain a colon against which
    '''subsequent entries in the stack trace are aligned.
    '''</param>
    '''<returns>
    '''The return value is the formatted stack trace string, ready for display.
    '''</returns>
    Public Shared Function BeautifyStackTrace(ByRef pstrStackTrace As String,
                                              ByRef pstrMessageTemplate As String) As String

        '   -----------------------------------------------------------------------------------------------------------------
        '   The following code is ported from F:\Source_Code\Visual_Studio\Projects\WizardWrx_Libs\BitMath\TestStand\Util.cs.
        '   -----------------------------------------------------------------------------------------------------------------

        Dim intTokenPos As Integer = pstrMessageTemplate.IndexOf(SpecialCharacters.COLON) + MagicNumbers.PLUS_TWO
        Dim strLeadingSpaces As String = New String(SpecialCharacters.SPACE_CHAR,
                                                    intTokenPos)
        Dim strRawPrefix As String = WizardWrx.Common.Properties.Resources.STACK_TRACE_ENTRY_PREFIX
        Dim achrTrimList As Char() = {SpecialCharacters.SPACE_CHAR}
        Dim strTrimmedPrefix As String = strRawPrefix.TrimStart(achrTrimList)
        Dim strOldToken As String = String.Concat(Environment.NewLine,
                                                  strRawPrefix)
        Dim strNewToken As String = String.Concat(Environment.NewLine,
                                                  strLeadingSpaces,
                                                  strTrimmedPrefix)

        Return pstrStackTrace.Replace(strOldToken,
                                      strNewToken).TrimStart(achrTrimList)

    End Function    ' BeautifyStackTrace


    '''<summary>
    '''Display a two-line message when the program is shutting down. The first
    '''line of the message reports the program name and the current time, while
    '''the second reports its total running time. Local and UTC times are
    '''reported.
    '''</summary>
    Public Shared Sub DisplayShutdownBanner()

        Dim myProcess As Process = Process.GetCurrentProcess()
        Dim dtmStopTime As DateTime = DateTime.Now
        Dim lngRunningTimeTicks As Long = dtmStopTime.ToUniversalTime().Ticks - myProcess.StartTime.ToUniversalTime().Ticks
        Dim tsMyRunningTime As TimeSpan = New TimeSpan(lngRunningTimeTicks)

        Console.WriteLine(My.Resources.MSG_PROGRAM_DONE,                        ' Format control string containing 4 tokens
                          My.Application.Info.AssemblyName,                     ' Format Item 0: {0} completed successfully
                          dtmStopTime,                                          ' Format Item 1: successfully at {1}
                          tsMyRunningTime,                                      ' Format Item 2: Running time: {2}"
                          Environment.NewLine)                                  ' Format Item 3: {3}Running

    End Sub     ' DisplayShutdownBanner


    '''<summary>
    '''Display a two-line message when the program starts. The first line of the
    '''message displays the program name and version, while the second reports
    '''the process start time. Local and UTC times are reported.
    '''</summary>
    Public Shared Sub DisplayStartupBanner()

        Dim myProcess As Process = Process.GetCurrentProcess()

        Console.WriteLine(My.Resources.MSG_PROGRAM_BEGIN,                       ' Format control string containing 5 tokens
                          My.Application.Info.AssemblyName,                     ' Format Item 0: {0}, version
                          My.Application.Info.Version,                          ' Format Item 1: version {1}
                          myProcess.StartTime,                                  ' Format Item 2: Started at {2}
                          myProcess.StartTime.ToUniversalTime(),                ' Format Item 3: ({3} UTC)
                          Environment.NewLine)                                  ' Format Item 4: {4}Started

    End Sub     ' DisplayStartupBanner


    ''' <summary>
    ''' Report exceptions of all stripes.
    ''' </summary>
    ''' <param name="pexAllKinds">
    ''' Pass in a reference to an Exception or derivative thereof.
    ''' </param>
    Public Shared Sub ReportException(pexAllKinds As Exception)

        Console.WriteLine(My.Resources.MSG_EXCEPTION_TYPE_AND_MESSAGE,      ' Format control string containing 3 tokens
                          pexAllKinds.GetType().FullName,                   ' Format Item 0: An {0} exception arose.
                          pexAllKinds.Message,                              ' Format Item 1: Exception Message: {1}"
                          Environment.NewLine)                              ' Format Item 2: arose.{2}{2}Exception
        Console.WriteLine(My.Resources.MSG_EXCEPTION_HRESULT,               ' Format control string containing 1 token
                          pexAllKinds.HResult)                              ' Format Item 0: HResult: 0
        Console.WriteLine(My.Resources.MSG_EXCEPTION_SOURCE,                ' Format control string containing 1 token
                          pexAllKinds.Source)                               ' Format Item 0: Exception Source: {0}
        Console.WriteLine(My.Resources.MSG_EXCEPTION_TARGETSITE,            ' Format control string containing 1 token
                          pexAllKinds.TargetSite)                           ' Format Item 0: Exception TargetSite: {0}
        Console.WriteLine(My.Resources.MSG_EXCEPTION_STACKTRACE,            ' Format control string containing 2 tokenS
                          Utils.BeautifyStackTrace(pexAllKinds.StackTrace,  ' Format Item 0: Exception StackTrace:{1}{0}
                                                   My.Resources.MSG_EXCEPTION_STACKTRACE),
                          Environment.NewLine)                              ' Format Item 1: Exception StackTrace:{1}{0}

        Environment.ExitCode = MagicNumbers.ERROR_RUNTIME

    End Sub     ' ReportException


    ''' <summary>
    ''' Increment a static (shared) value, returning the incremented value.
    ''' </summary>
    ''' <param name="pintIncrementThisValue">
    ''' Pass in a reference to the shared value to increment and return. Since
    ''' the value is incremented, it must be passed explicitly by reference.
    ''' </param>
    ''' <returns>
    ''' The return value is the initial value of
    ''' <paramref name="pintIncrementThisValue"/> plus one, which also becomes
    ''' the new value of <paramref name="pintIncrementThisValue"/>.
    ''' </returns>
    Public Shared Function SetToIncrementedValue(ByRef pintIncrementThisValue As Integer) As Integer

        pintIncrementThisValue += 1
        Return pintIncrementThisValue

    End Function    ' SetToIncrementedValue (1 of 2)


    ''' <summary>
    ''' Increment a static (shared) value, returning the incremented value.
    ''' </summary>
    ''' <param name="plngIncrementThisValue">
    ''' Pass in a reference to the shared value to increment and return. Since
    ''' the value is incremented, it must be passed explicitly by reference.
    ''' </param>
    ''' <returns>
    ''' The return value is the initial value of
    ''' <paramref name="plngIncrementThisValue"/> plus one, which also becomes
    ''' the new value of <paramref name="plngIncrementThisValue"/>.
    ''' </returns>
    Public Shared Function SetToIncrementedValue(ByRef plngIncrementThisValue As Long) As Long

        plngIncrementThisValue += 1
        Return plngIncrementThisValue

    End Function    ' SetToIncrementedValue (2 of 2)


    '''<summary>
    '''Display a message that indicates that the program failed and is returning
    '''a nonzero status code. Both decimal and hexadecimal representations of
    '''the status code appear in the message.
    '''</summary>
    Public Shared Sub ShutdownAbnormally()

        Console.Write(My.Resources.MSG_SHUTDOWN_WITH_ERROR,                     ' Format control string containing 2 tokenS
                      Environment.ExitCode,                                     ' Format Item 0: Execution failed with status code {0:0x8x}
                      Environment.ExitCode)                                     ' Format Item 1: ({1} decimal).
        WaitForCarbonUnit()

    End Sub     ' ShutdownAbnormally


    '''<summary>
    '''Display a message that indicates that the program successfully completed
    '''its assigned task.
    '''</summary>
    Public Shared Sub ShutdownNormally()

        Console.WriteLine(My.Resources.MSG_SHUTDOWN_NORMALLY)
        WaitForCarbonUnit()

    End Sub     ' ShutdownNormally


    '''<summary>
    '''Display a prompt, then wait until an operator presses the RETURN key.
    '''</summary>
    '''<param name="pstrPrompt">
    '''Unless its value is a null reference (Nothing), substitute this prompt
    '''string for the default message, which is read from the embedded managed
    '''resource strings.
    '''</param>
    Public Shared Sub WaitForCarbonUnit(Optional ByRef pstrPrompt As String = Nothing)

        If pstrPrompt Is Nothing Then
            Console.Write(My.Resources.MSG_WAIT_FOR_CARBON_UNIT)
        Else
            Console.Write(pstrPrompt)
        End If

        Console.ReadLine()

    End Sub     ' WaitForCarbonUnit

End Class   ' Utils