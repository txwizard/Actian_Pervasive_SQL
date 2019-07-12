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

    Date       By Description
    ---------- -- --------------------------------------------------------------
    2019/07/12 DG Initial implementation.
    ============================================================================
*/

using System;

using WizardWrx;


namespace PSQLviaADOCS
{
    public static class Utils
    {
        /// <summary>
        /// Increment a static (shared in Visual Basic) value, returning the
        /// incremented value.
        /// </summary>
        /// <param name="pintIncrementThisValue">
        /// Pass in a reference to the shared value to increment and return.
        /// <para>Since the value is incremented, it must be passed explicitly
        /// by reference.
        /// </para>
        /// </param>
        /// <returns>
        /// The return value is the initial value of
        /// <paramref name="pintIncrementThisValue"/> plus one, which also becomes
        /// the new value of <paramref name="pintIncrementThisValue"/>.
        /// </returns>
        public static int SetToIncrementedValue ( ref int pintIncrementThisValue )
        {
            pintIncrementThisValue++;
            return pintIncrementThisValue;
        }   // public static int SetToIncrementedValue


        /// <summary>
        /// Increment a static (shared in Visual Basic) value, returning the
        /// incremented value.
        /// </summary>
        /// <param name="plngIncrementThisValue">
        /// Pass in a reference to the shared value to increment and return.
        /// <para>Since the value is incremented, it must be passed explicitly
        /// by reference.
        /// </para>
        /// </param>
        /// <returns>
        /// The return value is the initial value of
        /// <paramref name="plngIncrementThisValue"/> plus one, which also becomes
        /// the new value of <paramref name="plngIncrementThisValue"/>.
        /// </returns>
        public static long SetToIncrementedValue ( ref long plngIncrementThisValue )
        {
            plngIncrementThisValue++;
            return plngIncrementThisValue;
        }   // public static long SetToIncrementedValue
    }   // public static class Utils
}   // partial namespace PSQLviaADOCS