/*
    ============================================================================

    Module Name:        ColumnNamesAndLabels.cs

    Assembly:           PSQLviaADOCS

    Root Namespace:     PSQLviaADOCS

    Class:              ColumnNamesAndLabels

    Objective:          This class models a column name and its label,
                        optionally associating both with a database table.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version By Description
    ---------- ------- ---------------------------------------------------------
    2019/07/12 1.0.0.0 DG Initial implementation.

    2019/07/14 1.1.0.0 DG Make the implementation much more efficient.

    2019/07/16 1.2.0.0 DG Break the code into regions, and add missing XML code
                          documentation.

    2019/07/24 1.3.0.0 DG 1) Make ColumnValue a read/write member, and add
                             static methods to return lists of column (field)
                             names and values as separate arrays for feeding
                             into the ADODB record input and update methods.

                          2) Define a delegate that generates column values.

                          3) Set the AutoNumber and PrimaryKey flags to TRUE if
                             the delegate is defined and called.
    ============================================================================
*/


using System;

using System.Collections.Generic;

using WizardWrx;


namespace PSQLviaADOCS
{
    /// <summary>
    /// This is the signature of a delegate that generates the value of a data
    /// base column.
    /// </summary>
    /// <param name="pdbConnection">
    /// Pass in a reference to the open ADODB.Connection through which to access
    /// the database.
    /// </param>
    /// <param name="paobjInputs">
    /// Pass in am optional array of object variables from which to derive the
    /// return value. If there are none, the array may be null or empty.
    /// </param>
    /// <returns>
    /// The return value is an objectified representation of the value to assign
    /// to the column.
    /// </returns>
    public delegate object ColumnValueSetter (
        ADODB.Connection pdbConnection ,
        object [ ] paobjInputs = null );


    /// <summary>
    /// This class models a set of column names and labels. Each column has an
    /// auto-generated zero-based index number.
    /// </summary>
    public class ColumnNamesAndLabels : IComparable<ColumnNamesAndLabels>
    {
        #region Constructors
        /// <summary>
        /// To guarantee that all instances are initialized, the default
        /// constructor is marked private.
        /// </summary>
        private ColumnNamesAndLabels ( )
        {
        }   // private ColumnNamesAndLabels constructor (1 of 7)


        /// <summary>
        /// Construct an instance that identifies a table by name, has a value,
        /// and has an automatically generated index number.
        /// </summary>
        /// <param name="pucnColumnName">
        /// Specify the string containing the column name to be validated
        /// against the list. If the constructor succeeds, the column name is
        /// unique with respect to the table named by the
        /// <paramref name="pstrTableName"/> parameter.
        /// </param>
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        /// <param name="pobjColumnValue">
        /// Specify an objectified value to assign to the column, which may be
        /// used for reporting or other processing.
        /// </param>
        /// <param name="pfIsPrimparyKey">
        /// This argument is TRUE for any column (field) that is in the Primary
        /// Key, and, therefore, cannot be changed once set.
        /// </param>
        /// <param name="pfIsAutoNumber">
        /// This argument is TRUE for any column (field) that is antomatically
        /// sequenced by the data base engine, and, therefore, cannot be changed
        /// by a user.
        /// </param>
        public ColumnNamesAndLabels (
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            object pobjColumnValue ,
            bool pfIsPrimparyKey ,
            bool pfIsAutoNumber )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _objColumnValue = pobjColumnValue;
            _fIsPrimparyKeyColumn = pfIsPrimparyKey;
            _fIsAutoNumberColumn = pfIsAutoNumber;

            if ( s_fIndexIncrementIsEnabled )
            {
                _intColumnIndex = MoreMath.IncrementAndReturnNewValue ( ref s_intNextIndex );
            }   // if ( s_fIndexIncrementIsEnabled )
        }   // public ColumnNamesAndLabels constructor (2 of 7)
        
        
        /// <summary>
        /// Construct an instance that identifies a table by name, has a value,
        /// and has an automatically generated index number.
        /// </summary>
        /// <param name="pucnColumnName">
        /// Specify the string containing the column name to be validated
        /// against the list. If the constructor succeeds, the column name is
        /// unique with respect to the table named by the
        /// <paramref name="pstrTableName"/> parameter.
        /// </param>
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        /// <param name="pobjColumnValue">
        /// Specify an objectified value to assign to the column, which may be
        /// used for reporting or other processing.
        /// </param>
        /// <param name="pcolumnValueSetter">
        /// Pass in the routine to register as the value source of the column.
        /// </param>
        public ColumnNamesAndLabels (
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            ColumnValueSetter pcolumnValueSetter ,
            object [ ] paobjInputs ,
            ADODB.Connection pdbConnection )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _columnValueSetter = pcolumnValueSetter;

            //  ----------------------------------------------------------------
            //  I prefer the more verbose, and obvious, expression here to the
            //  terse, and less obvious, simplification suggested by the editor.
            //  ----------------------------------------------------------------

            if ( pcolumnValueSetter != null )
            {
                _objColumnValue = pcolumnValueSetter (
                    pdbConnection ,
                    paobjInputs );
                _fIsAutoNumberColumn = true;
                _fIsPrimparyKeyColumn = true;
            }   // if ( pcolumnValueSetter != null )

            if ( s_fIndexIncrementIsEnabled )
            {
                _intColumnIndex = MoreMath.IncrementAndReturnNewValue ( ref s_intNextIndex );
            }   // if ( s_fIndexIncrementIsEnabled )
        }   // public ColumnNamesAndLabels constructor (3 of 7)


        /// <summary>
        /// Construct an instance that identifies a table by name, has a value, and
        /// and has an explicitly assigned index number.
        /// </summary>
        /// <param name="pintColumnIndex">
        /// Specify the integer containing index to assign, which also disables
        /// automatic assignment for all subsequent instances.
        /// </param>
        /// <param name="pucnColumnName">
        /// Specify the string containing the column name to be validated
        /// against the list. If the constructor succeeds, the column name is
        /// unique with respect to the table named by the
        /// <paramref name="pstrTableName"/> parameter.
        /// </param>
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        /// <param name="pobjColumnValue">
        /// Specify an objectified value to assign to the column, which may be
        /// used for reporting or other processing.
        /// </param>
        /// <param name="pfIsPrimparyKey">
        /// This argument is TRUE for any column (field) that is in the Primary
        /// Key, and, therefore, cannot be changed once set.
        /// </param>
        /// <param name="pfIsAutoNumber">
        /// This argument is TRUE for any column (field) that is antomatically
        /// sequenced by the data base engine, and, therefore, cannot be changed
        /// by a user.
        /// </param>
        public ColumnNamesAndLabels (
            int pintColumnIndex ,
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            object pobjColumnValue ,
            bool pfIsPrimparyKey ,
            bool pfIsAutoNumber )
        {
            _intColumnIndex = pintColumnIndex;
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _objColumnValue = pobjColumnValue;
            _fIsPrimparyKeyColumn = pfIsPrimparyKey;
            _fIsAutoNumberColumn = pfIsAutoNumber;

            s_fIndexIncrementIsEnabled = false;
        }   // public ColumnNamesAndLabels constructor (4 of 7)


        /// <summary>
        /// Construct an instance that identifies a table by name, has a value, and
        /// and has an explicitly assigned index number.
        /// </summary>
        /// <param name="pintColumnIndex">
        /// Specify the integer containing index to assign, which also disables
        /// automatic assignment for all subsequent instances.
        /// </param>
        /// <param name="pucnColumnName">
        /// Specify the string containing the column name to be validated
        /// against the list. If the constructor succeeds, the column name is
        /// unique with respect to the table named by the
        /// <paramref name="pstrTableName"/> parameter.
        /// </param>
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        /// <param name="pobjColumnValue">
        /// Specify an objectified value to assign to the column, which may be
        /// used for reporting or other processing.
        /// </param>
        /// <param name="pcolumnValueSetter">
        /// Pass in the routine to register as the value source of the column.
        /// </param>
        public ColumnNamesAndLabels (
            int pintColumnIndex ,
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            ColumnValueSetter pcolumnValueSetter ,
            object [ ] paobjInputs ,
            ADODB.Connection pdbConnection )
        {
            _intColumnIndex = pintColumnIndex;
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _columnValueSetter = pcolumnValueSetter;

            //  ----------------------------------------------------------------
            //  I prefer the more verbose, and obvious, expression here to the
            //  terse, and less obvious, simplification suggested by the editor.
            //  ----------------------------------------------------------------

#pragma warning disable
            if ( pcolumnValueSetter != null )
            {
                _objColumnValue = pcolumnValueSetter (
                    pdbConnection ,
                    paobjInputs );
            }   // if ( pcolumnValueSetter != null )
#pragma warning restore

            if ( s_fIndexIncrementIsEnabled )
            {
                _intColumnIndex = MoreMath.IncrementAndReturnNewValue ( ref s_intNextIndex );
            }   // if ( s_fIndexIncrementIsEnabled )
        }   // public ColumnNamesAndLabels constructor (5 of 7)


        /// <summary>
        /// Construct an instance that has a column name and label, along with an
        /// automatically generated index. The table and value proeprties are
        /// omitted, and remain null, although the value may be subsequently set.
        /// </summary>
        /// <param name="pucnColumnName">
        /// Specify the string containing the column name to be validated
        /// against the list. If the constructor succeeds, the column name is
        /// unique with respect to the table named by the
        /// <paramref name="pstrTableName"/> parameter of the 
        /// <paramref name="pucnColumnName"/> constructor.
        /// </param>
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        /// <param name="pfIsPrimparyKey">
        /// This argument is TRUE for any column (field) that is in the Primary
        /// Key, and, therefore, cannot be changed once set.
        /// </param>
        /// <param name="pfIsAutoNumber">
        /// This argument is TRUE for any column (field) that is antomatically
        /// sequenced by the data base engine, and, therefore, cannot be changed
        /// by a user.
        /// </param>
        public ColumnNamesAndLabels (
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            bool pfIsPrimparyKey ,
            bool pfIsAutoNumber )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _fIsPrimparyKeyColumn = pfIsPrimparyKey;
            _fIsAutoNumberColumn = pfIsAutoNumber;

            if ( s_fIndexIncrementIsEnabled )
            {
                _intColumnIndex = MoreMath.IncrementAndReturnNewValue ( ref s_intNextIndex );
            }   // if ( s_fIndexIncrementIsEnabled )
        }   // public ColumnNamesAndLabels constructor (6 of 7)


        /// <summary>
        /// Construct an instance that has a column name and label, along with an
        /// automatically generated index. The table and value proeprties are
        /// omitted, and remain null, although the value may be subsequently set.
        /// </summary>
        /// <param name="pintColumnIndex">
        /// Specify the integer containing index to assign, which also disables
        /// automatic assignment for all subsequent instances.
        /// </param>
        /// <param name="pucnColumnName">
        /// Specify the string containing the column name to be validated
        /// against the list. If the constructor succeeds, the column name is
        /// unique with respect to the table named by the
        /// <paramref name="pstrTableName"/> parameter.
        /// </param>
        /// <param name="pcolumnValueSetter">
        /// Pass in the routine to register as the value source of the column.
        /// </param>
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        /// <param name="pfIsPrimparyKey">
        /// This argument is TRUE for any column (field) that is in the Primary
        /// Key, and, therefore, cannot be changed once set.
        /// </param>
        /// <param name="pfIsAutoNumber">
        /// This argument is TRUE for any column (field) that is antomatically
        /// sequenced by the data base engine, and, therefore, cannot be changed
        /// by a user.
        /// </param>
        public ColumnNamesAndLabels (
            int pintColumnIndex ,
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            bool pfIsPrimparyKey ,
            bool pfIsAutoNumber )
        {
            _intColumnIndex = pintColumnIndex;
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _fIsPrimparyKeyColumn = pfIsPrimparyKey;
            _fIsAutoNumberColumn = pfIsAutoNumber;

            s_fIndexIncrementIsEnabled = false;
        }   // public ColumnNamesAndLabels constructor (7 of 7)
        #endregion  // Constructors


        #region Public Instance Properties
        /// <summary>
        /// Get the automatically generated or explicitly set column index.
        /// </summary>
        public int ColumnIndex
        {
            get
            {
                return _intColumnIndex;
            }   // public int ColumnIndex getter method
        }   // public read-only int ColumnIndex property


        /// <summary>
        /// Get the column label that was passed into the constructor.
        /// </summary>
        public string ColumnLabel
        {
            get
            {
                return _strColumnLabel;
            }   // public string ColumnLabel property getter method
        }   // public read-only string ColumnLabel property


        /// <summary>
        /// Get the string representation of the Column Name property from the
        /// UniqueColumnName member stored in the instance.
        /// </summary>
        public string ColumnName
        {
            get
            {
                return _ucnColumnName.ColumnName;
            }   // public string ColumnName property getter method
        }   // public read-only string ColumnName property


        /// <summary>
        /// Get or set the string representation of the Column Value property 
        /// stored in the instance.
        /// </summary>
        public object ColumnValue
        {
            get
            {
                return _objColumnValue;
            }   // public string ColumnValue property getter method

            set
            {
                _objColumnValue = value;
            }   // public string ColumnValue property setter method
        }   // public read-write string ColumnValue property


        /// <summary>
        /// Get the Boolean IsAutoNumber flag. When True, the associated column
        /// cannot be changed by a user.
        /// </summary>
        public bool IsAutoNumberColumn
        {
            get
            {
                return _fIsAutoNumberColumn;
            }   // public bool IsAutoNumberColumn property getter method
        }   // public read-only bool IsAutoNumberColumn


        /// <summary>
        /// Get the Boolean IsPrimaryKey flag. When True, the associated column
        /// cannot be changed by a user.
        /// </summary>
        public bool IsPrimaryKeyColumn
        {
            get
            {
                return _fIsPrimparyKeyColumn;
            }   // public read-only bool IsPrimaryKeyColumn property
        }   // public read-only bool IsPrimaryKeyColumn property getter method


        /// <summary>
        /// Get the string representation of the Table Name stored in the
        /// instance.
        /// </summary>
        public string TableName
        {
            get
            {
                return _ucnColumnName.TableName;
            }   // public string TableName property getter method
        }   // public read-only string TableName property


        /// <summary>
        /// Get the signature of the delegate that initializes the value of the
        /// object when its constructor is called. This value is stored for the
        /// record only, since the constructor gets a duplicate reference, too.
        /// </summary>
        public ColumnValueSetter ValueSetter
        {
            get
            {
                return _columnValueSetter;
            }   // public ColumnValueSetter ValueSetter setter method
        }   // public read-only ColumnValueSetter ValueSetter property
        #endregion  // Public Instance Properties


        #region Overridden Base Class Methods
        /// <summary>
        /// Override the Equals method on the base class, System.Object, to return a
        /// value that is consistent with the IComparable implemntation.
        /// </summary>
        /// <param name="obj">
        /// Pass in another object, which must be another ColumnNamesAndLabels
        /// instance if the result is to be meaningful.
        /// </param>
        /// <returns>
        /// When <paramref name="obj"/> is an instance of ColumnNamesAndLabels, the
        /// return value is the result of testing their equality. Otherwise, the
        /// return value is FALSE. Equality is evaluated by evaluating the equality
        /// of the string returned by the same CreateComparand method that drives
        /// the IComparable implemntation.
        /// </returns>
        public override bool Equals ( object obj )
        {
            if ( obj.GetType ( ) == this.GetType ( ) )
            {
                ColumnNamesAndLabels objOther = obj as ColumnNamesAndLabels;
                return CreateComparand ( this ).Equals ( CreateComparand ( objOther ) );
            }   // TRUE (anticipated outcome) block, if ( obj.GetType ( ) == this.GetType ( ) )
            else
            {
                return false;
            }   // FALSE (unanticipated outcome) block, if ( obj.GetType ( ) == this.GetType ( ) )
        }   // public override bool Equals operator


        /// <summary>
        /// Override the GetHashCode method on the base class, System.Object, to
        /// return a value that is consistent with the IComparable implemntation.
        /// </summary>
        /// <returns>
        /// Return the hash code of the string returned by CreateComparand, the same
        /// method that powers the IComparable implementation.
        /// </returns>
        public override int GetHashCode ( )
        {
            return CreateComparand ( this ).GetHashCode ( );
        }   // public override int GetHashCode method


        /// <summary>
        /// Override the ToString method on the base class, System.Object, display a
        /// string representation of the object's properties.
        /// </summary>
        /// <returns>
        /// Property values are substituted into the following template:
        /// ColumnName = {0}, ColumnIndex = {1}, ColumnValue = {2}, ColumnLabel = {3}.
        /// </returns>
        public override string ToString ( )
        {
            return string.Format (
                Properties.Resources.MSG_COLUMNNAMESANDLABELS_TOSTRING ,        // Format Control String    
                StringTricks.DisplayNullSafely ( _ucnColumnName.TableName ) ,   // Format Item 0: TableName = {0}
                _intColumnIndex ,                                               // Format Item 2: ColumnIndex = {1}    
                _ucnColumnName.ColumnName ,                                     // Format Item 1: ColumnName = {2}
                _objColumnValue ,                                               // Format Item 3: ColumnValue = {3}    
                _strColumnLabel ,                                               // Format Item 4: ColumnLabel = {4}
                _fIsAutoNumberColumn ,                                          // Format Item 5: IsAutoNumberKeyColumn = {5}
                _fIsPrimparyKeyColumn );                                        // Format Item 6: IsPrimaryKeyColumn = {6}
        }   // public override string ToString
        #endregion  // Overridden Base Class Methods


        #region IComparable Interface Implementation
        /// <summary>
        /// This method implements the IComparable interface for pairs of
        /// ColumnNamesAndLabels objects.
        /// </summary>
        /// <param name="other">
        /// Specify the other ColumnNamesAndLabels against which to compare the
        /// current instance.
        /// </param>
        /// <returns>
        /// The return value is an integer that conforms to the specifications of
        /// the IComparable interface.
        /// </returns>
        /// <remarks>
        /// Treat this method as infrastructure; the framework calls it when
        /// necessary, such as when a list is being sorted or searched. User
        /// code cannot call this method directly, which is why it has no
        /// explicit scope.
        /// </remarks>
        int IComparable<ColumnNamesAndLabels>.CompareTo ( ColumnNamesAndLabels other )
        {
            string strComparandThis = CreateComparand ( this );
            string strComparandOther = CreateComparand ( other );

            return strComparandThis.CompareTo ( strComparandOther );
        }   // int IComparable<ColumnNamesAndLabels>.CompareTo
        #endregion  // IComparable Interface Implementation


        #region Public Static Methods
        /// <summary>
        /// Call this method to get a list of column (field) names for use with
        /// the AddNew and Update methods on an ADODB Recordset object.
        /// </summary>
        /// <param name="paobjColumnNamesAndLabels">
        /// Pass in a reference to the initialized array of ColumnNamesAndLabels
        /// objects from which to extract the list of column names.
        /// </param>
        /// <returns>
        /// The return value is an array of strings, each element of which is
        /// the name of a column (field) in the Recordset with which it is used.
        /// </returns>
        public static string [ ] GetColumnNamesArray ( ColumnNamesAndLabels [ ] paobjColumnNamesAndLabels )
        {
            if ( paobjColumnNamesAndLabels != null )
            {
                if ( paobjColumnNamesAndLabels.Length > ArrayInfo.ARRAY_IS_EMPTY )
                {
                    int intItemCount = paobjColumnNamesAndLabels.Length;
                    string [ ] rastrOutputArray = new string [ intItemCount ];

                    for ( int intCurrentItem = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                              intCurrentItem < intItemCount ;
                              intCurrentItem++ )
                    {
                        rastrOutputArray [ intCurrentItem ] = paobjColumnNamesAndLabels [ intCurrentItem ].ColumnName;
                    }   // for ( int intCurrentItem = ArrayInfo.ARRAY_FIRST_ELEMENT ; intCurrentItem < intItemCount ; intCurrentItem++ )

                    return rastrOutputArray;
                }   // TRUE (anticipated outcome) block, if ( aobjColumnNamesAndLabels.Length > ArrayInfo.ARRAY_IS_EMPTY )
                else
                {   // Since all ArgumentException exceptions require a Message parameter, the message may as well include the parameter name.
                    throw new ArgumentException (
                        string.Format (
                            WizardWrx.Common.Properties.Resources.ERRMSG_ARRAY_IS_EMPTY ,
                            nameof ( paobjColumnNamesAndLabels ) ) );
                }   // FALSE (unanticipated outcome) block, if ( aobjColumnNamesAndLabels.Length > ArrayInfo.ARRAY_IS_EMPTY )
            }   // TRUE (anticipated outcome) block, if ( aobjColumnNamesAndLabels != null )
            else
            {   // The default message is self-explanatory, and if any question remains, the exception reporter spells it out.
                throw new ArgumentNullException ( nameof ( paobjColumnNamesAndLabels ) );
            }   // FALSE (unanticipated outcome) block, if ( aobjColumnNamesAndLabels != null )
        }   // public static string [ ] GetColumnNamesArray method


        /// <summary>
        /// Call this method to get a list of column (field) values for use with
        /// the AddNew and Update methods on an ADODB Recordset object.
        /// </summary>
        /// <param name="paobjColumnNamesAndLabels">
        /// Pass in a reference to the initialized array of ColumnNamesAndLabels
        /// objects from which to extract the list of column values.
        /// </param>
        /// <returns>
        /// The return value is an array of strings, each element of which is
        /// the values of a column (field) in the Recordset with which it is
        /// used.
        /// </returns>
        public static object [ ] GetColumnValuesArray ( ColumnNamesAndLabels [ ] paobjColumnNamesAndLabels )
        {
            if ( paobjColumnNamesAndLabels != null )
            {
                if ( paobjColumnNamesAndLabels.Length > ArrayInfo.ARRAY_IS_EMPTY )
                {
                    int intItemCount = paobjColumnNamesAndLabels.Length;
                    object [ ] rastrOutputArray = new string [ intItemCount ];

                    for ( int intCurrentItem = ArrayInfo.ARRAY_FIRST_ELEMENT ;
                              intCurrentItem < intItemCount ;
                              intCurrentItem++ )
                    {
                        rastrOutputArray [ intCurrentItem ] = paobjColumnNamesAndLabels [ intCurrentItem ].ColumnValue;
                    }   // for ( int intCurrentItem = ArrayInfo.ARRAY_FIRST_ELEMENT ; intCurrentItem < intItemCount ; intCurrentItem++ )

                    return rastrOutputArray;
                }   // TRUE (anticipated outcome) block, if ( aobjColumnNamesAndLabels.Length > ArrayInfo.ARRAY_IS_EMPTY )
                else
                {   // Since all ArgumentException exceptions require a Message parameter, the message may as well include the parameter name.
                    throw new ArgumentException (
                        string.Format (
                            WizardWrx.Common.Properties.Resources.ERRMSG_ARRAY_IS_EMPTY ,
                            nameof ( paobjColumnNamesAndLabels ) ) );
                }   // FALSE (unanticipated outcome) block, if ( aobjColumnNamesAndLabels.Length > ArrayInfo.ARRAY_IS_EMPTY )
            }   // TRUE (anticipated outcome) block, if ( aobjColumnNamesAndLabels != null )
            else
            {   // The default message is self-explanatory, and if any question remains, the exception reporter spells it out.
                throw new ArgumentNullException ( nameof ( paobjColumnNamesAndLabels ) );
            }   // FALSE (unanticipated outcome) block, if ( aobjColumnNamesAndLabels != null )
        }   // public static object [ ] GetColumnValuesArray method


        /// <summary>
        /// Call this static method to return the global IndexIncrementIsEnabled
        /// flag state.
        /// </summary>
        /// <returns>
        /// The return value is the current value of static class member
        /// s_fIndexIncrementIsEnabled.
        /// </returns>
        public static bool IsIndexIncrementEnabled ( )
        {
            return s_fIndexIncrementIsEnabled;
        }   // public static bool IsIndexIncrementEnabled
        #endregion  // Public Static Methods


        #region Private Static Methods
        /// <summary>
        /// This private static (Shared in Visual Basic) method constructs a
        /// string from the table and column name properties of a
        /// ColumnNamesAndLabels object.
        /// </summary>
        /// <param name="columnNamesAndLabels">
        /// Pass in the ColumnNamesAndLabels instance from which to construct a
        /// comparand string.
        /// </param>
        /// <returns>
        /// The returned string is a concatenation of the table name and column name
        /// separated by an underscore character.
        /// </returns>
        private static string CreateComparand ( ColumnNamesAndLabels columnNamesAndLabels )
        {
            return string.Concat (
                columnNamesAndLabels._ucnColumnName.TableName ,
                SpecialCharacters.UNDERSCORE_CHAR ,
                columnNamesAndLabels._ucnColumnName.ColumnName );
        }   // private static string CreateComparand
        #endregion  // Private Static Methods


        #region Private Instance Storage
        private readonly UniqueColumnName _ucnColumnName;
        private readonly ColumnValueSetter _columnValueSetter;
        private readonly int _intColumnIndex = WizardWrx.ArrayInfo.ARRAY_INVALID_INDEX;
        private readonly string _strColumnLabel;
        private readonly bool _fIsPrimparyKeyColumn;
        private readonly bool _fIsAutoNumberColumn;
        private object _objColumnValue;
        #endregion  // Private Instance Storage


        #region Private Static (Class) Storage
        private static int s_intNextIndex = WizardWrx.ArrayInfo.ARRAY_INVALID_INDEX;
        private static bool s_fIndexIncrementIsEnabled = true;
        #endregion  // Private Static (Class) Storage


        #region Nested Public Class UniqueColumnName
        /// <summary>
        /// Instances of this class are strings that are guaranteed to be
        /// globally unique. The guarantee is enforced by comparing the 
        /// combination of the table and column names against an internal
        /// list of names registered by previous constructor calls.
        /// </summary>
        public class UniqueColumnName : IComparable<UniqueColumnName>
        {
            #region UniqueColumnName Constructors
            /// <summary>
            /// To guarantee that all instances are initialized, the default
            /// constructor is marked private.
            /// </summary>
            private UniqueColumnName ( )
            {
            }   // private UniqueColumnName constructor (1 of 3)


            /// <summary>
            /// Construct a new instance based solely on a column name.
            /// </summary>
            /// <param name="pstrColumnName">
            /// Specify the string containing the column name to be validated
            /// against the list.
            /// </param>
            public UniqueColumnName ( string pstrColumnName )
            {
                if ( string.IsNullOrEmpty ( pstrColumnName ) )
                    throw new ArgumentNullException ( nameof ( pstrColumnName ) );

                IsColumnNameGloballyUnique ( pstrColumnName );
                ColumnName = pstrColumnName;
            }   // public UniqueColumnName constructor (2 of 3)


            /// <summary>
            /// Construct a new instance based on a column name, with a table name
            /// to disambiguate like-named columns in two or more tables.
            /// </summary>
            /// <param name="pstrColumnName">
            /// Specify the string containing the column name to be validated
            /// against the list.
            /// </param>
            /// <param name="pstrTableName">
            /// Specify the string containing the table name to disambiguate
            /// like-named columns in two or more tables.
            /// 
            /// When the application uses only a single table, the table name
            /// may be ignored by passing either a null reference (Nothing in
            /// Visual Basic) or the empty string.
            /// </param>
            public UniqueColumnName (
                string pstrColumnName ,
                string pstrTableName )
            {
                if ( string.IsNullOrEmpty ( pstrColumnName ) )
                    throw new ArgumentNullException ( nameof ( pstrColumnName ) );

                IsColumnNameGloballyUnique (
                    pstrColumnName ,
                    pstrTableName );
                ColumnName = pstrColumnName;
                TableName = pstrTableName;
            }   // public UniqueColumnName constructor (3 of 3)
            #endregion  // UniqueColumnName Constructors


            #region UniqueColumnName Public Properties
            /// <summary>
            /// Get the ColumnName string stored in the instance.
            /// </summary>
            public string ColumnName
            {
                get;
            }   // public string ColumnName property


            /// <summary>
            /// Get the TableName string stored in the instance.
            /// </summary>
            public string TableName
            {
                get;
            }   // public string TableName property
            #endregion  // UniqueColumnName Public Properties


            #region UniqueColumnName Overridden Base Class Methods
            /// <summary>
            /// Override the Equals method on the base class, System.Object, to return a
            /// value that is consistent with the IComparable implemntation.
            /// </summary>
            /// <param name="obj">
            /// Pass in another object, which must be another ValidColumnName
            /// instance if the result is to be meaningful.
            /// </param>
            /// <returns>
            /// When <paramref name="obj"/> is an instance of ValidColumnName, the
            /// return value is the result of testing their equality. Otherwise, the
            /// return value is FALSE. Equality is evaluated by evaluating the equality
            /// of the string returned by the same CreateComparand method that drives
            /// the IComparable implemntation.
            /// </returns>
            public override bool Equals ( object obj )
            {
                if ( obj.GetType ( ).Equals ( this.GetType ( ) ) )
                {
                    UniqueColumnName objOther = obj as UniqueColumnName;
                    return CreateComparand (
                        ColumnName ,
                        TableName ).Equals (
                        CreateComparand (
                            objOther.ColumnName ,
                            objOther.TableName ) );
                }   // TRUE (anticipated outcome) block, if ( obj.GetType ( ).Equals ( this.GetType ( ) ) )
                else
                {
                    return false;
                }   // FALSE (unanticipated outcome) block, if ( obj.GetType ( ).Equals ( this.GetType ( ) ) )
            }   // public override bool Equals


            /// <summary>
            /// Override the GetHashCode method on the base class, System.Object, to
            /// return a value that is consistent with the IComparable implemntation.
            /// </summary>
            /// <returns>
            /// Return the hash code of the string returned by CreateComparand, the same
            /// method that powers the IComparable implementation.
            /// </returns>
            public override int GetHashCode ( )
            {
                return CreateComparand ( ColumnName , TableName ).GetHashCode ( );
            }   // public override int GetHashCode


            /// <summary>
            /// Override the GetHashCode method on the base class,
            /// System.Object, to return a value that is consistent with the
            /// IComparable implemntation.
            /// </summary>
            /// <returns>
            /// Return a formatted string that names the two properties and
            /// their values.
            /// </returns>
            public override string ToString ( )
            {
                return string.Format (
                    Properties.Resources.UNIQUE_COLUMN_NAME_TOSTRING ,          // Format control string
                    ColumnName ,                                                // Format Item 0: ColumnName = {0}
                    TableName );                                                // Format Item 1: ColumnLabel = {1}
            }   // public override string ToString
            #endregion  // UniqueColumnName Overridden Base Class Methods


            #region UniqueColumnName IComparable Interface Implementation
            /// <summary>
            /// Implement the IComparable interface on a pair of ValidColumnName
            /// objects.
            /// </summary>
            /// <param name="other">
            /// Specify the other ValidColumnName object against which to compare
            /// the current instance.
            /// </param>
            /// <returns>
            /// The return value is an integer that conforms to the
            /// specifications of the IComparable interface.
            /// </returns>
            /// <remarks>
            /// Treat this method as infrastructure; the framework calls it when
            /// necessary, such as when a list is being sorted or searched. User
            /// code cannot call this method directly, which is why it has no
            /// explicit scope.
            /// </remarks>
            int IComparable<UniqueColumnName>.CompareTo ( UniqueColumnName other )
            {
                return CreateComparand (
                    ColumnName ,
                    TableName ).CompareTo ( CreateComparand (
                        other.ColumnName ,
                        other.TableName ) );
            }   // int IComparable<UniqueColumnName>.CompareTo
            #endregion  // UniqueColumnName IComparable Interface Implementation


            #region UniqueColumnName Private Static Methods and Storage
            /// <summary>
            /// When <paramref name="pstrTableName"/> is null, the comparand
            /// consists only of the <paramref name="pstrColumnName"/>.
            /// </summary>
            /// <param name="pstrColumnName">
            /// Pass in a reference to a string, which cannot be empty, that
            /// represents the column name.
            /// </param>
            /// <param name="pstrTableName">
            /// When the application references two or more tables, the table
            /// name is required to disambiguate column names. Otherwise, this
            /// value may be left empty, or even null.
            /// </param>
            /// <returns>
            /// The return value is a string constructed from the table name, if
            /// present, and the column name. If the table name is absent, the
            /// column name is treated as sufficient, and is returned by itself.
            /// </returns>
            private static string CreateComparand (
                string pstrColumnName ,
                string pstrTableName )
            {
                if ( pstrTableName == null )
                    return pstrColumnName;
                else
                    return string.Concat (
                        pstrTableName ,
                        SpecialCharacters.UNDERSCORE_CHAR ,
                        pstrColumnName );
            }   // private static string CreateComparand


            /// <summary>
            /// Update the list with each unique item, and throw when the item
            /// is a duplicate.
            /// </summary>
            /// <param name="pstrColumnName">
            /// Every item must have a column name.
            /// </param>
            /// <param name="pstrTableName">
            /// Unless the application processes two or more tables, the table
            /// name is optional, and may be left null.
            /// </param>
            private static void IsColumnNameGloballyUnique (
                string pstrColumnName ,
                string pstrTableName = null )
            {
                const int INITIAL_CAPACITY = 8;

                if ( s_alstUsedNames == null )
                {   // Defer initialization of the list until it is needed.
                    s_alstUsedNames = new List<string> ( INITIAL_CAPACITY )
                    {   // The initializer also inserts the first item.
                        pstrColumnName
                    };  // s_alstUsedNames = new List<string> ( INITIAL_CAPACITY )
                }   // TRUE (First pass) block, if ( s_alstUsedNames == null )
                else
                {   // The list contains at least one item. Construct a candidate.
                    string strUniqueColumnName = CreateComparand (
                        pstrColumnName ,
                        pstrTableName );

                    if ( s_alstUsedNames.BinarySearch ( strUniqueColumnName ) <= ListInfo.BINARY_SEARCH_NOT_FOUND )
                    {   // The new item is unique. Append it, then sort the list.
                        s_alstUsedNames.Add ( strUniqueColumnName );
                        s_alstUsedNames.Sort ( );
                    }   // TRUE (anticipated outcome) block, if ( s_alstUsedNames.BinarySearch ( strUniqueColumnName ) <= ListInfo.BINARY_SEARCH_NOT_FOUND )
                    else
                    {   // The item is a duplicate. Throw an exception.
                        throw new ArgumentOutOfRangeException (
                            nameof ( pstrColumnName ) ,
                            pstrColumnName ,
                            Properties.Resources.ERRMSG_DUPLICATE_COLUMN_NAME );
                    }   // FALSE (unanticipated outcome) block, if ( s_alstUsedNames.BinarySearch ( strUniqueColumnName ) <= ListInfo.BINARY_SEARCH_NOT_FOUND )
                }   // FALSE (Subsequent passes) block, if ( s_alstUsedNames == null )
            }   // private static void IsColumnNameGloballyUnique


            private static List<string> s_alstUsedNames;
            #endregion  // UniqueColumnName Private Static Methods and Storage
        }   // public class UniqueColumnName
    }   // public class ColumnNamesAndLabels
    #endregion  // Nested Public Class UniqueColumnName
}   // partial namespace PSQLviaADOCS