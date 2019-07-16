/*
    ============================================================================

    Assembly:           PSQLviaADOCS

    Root Namespace:     PSQLviaADOandVB

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
    ============================================================================
*/

using System;

using System.Collections.Generic;

using WizardWrx;


namespace PSQLviaADOCS
{
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
        }   // private ColumnNamesAndLabels constructor (1 of 5)


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
        /// <param name="pstrColumnValue">
        /// Specify a string representation of a value to assign to the column,
        /// which may be used for reporting or other processing.
        /// </param>
        public ColumnNamesAndLabels (
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            string pstrColumnValue )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _strColumnValue = pstrColumnValue;

            _intColumnIndex = Utils.SetToIncrementedValue ( ref s_intNextIndex );
        }   // public ColumnNamesAndLabels constructor (2 of 5)


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
        /// <param name="pstrColumnValue">
        /// Specify a string representation of a value to assign to the column,
        /// which may be used for reporting or other processing.
        /// </param>
        public ColumnNamesAndLabels (
            int pintColumnIndex ,
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel ,
            string pstrColumnValue )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;
            _strColumnValue = pstrColumnValue;

            _intColumnIndex = pintColumnIndex;
            s_fIndexIncrementIsEnabled = false;
        }   // public ColumnNamesAndLabels constructor (3 of 5)


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
        public ColumnNamesAndLabels (
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;

            _intColumnIndex = Utils.SetToIncrementedValue ( ref s_intNextIndex );
        }   // public ColumnNamesAndLabels constructor (4 of 5)


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
        /// <param name="pstrColumnLabel">
        /// Specify a string containing the column label, which is not
        /// sanity-checked for uniqueness.
        /// </param>
        public ColumnNamesAndLabels (
            int pintColumnIndex ,
            UniqueColumnName pucnColumnName ,
            string pstrColumnLabel )
        {
            _ucnColumnName = pucnColumnName;
            _strColumnLabel = pstrColumnLabel;

            _intColumnIndex = pintColumnIndex;
            s_fIndexIncrementIsEnabled = false;
        }   // public ColumnNamesAndLabels constructor (5 of 5)
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
        }   // public int ColumnIndex property


        /// <summary>
        /// Get the column label that was passed into the constructor.
        /// </summary>
        public string ColumnLabel
        {
            get
            {
                return _strColumnLabel;
            }   // public string ColumnLabel property getter method
        }   // public string ColumnLabel property


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
        }   // public string ColumnName property


        /// <summary>
        /// Get the string representation of the Column Value property stored in
        /// the instance.
        /// </summary>
        public string ColumnValue
        {
            get
            {
                return _strColumnValue;
            }   // public string ColumnValue property getter method
        }   // public string ColumnValue property


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
        }   // public string TableName property
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
                _ucnColumnName.ColumnName ,                                     // Format Item 0: ColumnName = {1}
                _intColumnIndex ,                                               // Format Item 1: ColumnIndex = {2}    
                _strColumnValue ,                                               // Format Item 2: ColumnValue = {3}    
                _strColumnLabel );                                              // Format Item 3: ColumnLabel = {4}
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
        /// Call this static method to return the global IndexIncrementIsEnabled
        /// flag state.
        /// </summary>
        /// <returns>
        /// The return value is the current value of static class member
        /// s_fIndexIncrementIsEnabled.
        /// </returns>
        public static bool GetIndexIncrementIsEnabled ( )
        {
            return s_fIndexIncrementIsEnabled;
        }   // public static bool GetIndexIncrementIsEnabled
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
        private readonly string _strColumnValue;
        private readonly string _strColumnLabel;
        private readonly int _intColumnIndex = WizardWrx.ArrayInfo.ARRAY_INVALID_INDEX;
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