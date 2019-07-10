' ==============================================================================
'
' Assembly Name:        ConsoleApp1
'
' Root Namespace Name:  PSQLviaADOandVB
'
' Module Name:          ColumnNamesAndLabels
'
' Module Objective:     This class models a column name and its label,
'                       optionally associating both with a database table.
'
' ------------------------------------------------------------------------------
' Revision History
' ------------------------------------------------------------------------------
'
' Date       By Description
' ---------- -- ----------------------------------------------------------------
' 2019/07/09 DG Initial implementation, including creation of a handful of core
'               helper routines that provide a Visual Basic implementation of my
'               tried and true console mode program skeleton.
'
' 2019/07/09 DG Suppress IntelliSense code analysis warning IDE0028.
' ==============================================================================

Imports WizardWrx

''' <summary>
''' This class models a set of column names and labels. Each column has an
''' auto-generated zero-based index number.
''' </summary>
Public Class ColumnNamesAndLabels
    Implements IComparable(Of ColumnNamesAndLabels)

    Private ReadOnly _strColumnName As UniqueColumnName
    Private ReadOnly _strTableName As String
    Private _strColumnValue As String
    Private ReadOnly _intColumnIndex As Integer = WizardWrx.ArrayInfo.ARRAY_INVALID_INDEX
    Private Shared s_intNextIndex As Integer = WizardWrx.ArrayInfo.ARRAY_INVALID_INDEX
    Private Shared s_fIndexIncrementIsEnabled As Boolean = True


    ''' <summary>
    ''' To enforce object initializeation, the default constructor is marked as
    ''' private.
    ''' </summary>
    Private Sub New()

    End Sub     ' New (1 of 9)


    ''' <summary>
    ''' Construct an instance that identifies a table by name, has a value, and
    ''' has an automatically generated index number.
    ''' </summary>
    ''' <param name="pstrTableName">
    ''' String containing name of table
    ''' </param>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    ''' <param name="pstrColumnValue">
    ''' String representation of a value to assign to the column, which may then
    ''' be used for reporting.
    ''' </param>
    Public Sub New(ByRef pstrTableName As String,
                   ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String,
                   ByRef pstrColumnValue As String)

        _strTableName = pstrTableName
        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel
        _strColumnValue = pstrColumnValue

        _intColumnIndex = ++s_intNextIndex

    End Sub     ' New (2 of 9)


    ''' <summary>
    ''' Construct an instance that identifies a table by name, has a value, and
    ''' has an explicitly assigned index number.
    ''' </summary>
    ''' <param name="pstrTableName">
    ''' String containing name of table
    ''' </param>
    ''' <param name="pintColumnIndex">
    ''' Integer containing index to assign, which also disables automatic
    ''' assignment for all subsequent instances
    ''' </param>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    ''' <param name="pstrColumnValue">
    ''' String representation of a value to assign to the column, which may then
    ''' be used for reporting.
    ''' </param>
    Public Sub New(ByRef pstrTableName As String,
                   ByVal pintColumnIndex As Integer,
                   ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String,
                   ByRef pstrColumnValue As String)

        _strTableName = pstrTableName
        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel
        _strColumnValue = pstrColumnValue

        _intColumnIndex = pintColumnIndex
        s_fIndexIncrementIsEnabled = False

    End Sub     ' New (3 of 9)


    ''' <summary>
    ''' Construct an instance that omits the table name, has a value, and
    ''' has an automatically generated index number.
    ''' </summary>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    ''' <param name="pstrColumnValue">
    ''' String representation of a value to assign to the column, which may then
    ''' be used for reporting.
    ''' </param>
    Public Sub New(ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String,
                   ByRef pstrColumnValue As String)

        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel
        _strColumnValue = pstrColumnValue

        _intColumnIndex = ++s_intNextIndex

        _strTableName = String.Empty

    End Sub     ' New (4 of 9)


    ''' <summary>
    ''' Construct an instance that omits the table name, has a value, and
    ''' has an explicitly assigned index number.
    ''' </summary>
    ''' <param name="pintColumnIndex">
    ''' Integer containing index to assign, which also disables automatic
    ''' assignment for all subsequent instances
    ''' </param>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    ''' <param name="pstrColumnValue">
    ''' String representation of a value to assign to the column, which may then
    ''' be used for reporting.
    ''' </param>
    Public Sub New(ByVal pintColumnIndex As Integer,
                   ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String,
                   ByRef pstrColumnValue As String)

        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel
        _strColumnValue = pstrColumnValue

        _intColumnIndex = pintColumnIndex
        s_fIndexIncrementIsEnabled = False

        _strTableName = String.Empty

    End Sub     ' New (5 of 9)


    ''' <summary>
    ''' Construct an instance that identifies a table by name and has an 
    ''' automatically generated index number, but omits a value, which can be
    ''' set through its read/write property.
    ''' </summary>
    ''' <param name="pstrTableName">
    ''' String containing name of table
    ''' </param>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    Public Sub New(ByRef pstrTableName As String,
                   ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String)

        _strTableName = pstrTableName
        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel

        _intColumnIndex = ++s_intNextIndex

        _strColumnValue = Nothing

    End Sub     ' New (6 of 9)


    ''' <summary>
    ''' Construct an instance that identifies a table by name and has an 
    ''' explicitly assigned index number, but omits a value, which can be
    ''' set through its read/write property.
    ''' </summary>
    ''' <param name="pstrTableName">
    ''' String containing name of table
    ''' </param>
    ''' <param name="pintColumnIndex">
    ''' Integer containing index to assign, which also disables automatic
    ''' assignment for all subsequent instances
    ''' </param>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    Public Sub New(ByRef pstrTableName As String,
                   ByVal pintColumnIndex As Integer,
                   ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String)

        _strTableName = pstrTableName
        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel

        _intColumnIndex = pintColumnIndex
        s_fIndexIncrementIsEnabled = False

        _strColumnValue = Nothing

    End Sub     ' New (7 of 9)


    ''' <summary>
    ''' Construct an instance that has a column name and label, along with an
    ''' automatically generated index. The table and value proeprties are
    ''' omitted, and remain null, although the value may be subsequently set.
    ''' </summary>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    Public Sub New(ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String)

        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel

        _intColumnIndex = Utils.SetToIncrementedValue(s_intNextIndex)

        _strTableName = String.Empty
        _strColumnValue = Nothing

    End Sub     ' New (8 of 9)


    ''' <summary>
    ''' Construct an instance that has a column name and label, along with an
    ''' explicitly set index. The table and value proeprties are
    ''' omitted, and remain null, although the value may be subsequently set.
    ''' </summary>
    ''' <param name="pintColumnIndex">
    ''' Integer containing index to assign, which also disables automatic
    ''' assignment for all subsequent instances
    ''' </param>
    ''' <param name="pstrColumnName">
    ''' ValidColumnName containing name of column, a string, which must be
    ''' globally unique
    ''' </param>
    ''' <param name="pstrColumnLabel">
    ''' String containing column label, which is not sanity-checked for
    ''' uniqueness
    ''' </param>
    Public Sub New(ByVal pintColumnIndex As Integer,
                   ByRef pstrColumnName As UniqueColumnName,
                   ByRef pstrColumnLabel As String)

        _strColumnName = pstrColumnName
        ColumnLabel = pstrColumnLabel

        _intColumnIndex = pintColumnIndex
        s_fIndexIncrementIsEnabled = False

        _strTableName = String.Empty
        _strColumnValue = Nothing

    End Sub     ' New (9 of 9)


    ''' <summary>
    ''' Gets the automatically generated or explicitly set column index
    ''' </summary>
    ''' <returns>
    ''' The return value is an index, which is expected to be a valid array
    ''' subscript value.
    ''' </returns>
    Public ReadOnly Property ColumnIndex As Integer
        Get
            Return _intColumnIndex
        End Get     ' ColumnIndex Getter Method
    End Property    ' ColumnIndex Property


    ''' <summary>
    ''' Gets the column label that was passed into the constructor
    ''' </summary>
    ''' <returns>
    ''' The return value is a string that is intended for use as a line item
    ''' report of the column value.
    ''' </returns>
    Public ReadOnly Property ColumnLabel As String                              ' ColumnLabel Property


    ''' <summary>
    ''' Return the string stored in the private ValidColumnName property.
    ''' </summary>
    ''' <returns>
    ''' The return value is the globally unique column name, made so because it
    ''' takes into account the table name, if any, that was specified.
    ''' </returns>
    Public ReadOnly Property ColumnName As String
        Get
            Return _strColumnName.ColumnName
        End Get     ' Column Getter Method
    End Property    ' Column Property


    ''' <summary>
    ''' Gets or sets the column value
    ''' </summary>
    ''' <returns>
    ''' The return value is a string representation of the column value.
    ''' </returns>
    Public Property ColumnValue
        Get
            Return _strColumnValue
        End Get     ' ColumnValue Getter Method
        Set(value)
            _strColumnValue = value
        End Set     ' ColumnValue Setter Method
    End Property    ' ColumnValue Property


    ''' <summary>
    ''' Gets the table name, if any, that was passed into the constructor
    ''' </summary>
    ''' <returns>
    ''' The return value is a string, which is the empty string when the table
    ''' name is omitted from the constructor call.
    ''' </returns>
    Public ReadOnly Property TableName As String
        Get
            Return _strTableName
        End Get     ' TableName Getter Method
    End Property    ' TableName Property


    ''' <summary>
    ''' Override the Equals method on the base class, System.Object, to return a
    ''' value that is consistent with the IComparable implemntation.
    ''' </summary>
    ''' <param name="obj">
    ''' Pass in another object, which must be another ColumnNamesAndLabels
    ''' instance if the result is to be meaningful.
    ''' </param>
    ''' <returns>
    ''' When <paramref name="obj"/> is an instance of ColumnNamesAndLabels, the
    ''' return value is the result of testing their equality. Otherwise, the
    ''' return value is FALSE. Equality is evaluated by evaluating the equality
    ''' of the string returned by the same CreateComparand method that drives
    ''' the IComparable implemntation.
    ''' </returns>
    Public Overrides Function Equals(obj As Object) As Boolean

        If obj.GetType() = Me.GetType() Then
            Dim objOther As ColumnNamesAndLabels = obj
            Return CreateComparand(Me).Equals(CreateComparand(objOther))
        Else
            Return False
        End If      ' If obj.GetType() = Me.GetType() Then

    End Function    ' Equals Ovewrride Method


    ''' <summary>
    ''' Override the GetHashCode method on the base class, System.Object, to
    ''' return a value that is consistent with the IComparable implemntation.
    ''' </summary>
    ''' <returns>
    ''' Return the hash code of the string returned by CreateComparand, the same
    ''' method that powers the IComparable implementation.
    ''' </returns>
    Public Overrides Function GetHashCode() As Integer

        Return CreateComparand(Me).GetHashCode()

    End Function    ' GetHashCode Ovewrride Method


    ''' <summary>
    ''' Override the ToString method on the base class, System.Object, display a
    ''' string representation of the object's properties.
    ''' </summary>
    ''' <returns></returns>
    Public Overrides Function ToString() As String

        Return String.Format(
            My.Resources.MSG_COLUMNNAMESANDLABELS_TOSTRING,                     ' Format Control String
            _strColumnName,                                                     ' Format Item 0: ColumnName = {0}
            _intColumnIndex,                                                    ' Format Item 1: ColumnIndex = {1}
            _strColumnValue,                                                    ' Format Item 2: ColumnValue = {2}
            ColumnLabel)                                                        ' Format Item 3: ColumnLabel = {3}

    End Function    ' ToString Ovewrride Method


    ''' <summary>
    ''' This method implements the IComparable interface for pairs of
    ''' ColumnNamesAndLabels objects.
    ''' </summary>
    ''' <param name="other">
    ''' Specify the other ColumnNamesAndLabels against which to compare the
    ''' current instance.
    ''' </param>
    ''' <returns>
    ''' The return value is an integer that conforms to the specifications of
    ''' the IComparable interface.
    ''' </returns>
    Public Function CompareTo(other As ColumnNamesAndLabels) As Integer Implements IComparable(Of ColumnNamesAndLabels).CompareTo

        Dim strComparandThis As String = CreateComparand(Me)
        Dim strComparandOther As String = CreateComparand(other)

        Return strComparandThis.CompareTo(strComparandOther)

    End Function    ' CompareTo Method of IComparable(Of ColumnNamesAndLabels Interface


    ''' <summary>
    ''' This provate shared method constructs a string from the table and column
    ''' name properties of a ColumnNamesAndLabels object.
    ''' </summary>
    ''' <param name="ColumnNamesAndLabels">
    ''' Pass in the ColumnNamesAndLabels instance from which to construct a
    ''' comparand string.
    ''' </param>
    ''' <returns>
    ''' The returned string is a concatenation of the table name and column name
    ''' separated by an underscore character.
    ''' </returns>
    Private Shared Function CreateComparand(ColumnNamesAndLabels As ColumnNamesAndLabels) As String

        Return String.Concat(ColumnNamesAndLabels._strTableName,
                             SpecialCharacters.UNDERSCORE_CHAR,
                             ColumnNamesAndLabels._strColumnName)

    End Function    ' CreateComparand Method, dependency of IComparable(Of ColumnNamesAndLabels Interface


    ''' <summary>
    ''' Instances of this class are strings that are guaranteed to be globally
    ''' unique. The guarantee is enforced by comparing the 
    ''' </summary>
    Public Class UniqueColumnName
        Implements IComparable(Of UniqueColumnName)

        Private Shared s_alstUsedNames As List(Of String)

        Private ReadOnly _strColumnName As String
        Private ReadOnly _strTableName As String

        Public Sub New()

        End Sub     ' ColumnName constructor (1 of 2)


        ''' <summary>
        ''' Construct a new instance based solely on a column name.
        ''' </summary>
        ''' <param name="pstrColumnName">
        ''' Pass in the column name to be validated against the list.
        ''' </param>
        ''' <exception cref="ArgumentNullException">
        ''' An ArgumentNullException exception arises when
        ''' <paramref name="pstrColumnName"/> is either a null reference or the
        ''' empty string.
        ''' </exception>
        Public Sub New(ByRef pstrColumnName As String)

            If String.IsNullOrEmpty(pstrColumnName) Then
                Throw New ArgumentNullException(NameOf(pstrColumnName))
            End If

            IsColumnNameGloballyUnique(pstrColumnName)

            _strColumnName = pstrColumnName

        End Sub     ' ColumnName constructor (2 of 3)


        ''' <summary>
        ''' Construct a new instance based on a column name, with a table name
        ''' to disambiguate like-named columns in two or more tables.
        ''' </summary>
        ''' <param name="pstrColumnName">
        ''' Pass in the column name to be validated against the list.
        ''' </param>
        ''' <param name="pstrTableName">
        ''' Pass in the table name to disambiguate like-named columns in two or
        ''' more tables. When the application uses only a single table, the
        ''' table name may be ignored by passing either a null reference
        ''' (Nothing in Visual Basic) or the empty string.
        ''' </param>
        ''' <exception cref="ArgumentNullException">
        ''' An ArgumentNullException exception arises when
        ''' <paramref name="pstrColumnName"/> is either a null reference or the
        ''' empty string.
        ''' </exception>
        Public Sub New(ByRef pstrColumnName As String,
                       ByRef pstrTableName As String)

            If String.IsNullOrEmpty(pstrColumnName) Then
                Throw New ArgumentNullException(NameOf(pstrColumnName))
            End If

            IsColumnNameGloballyUnique(pstrColumnName,
                                       pstrTableName)

            _strColumnName = pstrColumnName
            _strTableName = pstrTableName

        End Sub     ' ColumnName constructor (3 of 3)


        ''' <summary>
        ''' Gets the column name that was fed into the constructor.
        ''' </summary>
        ''' <returns>
        ''' The returned column name is guaranteed to be globally unique.
        ''' </returns>
        Public ReadOnly Property ColumnName
            Get
                Return _strColumnName
            End Get     ' ColumnName Getter Method
        End Property    ' ColumnName Property


        ''' <summary>
        ''' When specified, the table name becomes part of the global uniqueness
        ''' criteria.
        ''' </summary>
        ''' <returns>
        ''' The returned table name is as specified to the constructor. Table
        ''' names are not expected to be unique, and there is no practical way
        ''' to test them, so they are taken at face value.
        ''' </returns>
        Public ReadOnly Property TableName
            Get
                Return _strTableName
            End Get     ' TableName Getter Method
        End Property    ' TableName Property


        ''' <summary>
        ''' Implement the IComparable interface on a pair of ValidColumnName
        ''' objects.
        ''' </summary>
        ''' <param name="other">
        ''' Specify the other ValidColumnName object against which to compare
        ''' the current instance.
        ''' </param>
        ''' <returns>
        ''' The return value is an integer that conforms to the specifications of
        ''' the IComparable interface.
        ''' </returns>
        Public Function CompareTo(other As UniqueColumnName) As Integer Implements IComparable(Of UniqueColumnName).CompareTo
            Return CreateComparand(_strColumnName,
                                   _strTableName).CompareTo(CreateComparand(other._strColumnName,
                                                                            other._strTableName))
        End Function    ' CompareTo Method


        ''' <summary>
        ''' Override the Equals method on the base class, System.Object, to return a
        ''' value that is consistent with the IComparable implemntation.
        ''' </summary>
        ''' <param name="obj">
        ''' Pass in another object, which must be another ValidColumnName
        ''' instance if the result is to be meaningful.
        ''' </param>
        ''' <returns>
        ''' When <paramref name="obj"/> is an instance of ValidColumnName, the
        ''' return value is the result of testing their equality. Otherwise, the
        ''' return value is FALSE. Equality is evaluated by evaluating the equality
        ''' of the string returned by the same CreateComparand method that drives
        ''' the IComparable implemntation.
        ''' </returns>
        Public Overrides Function Equals(obj As Object) As Boolean

            If obj.GetType().Equals(Me.GetType()) Then
                Dim objOther As UniqueColumnName = obj
                Return CreateComparand(_strColumnName,
                                       _strTableName).Equals(CreateComparand(objOther._strColumnName,
                                                                             objOther._strTableName))
            Else
                Return False
            End If      ' If obj.GetType().Equals(Me.GetType()) Then

        End Function    ' Equals Method Override


        ''' <summary>
        ''' Override the GetHashCode method on the base class, System.Object, to
        ''' return a value that is consistent with the IComparable implemntation.
        ''' </summary>
        ''' <returns>
        ''' Return the hash code of the string returned by CreateComparand, the same
        ''' method that powers the IComparable implementation.
        ''' </returns>
        Public Overrides Function GetHashCode() As Integer
            Return CreateComparand(_strColumnName, _strTableName).GetHashCode()
        End Function    ' GetHashCode Method Override


        Public Overrides Function ToString() As String

            Return String.Format(My.Resources.UNIQUE_COLUMN_NAME_TOSTRING,      ' Format control string
                                 _strColumnName,                                ' Format Item 0: ColumnName = {0}
                                 _strTableName)                                 ' Format Item 1: ColumnLabel = {1}

        End Function    ' ToString Method Override


        ''' <summary>
        ''' Validate the column name, adding valid names to the list for use by
        ''' subsequent constructions.
        ''' </summary>
        ''' <param name="pstrColumnName">
        ''' Pass in the name of the column that was fed into the constructor.
        ''' </param>
        Private Shared Sub IsColumnNameGloballyUnique(ByRef pstrColumnName As String,
                                                      Optional ByRef pstrTableName As String = Nothing)

            Const INITIAL_CAPACITY = 8

            If s_alstUsedNames Is Nothing Then
#Disable Warning IDE0028 ' Simplify collection initialization.
                s_alstUsedNames = New List(Of String)(INITIAL_CAPACITY)
#Enable Warning IDE0028 ' Simplify collection initialization.
                s_alstUsedNames.Add(pstrColumnName)
            Else
                Dim strUniqueColumnName As String = CreateComparand(pstrColumnName,
                                                                    pstrTableName)

                If s_alstUsedNames.BinarySearch(strUniqueColumnName) <= ListInfo.BINARY_SEARCH_NOT_FOUND Then
                    s_alstUsedNames.Add(strUniqueColumnName)
                    s_alstUsedNames.Sort()
                Else
                    Throw New ArgumentOutOfRangeException(NameOf(pstrColumnName),
                                                          pstrColumnName,
                                                          My.Resources.ERRMSG_DUPLICATE_COLUMN_NAME)
                End If  ' If s_alstUsedNames.BinarySearch(strUniqueColumnName) >= ListInfo.BINARY_SEARCH_NOT_FOUND
            End If  ' If s_alstUsedNames Is Nothing Then

        End Sub     ' IsColumnNameGloballyUnique


        Private Shared Function CreateComparand(ByRef pstrColumnName As String,
                                                Optional ByRef pstrTableName As String = Nothing) As String

            If pstrTableName Is Nothing Then
                Return pstrColumnName
            Else
                Return String.Concat(pstrTableName,
                                     SpecialCharacters.UNDERSCORE_CHAR,
                                     pstrColumnName)
            End If  ' If pstrTableName Is Nothing Then

        End Function    ' CreateComparand
    End Class   ' UniqueColumnName
End Class   ' ColumnNamesAndLabels