﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace PSQLviaADOCS.Properties {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "15.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("PSQLviaADOCS.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Duplicate column name.
        /// </summary>
        internal static string ERRMSG_DUPLICATE_COLUMN_NAME {
            get {
                return ResourceManager.GetString("ERRMSG_DUPLICATE_COLUMN_NAME", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {1}Table name {0} is invalid.{1}.
        /// </summary>
        internal static string ERRMSG_INVALID_NAME {
            get {
                return ResourceManager.GetString("ERRMSG_INVALID_NAME", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Line {0} in {1} table schema file {2} is invalid.{6}    Expected Column Count = {3}{6}    Actual Column Count   = {4}{6}    Text of Invalid Line  = {5}{6}.
        /// </summary>
        internal static string ERRMSG_INVALID_SCHEMA_LINE {
            get {
                return ResourceManager.GetString("ERRMSG_INVALID_SCHEMA_LINE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to is not a valid value for CrudVerb..
        /// </summary>
        internal static string ERRMSG_PREFIX_INVALID_VERB {
            get {
                return ResourceManager.GetString("ERRMSG_PREFIX_INVALID_VERB", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to TableName = {0}, ColumnName = {1}, ColumnIndex = {2}, ColumnValue = {3}, ColumnLabel = {4}.
        /// </summary>
        internal static string MSG_COLUMNNAMESANDLABELS_TOSTRING {
            get {
                return ResourceManager.GetString("MSG_COLUMNNAMESANDLABELS_TOSTRING", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Processing PSQL database table {0}{2}                Action Taken = {1}{2}.
        /// </summary>
        internal static string MSG_DISPLAY_TABLE_NAME_ON_CONSOLE {
            get {
                return ResourceManager.GetString("MSG_DISPLAY_TABLE_NAME_ON_CONSOLE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to     Exception HResult: {0}.
        /// </summary>
        internal static string MSG_EXCEPTION_HRESULT {
            get {
                return ResourceManager.GetString("MSG_EXCEPTION_HRESULT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to     Exception Source: {0}.
        /// </summary>
        internal static string MSG_EXCEPTION_SOURCE {
            get {
                return ResourceManager.GetString("MSG_EXCEPTION_SOURCE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to     Exception StackTrace: {0}{1}.
        /// </summary>
        internal static string MSG_EXCEPTION_STACKTRACE {
            get {
                return ResourceManager.GetString("MSG_EXCEPTION_STACKTRACE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to     Exception TargetSite: {0}.
        /// </summary>
        internal static string MSG_EXCEPTION_TARGETSITE {
            get {
                return ResourceManager.GetString("MSG_EXCEPTION_TARGETSITE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to An {0} exception arose.{2}{2}    Exception Message: {1}.
        /// </summary>
        internal static string MSG_EXCEPTION_TYPE_AND_MESSAGE {
            get {
                return ResourceManager.GetString("MSG_EXCEPTION_TYPE_AND_MESSAGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Listing.
        /// </summary>
        internal static string MSG_LABEL_FOR_LISTING {
            get {
                return ResourceManager.GetString("MSG_LABEL_FOR_LISTING", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Table  .
        /// </summary>
        internal static string MSG_LABEL_FOR_TABLE {
            get {
                return ResourceManager.GetString("MSG_LABEL_FOR_TABLE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to     Listing record # {0} of {1}.
        /// </summary>
        internal static string MSG_PROGRESS_UPDATE {
            get {
                return ResourceManager.GetString("MSG_PROGRESS_UPDATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to     Specify which table to process..
        /// </summary>
        internal static string MSG_PROMPT_FOR_TABLE_NAME {
            get {
                return ResourceManager.GetString("MSG_PROMPT_FOR_TABLE_NAME", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Record Number {0}: .
        /// </summary>
        internal static string MSG_RECORD_LABEL_PREFIX {
            get {
                return ResourceManager.GetString("MSG_RECORD_LABEL_PREFIX", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Report Name: Listing of Everything in a PSQL Table{4}Run Date: {0} ({1} UTC){4}{4}Table Name       = {2}{4}Records in Table = {3}{4}.
        /// </summary>
        internal static string MSG_REPORT_HEADER {
            get {
                return ResourceManager.GetString("MSG_REPORT_HEADER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Execution succeeded..
        /// </summary>
        internal static string MSG_SHUTDOWN_NORMALLY {
            get {
                return ResourceManager.GetString("MSG_SHUTDOWN_NORMALLY", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Execution failed with status code {0:0x8x} ({1} decimal)..
        /// </summary>
        internal static string MSG_SHUTDOWN_WITH_ERROR {
            get {
                return ResourceManager.GetString("MSG_SHUTDOWN_WITH_ERROR", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0}{1} File Name = {2}.
        /// </summary>
        internal static string MSG_TASK_SUMMARY {
            get {
                return ResourceManager.GetString("MSG_TASK_SUMMARY", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Press the RETURN key to return to Windows..
        /// </summary>
        internal static string MSG_WAIT_FOR_CARBON_UNIT {
            get {
                return ResourceManager.GetString("MSG_WAIT_FOR_CARBON_UNIT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to End of report, Total records = {0}.
        /// </summary>
        internal static string REPORT_FOOTER {
            get {
                return ResourceManager.GetString("REPORT_FOOTER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to ColumnName = {0}, ColumnLabel = {1}.
        /// </summary>
        internal static string UNIQUE_COLUMN_NAME_TOSTRING {
            get {
                return ResourceManager.GetString("UNIQUE_COLUMN_NAME_TOSTRING", resourceCulture);
            }
        }
    }
}
