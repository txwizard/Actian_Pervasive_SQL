﻿'------------------------------------------------------------------------------
' <auto-generated>
'     This code was generated by a tool.
'     Runtime Version:4.0.30319.42000
'
'     Changes to this file may cause incorrect behavior and will be lost if
'     the code is regenerated.
' </auto-generated>
'------------------------------------------------------------------------------

Option Strict On
Option Explicit On

Imports System

Namespace My.Resources
    
    'This class was auto-generated by the StronglyTypedResourceBuilder
    'class via a tool like ResGen or Visual Studio.
    'To add or remove a member, edit your .ResX file then rerun ResGen
    'with the /str option, or rebuild your VS project.
    '''<summary>
    '''  A strongly-typed resource class, for looking up localized strings, etc.
    '''</summary>
    <Global.System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "15.0.0.0"),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Runtime.CompilerServices.CompilerGeneratedAttribute(),  _
     Global.Microsoft.VisualBasic.HideModuleNameAttribute()>  _
    Friend Module Resources
        
        Private resourceMan As Global.System.Resources.ResourceManager
        
        Private resourceCulture As Global.System.Globalization.CultureInfo
        
        '''<summary>
        '''  Returns the cached ResourceManager instance used by this class.
        '''</summary>
        <Global.System.ComponentModel.EditorBrowsableAttribute(Global.System.ComponentModel.EditorBrowsableState.Advanced)>  _
        Friend ReadOnly Property ResourceManager() As Global.System.Resources.ResourceManager
            Get
                If Object.ReferenceEquals(resourceMan, Nothing) Then
                    Dim temp As Global.System.Resources.ResourceManager = New Global.System.Resources.ResourceManager("PSQLviaADOandVB.Resources", GetType(Resources).Assembly)
                    resourceMan = temp
                End If
                Return resourceMan
            End Get
        End Property
        
        '''<summary>
        '''  Overrides the current thread's CurrentUICulture property for all
        '''  resource lookups using this strongly typed resource class.
        '''</summary>
        <Global.System.ComponentModel.EditorBrowsableAttribute(Global.System.ComponentModel.EditorBrowsableState.Advanced)>  _
        Friend Property Culture() As Global.System.Globalization.CultureInfo
            Get
                Return resourceCulture
            End Get
            Set
                resourceCulture = value
            End Set
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Duplicate column name.
        '''</summary>
        Friend ReadOnly Property ERRMSG_DUPLICATE_COLUMN_NAME() As String
            Get
                Return ResourceManager.GetString("ERRMSG_DUPLICATE_COLUMN_NAME", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}Amount Owed: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_AMOUNT_OWED() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_AMOUNT_OWED", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}Amount Paid: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_AMOUNT_PAID() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_AMOUNT_PAID", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}Comments: {1}{2}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_COMMENTS() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_COMMENTS", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}Log: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_LOG() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_LOG", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}Registrar ID: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_REGISTRAR_ID() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_REGISTRAR_ID", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Record Number {0,5}: Student ID: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_STUDENT_ID() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_STUDENT_ID", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}Transaction Number: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMN_LABEL_STRING_TRANSACTION_NUMBER() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMN_LABEL_STRING_TRANSACTION_NUMBER", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to ColumnName = {0}, ColumnIndex = {1}, ColumnValue = {2}, ColumnLabel = {3}.
        '''</summary>
        Friend ReadOnly Property MSG_COLUMNNAMESANDLABELS_TOSTRING() As String
            Get
                Return ResourceManager.GetString("MSG_COLUMNNAMESANDLABELS_TOSTRING", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to     Exception HResult: {0}.
        '''</summary>
        Friend ReadOnly Property MSG_EXCEPTION_HRESULT() As String
            Get
                Return ResourceManager.GetString("MSG_EXCEPTION_HRESULT", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to     Exception Source: {0}.
        '''</summary>
        Friend ReadOnly Property MSG_EXCEPTION_SOURCE() As String
            Get
                Return ResourceManager.GetString("MSG_EXCEPTION_SOURCE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to     Exception StackTrace: {0}{1}.
        '''</summary>
        Friend ReadOnly Property MSG_EXCEPTION_STACKTRACE() As String
            Get
                Return ResourceManager.GetString("MSG_EXCEPTION_STACKTRACE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to     Exception TargetSite: {0}.
        '''</summary>
        Friend ReadOnly Property MSG_EXCEPTION_TARGETSITE() As String
            Get
                Return ResourceManager.GetString("MSG_EXCEPTION_TARGETSITE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to An {0} exception arose.{2}{2}    Exception Message: {1}.
        '''</summary>
        Friend ReadOnly Property MSG_EXCEPTION_TYPE_AND_MESSAGE() As String
            Get
                Return ResourceManager.GetString("MSG_EXCEPTION_TYPE_AND_MESSAGE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Listing.
        '''</summary>
        Friend ReadOnly Property MSG_LABEL_FOR_LISTING() As String
            Get
                Return ResourceManager.GetString("MSG_LABEL_FOR_LISTING", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Table  .
        '''</summary>
        Friend ReadOnly Property MSG_LABEL_FOR_TABLE() As String
            Get
                Return ResourceManager.GetString("MSG_LABEL_FOR_TABLE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}, version {1}{4}Started at {2} ({3} UTC){4}.
        '''</summary>
        Friend ReadOnly Property MSG_PROGRAM_BEGIN() As String
            Get
                Return ResourceManager.GetString("MSG_PROGRAM_BEGIN", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {3}{0} completed at {1}{3}Running time: {2}.
        '''</summary>
        Friend ReadOnly Property MSG_PROGRAM_DONE() As String
            Get
                Return ResourceManager.GetString("MSG_PROGRAM_DONE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to     Listing record # {0}.
        '''</summary>
        Friend ReadOnly Property MSG_PROGRESS_UPDATE() As String
            Get
                Return ResourceManager.GetString("MSG_PROGRESS_UPDATE", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Report Name: Listing of everything in the Billing table{2}Run Date: {0} ({1} UTC){2}.
        '''</summary>
        Friend ReadOnly Property MSG_REPORT_HEADER() As String
            Get
                Return ResourceManager.GetString("MSG_REPORT_HEADER", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Execution succeeded..
        '''</summary>
        Friend ReadOnly Property MSG_SHUTDOWN_NORMALLY() As String
            Get
                Return ResourceManager.GetString("MSG_SHUTDOWN_NORMALLY", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Execution failed with status code {0:0x8x} ({1} decimal)..
        '''</summary>
        Friend ReadOnly Property MSG_SHUTDOWN_WITH_ERROR() As String
            Get
                Return ResourceManager.GetString("MSG_SHUTDOWN_WITH_ERROR", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to {0}{1} File Name = {2}.
        '''</summary>
        Friend ReadOnly Property MSG_TASK_SUMMARY() As String
            Get
                Return ResourceManager.GetString("MSG_TASK_SUMMARY", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to Press the RETURN key to return to Windows..
        '''</summary>
        Friend ReadOnly Property MSG_WAIT_FOR_CARBON_UNIT() As String
            Get
                Return ResourceManager.GetString("MSG_WAIT_FOR_CARBON_UNIT", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to End of report, Total records = {0}.
        '''</summary>
        Friend ReadOnly Property REPORT_FOOTER() As String
            Get
                Return ResourceManager.GetString("REPORT_FOOTER", resourceCulture)
            End Get
        End Property
        
        '''<summary>
        '''  Looks up a localized string similar to ColumnName = {0}, ColumnLabel = {1}.
        '''</summary>
        Friend ReadOnly Property UNIQUE_COLUMN_NAME_TOSTRING() As String
            Get
                Return ResourceManager.GetString("UNIQUE_COLUMN_NAME_TOSTRING", resourceCulture)
            End Get
        End Property
    End Module
End Namespace
