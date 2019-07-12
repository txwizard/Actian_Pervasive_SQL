/*
    ============================================================================

    Assembly Name:        PSQLviaADOCS

    Root Namespace Name:  PSQLviaADOandVB

    Module Name:          Module1

    Module Objective:     This application demonstrates basic CRUD operations,
                          which were once also called ACID operations, on a 
                          Pervacive SQL (BTrieve) data base, using the ADODB
                          data provider through COM interop.

                          Sub Main() Of this Module Is the entry point routine
                          of a Visual Basic console application.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------
'
    Date       By Description
    ---------- -- --------------------------------------------------------------
    2019/07/12 DG Initial implementation, including creation of a handful of
                  core helper routines that provide a Visual Basic
                  implementation of my tried and true console mode program
                  skeleton.
    ============================================================================
*/


using System;
using System.Collections.Generic;
using System.Text;
using WizardWrx;
using WizardWrx.ConsoleAppAids3;

namespace PSQLviaADOCS
{
    class Program
    {
        static void Main ( string [ ] args )
        {
            ConsoleAppStateManager csm = ConsoleAppStateManager.GetTheSingleInstance ( );
            csm.DisplayBOJMessage ( );

            try
            {
                DoTask ( );
            }
            catch ( Exception ex )
            {
                csm.BaseStateManager.AppExceptionLogger.ReportException ( ex );
            }
            finally
            {
                csm.DisplayEOJMessage ( );

                if ( Environment.ExitCode == MagicNumbers.ERROR_SUCCESS )
                {
                    csm.NormalExit ( ConsoleAppStateManager.NormalExitAction.Timed );
                }   // TRUE (anticipated outcome) block, if ( Environment.ExitCode == MagicNumbers.ERROR_SUCCESS )
                else
                {
                    csm.ErrorExit ( ( uint ) Environment.ExitCode );
                }   // FALSE (unanticipated outcome) block, if ( Environment.ExitCode == MagicNumbers.ERROR_SUCCESS )
            }   // Try/Catch/Finally block
        }   // static void Main


        private static void DoTask ( )
        {
            throw new NotImplementedException ( );
        }
    }   // class Program
}   // partial amespace PSQLviaADOCS