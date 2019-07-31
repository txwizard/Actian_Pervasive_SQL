////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 - Actian Corp.
//
////////////////////////////////////////////////////////////

// This file lives in project "psql.core" and "psql.docs".
// Make sure you correctly commit this file to both projects.  
// Do NOT simply make a copy of it.

#ifndef _BTRIEVECPP_H
#define _BTRIEVECPP_H

#include <set>

#include "btrieveC.h"

class BtrieveClient;
class BtrieveCollection;
class BtrieveDocumentSet;
class BtrieveFile;
class BtrieveFileAttributes;
class BtrieveFileInformation;
class BtrieveFilter;
class BtrieveBulkRetrieveResult;
class BtrieveBulkRetrieveAttributes;
class BtrieveIndexAttributes;
class BtrieveBulkCreatePayload;
class BtrieveBulkCreateResult;
class BtrieveKeySegment;
class BtrieveVersion;

/// \brief The %Btrieve class.
class LINKAGE Btrieve
{
public:
   /// \brief The %Btrieve maximum record length.
   static const int MAXIMUM_RECORD_LENGTH = BTRIEVE_MAXIMUM_RECORD_LENGTH;

   /// \brief The %Btrieve maximum key segment length.
   static const int MAXIMUM_KEY_LENGTH = BTRIEVE_MAXIMUM_KEY_LENGTH;

   /// \brief The %Btrieve alternate collation sequence modes.
   /// \see Btrieve::ACSModeToString
   enum ACSMode {
      /// \brief None.
      ACS_MODE_NONE = BTRIEVE_ACS_MODE_NONE,
      /// \brief Named.
      ACS_MODE_NAMED = BTRIEVE_ACS_MODE_NAMED,
      /// \brief Numbered.
      ACS_MODE_NUMBERED = BTRIEVE_ACS_MODE_NUMBERED,
      /// \brief Case insensitive.
      ACS_MODE_CASE_INSENSITIVE = BTRIEVE_ACS_MODE_CASE_INSENSITIVE,
      /// \brief Default.
      ACS_MODE_DEFAULT = BTRIEVE_ACS_MODE_DEFAULT,
      /// \brief Unknown.
      ACS_MODE_UNKNOWN = BTRIEVE_ACS_MODE_UNKNOWN
   };

   /// \brief The %Btrieve create modes.
   /// \par \SNIPPET
   /// \snippet btest.cpp CreateMode
   enum CreateMode {
      /// \brief Overwrite.
      CREATE_MODE_OVERWRITE = BTRIEVE_CREATE_MODE_OVERWRITE,
      /// \brief No overwrite.
      CREATE_MODE_NO_OVERWRITE = BTRIEVE_CREATE_MODE_NO_OVERWRITE,
      /// \brief Unknown.
      CREATE_MODE_UNKNOWN = BTRIEVE_CREATE_MODE_UNKNOWN
   };
   /// \brief The %Btrieve comparisons.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp Comparison
   enum Comparison {
      /// \brief None.
      COMPARISON_NONE = BTRIEVE_COMPARISON_NONE,
      /// \brief Equal.
      COMPARISON_EQUAL = BTRIEVE_COMPARISON_EQUAL,
      /// \brief Greater than.
      COMPARISON_GREATER_THAN = BTRIEVE_COMPARISON_GREATER_THAN,
      /// \brief Less than.
      COMPARISON_LESS_THAN = BTRIEVE_COMPARISON_LESS_THAN,
      /// \brief Not equal.
      COMPARISON_NOT_EQUAL = BTRIEVE_COMPARISON_NOT_EQUAL,
      /// \brief Greater than or equal.
      COMPARISON_GREATER_THAN_OR_EQUAL = BTRIEVE_COMPARISON_GREATER_THAN_OR_EQUAL,
      /// \brief Less than or equal.
      COMPARISON_LESS_THAN_OR_EQUAL = BTRIEVE_COMPARISON_LESS_THAN_OR_EQUAL,
      /// \brief Like.
      COMPARISON_LIKE = BTRIEVE_COMPARISON_LIKE,
      /// \brief Not like.
      COMPARISON_NOT_LIKE = BTRIEVE_COMPARISON_NOT_LIKE,
      /// \brief Unknown.
      COMPARISON_UNKNOWN = BTRIEVE_COMPARISON_UNKNOWN
   };

   /// \brief The %Btrieve connectors.
   /// \par \SNIPPET
   /// \snippet bfilter.cpp Connector
   enum Connector {
      /// \brief Last.
      CONNECTOR_LAST = BTRIEVE_CONNECTOR_LAST,
      /// \brief And.
      CONNECTOR_AND = BTRIEVE_CONNECTOR_AND,
      /// \brief Or.
      CONNECTOR_OR = BTRIEVE_CONNECTOR_OR,
      /// \brief Unknown.
      CONNECTOR_UNKNOWN = BTRIEVE_CONNECTOR_UNKNOWN
   };


   /// \brief The %Btrieve disk drives.
   enum DiskDrive {
      /// \brief Disk drive A.
      DISK_DRIVE_A = BTRIEVE_DISK_DRIVE_A, 
      /// \brief Disk drive B.
      DISK_DRIVE_B = BTRIEVE_DISK_DRIVE_B, 
      /// \brief Disk drive C.
      DISK_DRIVE_C = BTRIEVE_DISK_DRIVE_C,
      /// \brief Disk drive D.
      DISK_DRIVE_D = BTRIEVE_DISK_DRIVE_D, 
      /// \brief Disk drive E.
      DISK_DRIVE_E = BTRIEVE_DISK_DRIVE_E, 
      /// \brief Disk drive F.
      DISK_DRIVE_F = BTRIEVE_DISK_DRIVE_F,
      /// \brief Disk drive G.
      DISK_DRIVE_G = BTRIEVE_DISK_DRIVE_G, 
      /// \brief Disk drive H.
      DISK_DRIVE_H = BTRIEVE_DISK_DRIVE_H, 
      /// \brief Disk drive I.
      DISK_DRIVE_I = BTRIEVE_DISK_DRIVE_I,
      /// \brief Disk drive J.
      DISK_DRIVE_J = BTRIEVE_DISK_DRIVE_J, 
      /// \brief Disk drive K.
      DISK_DRIVE_K = BTRIEVE_DISK_DRIVE_K, 
      /// \brief Disk drive L.
      DISK_DRIVE_L = BTRIEVE_DISK_DRIVE_L,
      /// \brief Disk drive M.
      DISK_DRIVE_M = BTRIEVE_DISK_DRIVE_M, 
      /// \brief Disk drive N.
      DISK_DRIVE_N = BTRIEVE_DISK_DRIVE_N, 
      /// \brief Disk drive O.
      DISK_DRIVE_O = BTRIEVE_DISK_DRIVE_O,
      /// \brief Disk drive P.
      DISK_DRIVE_P = BTRIEVE_DISK_DRIVE_P, 
      /// \brief Disk drive Q.
      DISK_DRIVE_Q = BTRIEVE_DISK_DRIVE_Q, 
      /// \brief Disk drive R.
      DISK_DRIVE_R = BTRIEVE_DISK_DRIVE_R,
      /// \brief Disk drive S.
      DISK_DRIVE_S = BTRIEVE_DISK_DRIVE_S, 
      /// \brief Disk drive T.
      DISK_DRIVE_T = BTRIEVE_DISK_DRIVE_T, 
      /// \brief Disk drive U.
      DISK_DRIVE_U = BTRIEVE_DISK_DRIVE_U,
      /// \brief Disk drive V.
      DISK_DRIVE_V = BTRIEVE_DISK_DRIVE_V, 
      /// \brief Disk drive W.
      DISK_DRIVE_W = BTRIEVE_DISK_DRIVE_W, 
      /// \brief Disk drive X.
      DISK_DRIVE_X = BTRIEVE_DISK_DRIVE_X,
      /// \brief Disk drive Y.
      DISK_DRIVE_Y = BTRIEVE_DISK_DRIVE_Y, 
      /// \brief Disk drive Z.
      DISK_DRIVE_Z = BTRIEVE_DISK_DRIVE_Z, 
      /// \brief Default.
      DISK_DRIVE_DEFAULT = BTRIEVE_DISK_DRIVE_DEFAULT,
      /// \brief Unknown.
      DISK_DRIVE_UNKNOWN = BTRIEVE_DISK_DRIVE_UNKNOWN
   };

   /// \brief The %Btrieve duplicate modes.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp DuplicateMode
   /// \see Btrieve::DuplicateModeToString
   enum DuplicateMode {
      /// \brief Duplicates not allowed.
      DUPLICATE_MODE_NOT_ALLOWED = BTRIEVE_DUPLICATE_MODE_NOT_ALLOWED,
      /// \brief Duplicates allowed, nonrepeating.
      DUPLICATE_MODE_ALLOWED_NONREPEATING = BTRIEVE_DUPLICATE_MODE_ALLOWED_NONREPEATING,
      /// \brief Duplicates allowed, repeating.
      DUPLICATE_MODE_ALLOWED_REPEATING = BTRIEVE_DUPLICATE_MODE_ALLOWED_REPEATING,
      /// \brief Unknown.
      DUPLICATE_MODE_UNKNOWN = BTRIEVE_DUPLICATE_MODE_UNKNOWN
   };

   /// \brief The %Btrieve data types.
   /// \par \SNIPPET
   /// \snippet btest.cpp DataType
   /// \see Btrieve::DataTypeToString
   enum DataType {
      /// \brief Character
      DATA_TYPE_CHAR = BTRIEVE_DATA_TYPE_CHAR,
      /// \brief Null terminated string.
      DATA_TYPE_ZSTRING = BTRIEVE_DATA_TYPE_ZSTRING,
      /// \brief Integer.
      DATA_TYPE_INTEGER = BTRIEVE_DATA_TYPE_INTEGER,
      /// \brief Unsigned binary.
      DATA_TYPE_UNSIGNED_BINARY = BTRIEVE_DATA_TYPE_UNSIGNED_BINARY,
      /// \brief Float.
      DATA_TYPE_FLOAT = BTRIEVE_DATA_TYPE_FLOAT,
      /// \brief Autoincrement.
      DATA_TYPE_AUTOINCREMENT = BTRIEVE_DATA_TYPE_AUTOINCREMENT,
      /// \brief Date.
      DATA_TYPE_DATE = BTRIEVE_DATA_TYPE_DATE,
      /// \brief Numeric sign trailing separate.
      DATA_TYPE_NUMERICSTS = BTRIEVE_DATA_TYPE_NUMERICSTS,
      /// \brief Time.
      DATA_TYPE_TIME = BTRIEVE_DATA_TYPE_TIME,
      /// \brief Numeric signed ASCII.
      DATA_TYPE_NUMERICSA = BTRIEVE_DATA_TYPE_NUMERICSA,
      /// \brief Decimal.
      DATA_TYPE_DECIMAL = BTRIEVE_DATA_TYPE_DECIMAL,
      /// \brief Currency.
      DATA_TYPE_CURRENCY = BTRIEVE_DATA_TYPE_CURRENCY,
      /// \brief Money.
      DATA_TYPE_MONEY = BTRIEVE_DATA_TYPE_MONEY,
      /// \brief Timestamp.
      DATA_TYPE_TIMESTAMP = BTRIEVE_DATA_TYPE_TIMESTAMP,
      /// \brief Logical.
      DATA_TYPE_LOGICAL = BTRIEVE_DATA_TYPE_LOGICAL,
      /// \brief Wide string.
      DATA_TYPE_WSTRING = BTRIEVE_DATA_TYPE_WSTRING,
      /// \brief Numeric.
      DATA_TYPE_NUMERIC = BTRIEVE_DATA_TYPE_NUMERIC,
      /// \brief Wide null terminated string.
      DATA_TYPE_WZSTRING = BTRIEVE_DATA_TYPE_WZSTRING,
      /// \brief BASIC float.
      DATA_TYPE_BFLOAT = BTRIEVE_DATA_TYPE_BFLOAT,
      /// \brief Globally unique identifier.
      DATA_TYPE_GUID = BTRIEVE_DATA_TYPE_GUID,
      /// \brief Length first string.
      DATA_TYPE_LSTRING = BTRIEVE_DATA_TYPE_LSTRING,
      /// \brief Null indicator segment.
      DATA_TYPE_NULL_INDICATOR_SEGMENT = BTRIEVE_DATA_TYPE_NULL_INDICATOR_SEGMENT,
      /// \brief Legacy string.
      DATA_TYPE_LEGACY_STRING = BTRIEVE_DATA_TYPE_LEGACY_STRING,
      /// \brief Legacy binary.
      DATA_TYPE_LEGACY_BINARY = BTRIEVE_DATA_TYPE_LEGACY_BINARY,
      /// \brief Unknown.
      DATA_TYPE_UNKNOWN = BTRIEVE_DATA_TYPE_UNKNOWN 
   };

   /// \brief The %Btrieve file versions.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp FileVersion
   /// \see Btrieve::FileVersionToString
   enum FileVersion {
      /// \brief File version 6.0.
      FILE_VERSION_6_0 = BTRIEVE_FILE_VERSION_6_0,
      /// \brief File version 6.1.
      FILE_VERSION_6_1 = BTRIEVE_FILE_VERSION_6_1,
      /// \brief File version 7.0.
      FILE_VERSION_7_0 = BTRIEVE_FILE_VERSION_7_0,
      /// \brief File version 8.0.
      FILE_VERSION_8_0 = BTRIEVE_FILE_VERSION_8_0,
      /// \brief File version 9.0.
      FILE_VERSION_9_0 = BTRIEVE_FILE_VERSION_9_0,
      /// \brief File version 9.5.
      FILE_VERSION_9_5 = BTRIEVE_FILE_VERSION_9_5,
      /// \brief File version 13.0.
      FILE_VERSION_13_0 = BTRIEVE_FILE_VERSION_13_0,
      /// \brief Default.
      FILE_VERSION_DEFAULT = BTRIEVE_FILE_VERSION_DEFAULT,
      /// \brief Unknown.
      FILE_VERSION_UNKNOWN = BTRIEVE_FILE_VERSION_UNKNOWN
   };

   /// \brief The %Btrieve free space thresholds.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp FreeSpaceThreshold
   /// \see Btrieve::FreeSpaceThresholdToString
   enum FreeSpaceThreshold {
      /// \brief Free space threshold 10%.
      FREE_SPACE_THRESHOLD_10_PERCENT = BTRIEVE_FREE_SPACE_THRESHOLD_10_PERCENT,
      /// \brief Free space threshold 20%.
      FREE_SPACE_THRESHOLD_20_PERCENT = BTRIEVE_FREE_SPACE_THRESHOLD_20_PERCENT,
      /// \brief Free space threshold 30%.
      FREE_SPACE_THRESHOLD_30_PERCENT = BTRIEVE_FREE_SPACE_THRESHOLD_30_PERCENT,
      /// \brief Default.
      FREE_SPACE_THRESHOLD_DEFAULT = BTRIEVE_FREE_SPACE_THRESHOLD_DEFAULT,
      /// \brief Unknown.
      FREE_SPACE_THRESHOLD_UNKNOWN = BTRIEVE_FREE_SPACE_THRESHOLD_UNKNOWN
   };

   /// \brief The %Btrieve indexes.
   /// \par \SNIPPET
   /// \snippet btest.cpp Index
   /// \see Btrieve::IndexToString
   enum Index {
      /// \brief Index 1
      INDEX_1 = BTRIEVE_INDEX_1,
      /// \brief Index 2
      INDEX_2 = BTRIEVE_INDEX_2,
      /// \brief Index 3
      INDEX_3 = BTRIEVE_INDEX_3,
      /// \brief Index 4
      INDEX_4 = BTRIEVE_INDEX_4,
      /// \brief Index 5
      INDEX_5 = BTRIEVE_INDEX_5,
      /// \brief Index 6
      INDEX_6 = BTRIEVE_INDEX_6,
      /// \brief Index 7
      INDEX_7 = BTRIEVE_INDEX_7,
      /// \brief Index 8
      INDEX_8 = BTRIEVE_INDEX_8,
      /// \brief Index 9
      INDEX_9 = BTRIEVE_INDEX_9,
      /// \brief Index 10
      INDEX_10 = BTRIEVE_INDEX_10,
      /// \brief Index 11
      INDEX_11 = BTRIEVE_INDEX_11,
      /// \brief Index 12
      INDEX_12 = BTRIEVE_INDEX_12,
      /// \brief Index 13
      INDEX_13 = BTRIEVE_INDEX_13,
      /// \brief Index 14
      INDEX_14 = BTRIEVE_INDEX_14,
      /// \brief Index 15
      INDEX_15 = BTRIEVE_INDEX_15,
      /// \brief Index 16
      INDEX_16 = BTRIEVE_INDEX_16,
      /// \brief Index 17
      INDEX_17 = BTRIEVE_INDEX_17,
      /// \brief Index 18
      INDEX_18 = BTRIEVE_INDEX_18,
      /// \brief Index 19
      INDEX_19 = BTRIEVE_INDEX_19,
      /// \brief Index 20
      INDEX_20 = BTRIEVE_INDEX_20,
      /// \brief Index 21
      INDEX_21 = BTRIEVE_INDEX_21,
      /// \brief Index 22
      INDEX_22 = BTRIEVE_INDEX_22,
      /// \brief Index 23
      INDEX_23 = BTRIEVE_INDEX_23,
      /// \brief Index 24
      INDEX_24 = BTRIEVE_INDEX_24,
      /// \brief Index 25
      INDEX_25 = BTRIEVE_INDEX_25,
      /// \brief Index 26
      INDEX_26 = BTRIEVE_INDEX_26,
      /// \brief Index 27
      INDEX_27 = BTRIEVE_INDEX_27,
      /// \brief Index 28
      INDEX_28 = BTRIEVE_INDEX_28,
      /// \brief Index 29
      INDEX_29 = BTRIEVE_INDEX_29,
      /// \brief Index 30
      INDEX_30 = BTRIEVE_INDEX_30,
      /// \brief Index 31
      INDEX_31 = BTRIEVE_INDEX_31,
      /// \brief Index 32
      INDEX_32 = BTRIEVE_INDEX_32,
      /// \brief Index 33
      INDEX_33 = BTRIEVE_INDEX_33,
      /// \brief Index 34
      INDEX_34 = BTRIEVE_INDEX_34,
      /// \brief Index 35
      INDEX_35 = BTRIEVE_INDEX_35,
      /// \brief Index 36
      INDEX_36 = BTRIEVE_INDEX_36,
      /// \brief Index 37
      INDEX_37 = BTRIEVE_INDEX_37,
      /// \brief Index 38
      INDEX_38 = BTRIEVE_INDEX_38,
      /// \brief Index 39
      INDEX_39 = BTRIEVE_INDEX_39,
      /// \brief Index 40
      INDEX_40 = BTRIEVE_INDEX_40,
      /// \brief Index 41
      INDEX_41 = BTRIEVE_INDEX_41,
      /// \brief Index 42
      INDEX_42 = BTRIEVE_INDEX_42,
      /// \brief Index 43
      INDEX_43 = BTRIEVE_INDEX_43,
      /// \brief Index 44
      INDEX_44 = BTRIEVE_INDEX_44,
      /// \brief Index 45
      INDEX_45 = BTRIEVE_INDEX_45,
      /// \brief Index 46
      INDEX_46 = BTRIEVE_INDEX_46,
      /// \brief Index 47
      INDEX_47 = BTRIEVE_INDEX_47,
      /// \brief Index 48
      INDEX_48 = BTRIEVE_INDEX_48,
      /// \brief Index 49
      INDEX_49 = BTRIEVE_INDEX_49,
      /// \brief Index 50
      INDEX_50 = BTRIEVE_INDEX_50,
      /// \brief Index 51
      INDEX_51 = BTRIEVE_INDEX_51,
      /// \brief Index 52
      INDEX_52 = BTRIEVE_INDEX_52,
      /// \brief Index 53
      INDEX_53 = BTRIEVE_INDEX_53,
      /// \brief Index 54
      INDEX_54 = BTRIEVE_INDEX_54,
      /// \brief Index 55
      INDEX_55 = BTRIEVE_INDEX_55,
      /// \brief Index 56
      INDEX_56 = BTRIEVE_INDEX_56,
      /// \brief Index 57
      INDEX_57 = BTRIEVE_INDEX_57,
      /// \brief Index 58
      INDEX_58 = BTRIEVE_INDEX_58,
      /// \brief Index 59
      INDEX_59 = BTRIEVE_INDEX_59,
      /// \brief Index 60
      INDEX_60 = BTRIEVE_INDEX_60,
      /// \brief Index 61
      INDEX_61 = BTRIEVE_INDEX_61,
      /// \brief Index 62
      INDEX_62 = BTRIEVE_INDEX_62,
      /// \brief Index 63
      INDEX_63 = BTRIEVE_INDEX_63,
      /// \brief Index 64
      INDEX_64 = BTRIEVE_INDEX_64,
      /// \brief Index 65
      INDEX_65 = BTRIEVE_INDEX_65,
      /// \brief Index 66
      INDEX_66 = BTRIEVE_INDEX_66,
      /// \brief Index 67
      INDEX_67 = BTRIEVE_INDEX_67,
      /// \brief Index 68
      INDEX_68 = BTRIEVE_INDEX_68,
      /// \brief Index 69
      INDEX_69 = BTRIEVE_INDEX_69,
      /// \brief Index 70
      INDEX_70 = BTRIEVE_INDEX_70,
      /// \brief Index 71
      INDEX_71 = BTRIEVE_INDEX_71,
      /// \brief Index 72
      INDEX_72 = BTRIEVE_INDEX_72,
      /// \brief Index 73
      INDEX_73 = BTRIEVE_INDEX_73,
      /// \brief Index 74
      INDEX_74 = BTRIEVE_INDEX_74,
      /// \brief Index 75
      INDEX_75 = BTRIEVE_INDEX_75,
      /// \brief Index 76
      INDEX_76 = BTRIEVE_INDEX_76,
      /// \brief Index 77
      INDEX_77 = BTRIEVE_INDEX_77,
      /// \brief Index 78
      INDEX_78 = BTRIEVE_INDEX_78,
      /// \brief Index 79
      INDEX_79 = BTRIEVE_INDEX_79,
      /// \brief Index 80
      INDEX_80 = BTRIEVE_INDEX_80,
      /// \brief Index 81
      INDEX_81 = BTRIEVE_INDEX_81,
      /// \brief Index 82
      INDEX_82 = BTRIEVE_INDEX_82,
      /// \brief Index 83
      INDEX_83 = BTRIEVE_INDEX_83,
      /// \brief Index 84
      INDEX_84 = BTRIEVE_INDEX_84,
      /// \brief Index 85
      INDEX_85 = BTRIEVE_INDEX_85,
      /// \brief Index 86
      INDEX_86 = BTRIEVE_INDEX_86,
      /// \brief Index 87
      INDEX_87 = BTRIEVE_INDEX_87,
      /// \brief Index 88
      INDEX_88 = BTRIEVE_INDEX_88,
      /// \brief Index 89
      INDEX_89 = BTRIEVE_INDEX_89,
      /// \brief Index 90
      INDEX_90 = BTRIEVE_INDEX_90,
      /// \brief Index 91
      INDEX_91 = BTRIEVE_INDEX_91,
      /// \brief Index 92
      INDEX_92 = BTRIEVE_INDEX_92,
      /// \brief Index 93
      INDEX_93 = BTRIEVE_INDEX_93,
      /// \brief Index 94
      INDEX_94 = BTRIEVE_INDEX_94,
      /// \brief Index 95
      INDEX_95 = BTRIEVE_INDEX_95,
      /// \brief Index 96
      INDEX_96 = BTRIEVE_INDEX_96,
      /// \brief Index 97
      INDEX_97 = BTRIEVE_INDEX_97,
      /// \brief Index 98
      INDEX_98 = BTRIEVE_INDEX_98,
      /// \brief Index 99
      INDEX_99 = BTRIEVE_INDEX_99,
      /// \brief Index 100
      INDEX_100 = BTRIEVE_INDEX_100,
      /// \brief Index 101
      INDEX_101 = BTRIEVE_INDEX_101,
      /// \brief Index 102
      INDEX_102 = BTRIEVE_INDEX_102,
      /// \brief Index 103
      INDEX_103 = BTRIEVE_INDEX_103,
      /// \brief Index 104
      INDEX_104 = BTRIEVE_INDEX_104,
      /// \brief Index 105
      INDEX_105 = BTRIEVE_INDEX_105,
      /// \brief Index 106
      INDEX_106 = BTRIEVE_INDEX_106,
      /// \brief Index 107
      INDEX_107 = BTRIEVE_INDEX_107,
      /// \brief Index 108
      INDEX_108 = BTRIEVE_INDEX_108,
      /// \brief Index 109
      INDEX_109 = BTRIEVE_INDEX_109,
      /// \brief Index 110
      INDEX_110 = BTRIEVE_INDEX_110,
      /// \brief Index 111
      INDEX_111 = BTRIEVE_INDEX_111,
      /// \brief Index 112
      INDEX_112 = BTRIEVE_INDEX_112,
      /// \brief Index 113
      INDEX_113 = BTRIEVE_INDEX_113,
      /// \brief Index 114
      INDEX_114 = BTRIEVE_INDEX_114,
      /// \brief Index 115
      INDEX_115 = BTRIEVE_INDEX_115,
      /// \brief Index 116
      INDEX_116 = BTRIEVE_INDEX_116,
      /// \brief Index 117
      INDEX_117 = BTRIEVE_INDEX_117,
      /// \brief Index 118
      INDEX_118 = BTRIEVE_INDEX_118,
      /// \brief Index 119
      INDEX_119 = BTRIEVE_INDEX_119,
      /// \brief System.
      INDEX_SYSTEM = BTRIEVE_INDEX_SYSTEM, 
      /// \brief None.
      INDEX_NONE = BTRIEVE_INDEX_NONE, 
      /// \brief Unknown.
      INDEX_UNKNOWN = BTRIEVE_INDEX_UNKNOWN
   };

   /// \brief The %Btrieve location modes.
   enum LocationMode {
      /// \brief No preference.
      LOCATION_MODE_NO_PREFERENCE = BTRIEVE_LOCATION_MODE_NO_PREFERENCE,
      /// \brief Force local.
      LOCATION_MODE_FORCE_LOCAL = BTRIEVE_LOCATION_MODE_FORCE_LOCAL,
      /// \brief Force remote.
      LOCATION_MODE_FORCE_REMOTE = BTRIEVE_LOCATION_MODE_FORCE_REMOTE,
      /// \brief Unknown.
      LOCATION_MODE_UNKNOWN = BTRIEVE_LOCATION_MODE_UNKNOWN
   };

   /// \brief The %Btrieve lock modes.
   /// \par \SNIPPET
   /// \snippet block.cpp LockMode
   /// \see Btrieve::LockModeToString
   enum LockMode {
      /// \brief None.
      LOCK_MODE_NONE = BTRIEVE_LOCK_MODE_NONE,
      /// \brief Single with wait.
      LOCK_MODE_SINGLE_WAIT = BTRIEVE_LOCK_MODE_SINGLE_WAIT,
      /// \brief Single with no wait.
      LOCK_MODE_SINGLE_NO_WAIT = BTRIEVE_LOCK_MODE_SINGLE_NO_WAIT,
      /// \brief Multiple with wait.
      LOCK_MODE_MULTIPLE_WAIT = BTRIEVE_LOCK_MODE_MULTIPLE_WAIT,
      /// \brief Multiple with no wait.
      LOCK_MODE_MULTIPLE_NO_WAIT = BTRIEVE_LOCK_MODE_MULTIPLE_NO_WAIT,
      /// \brief Unknown.
      LOCK_MODE_UNKNOWN = BTRIEVE_LOCK_MODE_UNKNOWN
   };

   /// \brief The %Btrieve null key modes.
   /// \see Btrieve::NullKeyModeToString
   enum NullKeyMode {
      /// \brief None.
      NULL_KEY_MODE_NONE = BTRIEVE_NULL_KEY_MODE_NONE,
      /// \brief All segments.
      NULL_KEY_MODE_ALL_SEGMENTS = BTRIEVE_NULL_KEY_MODE_ALL_SEGMENTS,
      /// \brief Any segments.
      NULL_KEY_MODE_ANY_SEGMENTS = BTRIEVE_NULL_KEY_MODE_ANY_SEGMENTS,
      /// \brief Unknown.
      NULL_KEY_MODE_UNKNOWN = BTRIEVE_NULL_KEY_MODE_UNKNOWN 
   };

   /// \brief The %Btrieve open modes.
   /// \par \SNIPPET
   /// \snippet btest.cpp OpenMode
   enum OpenMode {
      /// \brief Normal.
      OPEN_MODE_NORMAL = BTRIEVE_OPEN_MODE_NORMAL,
      /// \brief Accelerated.
      OPEN_MODE_ACCELERATED = BTRIEVE_OPEN_MODE_ACCELERATED,
      /// \brief Read only.
      OPEN_MODE_READ_ONLY = BTRIEVE_OPEN_MODE_READ_ONLY,
      /// \brief Exclusive.
      OPEN_MODE_EXCLUSIVE = BTRIEVE_OPEN_MODE_EXCLUSIVE,
      /// \brief Unknown.
      OPEN_MODE_UNKNOWN = BTRIEVE_OPEN_MODE_UNKNOWN
   };

   /// \brief The %Btrieve file owner modes.
   /// \see Btrieve::OwnerModeToString
   enum OwnerMode {
      /// \brief None.
      OWNER_MODE_NONE = BTRIEVE_OWNER_MODE_NONE,
      /// \brief No encyption with no read allowed.
      OWNER_MODE_NO_ENCRYPTION_NO_READ_ALLOWED = BTRIEVE_OWNER_MODE_NO_ENCRYPTION_NO_READ_ALLOWED,
      /// \brief No encyption with read allowed.
      OWNER_MODE_NO_ENCRYPTION_READ_ALLOWED = BTRIEVE_OWNER_MODE_NO_ENCRYPTION_READ_ALLOWED,
      /// \brief Encyption with no read allowed.
      OWNER_MODE_ENCRYPTION_NO_READ_ALLOWED = BTRIEVE_OWNER_MODE_ENCRYPTION_NO_READ_ALLOWED,
      /// \brief Encyption with read allowed.
      OWNER_MODE_ENCRYPTION_READ_ALLOWED = BTRIEVE_OWNER_MODE_ENCRYPTION_READ_ALLOWED,
      /// \brief Unknown.
      OWNER_MODE_UNKNOWN = BTRIEVE_OWNER_MODE_UNKNOWN
   };

   /// \brief The %Btrieve page lock type.
   /// \see Btrieve::PageLockTypeToString
   enum PageLockType {
      /// \brief None.
      PAGE_LOCK_TYPE_NONE = BTRIEVE_PAGE_LOCK_TYPE_NONE,
      /// \brief Data page.
      PAGE_LOCK_TYPE_DATA_PAGE = BTRIEVE_PAGE_LOCK_TYPE_DATA_PAGE,
      /// \brief Index page.
      PAGE_LOCK_TYPE_INDEX_PAGE = BTRIEVE_PAGE_LOCK_TYPE_INDEX_PAGE,
      /// \brief Variable page.
      PAGE_LOCK_TYPE_VARIABLE_PAGE = BTRIEVE_PAGE_LOCK_TYPE_VARIABLE_PAGE,
      /// \brief Unknown.
      PAGE_LOCK_TYPE_UNKNOWN = BTRIEVE_PAGE_LOCK_TYPE_UNKNOWN
   };

   /// \brief The %Btrieve page sizes.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp PageSize
   /// \see Btrieve::PageSizeToString
   enum PageSize {
      /// \brief Page size 512.
      PAGE_SIZE_512 = BTRIEVE_PAGE_SIZE_512,
      /// \brief Page size 1024.
      PAGE_SIZE_1024 = BTRIEVE_PAGE_SIZE_1024,
      /// \brief Page size 1536.
      PAGE_SIZE_1536 = BTRIEVE_PAGE_SIZE_1536,
      /// \brief Page size 2048.
      PAGE_SIZE_2048 = BTRIEVE_PAGE_SIZE_2048,
      /// \brief Page size 3072.
      PAGE_SIZE_3072 = BTRIEVE_PAGE_SIZE_3072,
      /// \brief Page size 3584.
      PAGE_SIZE_3584 = BTRIEVE_PAGE_SIZE_3584,
      /// \brief Page size 4096.
      PAGE_SIZE_4096 = BTRIEVE_PAGE_SIZE_4096,
      /// \brief Page size 8192.
      PAGE_SIZE_8192 = BTRIEVE_PAGE_SIZE_8192,
      /// \brief Page size 16384.
      PAGE_SIZE_16384 = BTRIEVE_PAGE_SIZE_16384,
      /// \brief Default.
      PAGE_SIZE_DEFAULT = BTRIEVE_PAGE_SIZE_DEFAULT,
      /// \brief Unknown.
      PAGE_SIZE_UNKNOWN = BTRIEVE_PAGE_SIZE_UNKNOWN
   };

   /// \brief The %Btrieve record compression modes.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp RecordCompressionMode
   /// \see Btrieve::RecordCompressionModeToString
   enum RecordCompressionMode {
      /// \brief None.
      RECORD_COMPRESSION_MODE_NONE = BTRIEVE_RECORD_COMPRESSION_MODE_NONE,
      /// \brief Blank truncation.
      RECORD_COMPRESSION_MODE_BLANK_TRUNCATION = BTRIEVE_RECORD_COMPRESSION_MODE_BLANK_TRUNCATION,
      /// \brief Run length encoding.
      RECORD_COMPRESSION_MODE_RUN_LENGTH_ENCODING = BTRIEVE_RECORD_COMPRESSION_MODE_RUN_LENGTH_ENCODING,
      /// \brief Unknown.
      RECORD_COMPRESSION_MODE_UNKNOWN = BTRIEVE_RECORD_COMPRESSION_MODE_UNKNOWN
   };

   /// \brief The %Btrieve status codes.
   /// \par \SNIPPET
   /// \snippet btest.cpp StatusCode
   /// \see Btrieve::StatusCodeToString
   enum StatusCode {
		/// \brief 0 - No error.
      STATUS_CODE_NO_ERROR = BTRIEVE_STATUS_CODE_NO_ERROR,
		/// \brief 1 - Invalid function.
      STATUS_CODE_INVALID_FUNCTION = BTRIEVE_STATUS_CODE_INVALID_FUNCTION,
		/// \brief 2 - Input/Output error.
      STATUS_CODE_IO_ERROR = BTRIEVE_STATUS_CODE_IO_ERROR,
		/// \brief 3 - File not open.
      STATUS_CODE_FILE_NOT_OPEN = BTRIEVE_STATUS_CODE_FILE_NOT_OPEN,
		/// \brief 4 - Key value not found.
      STATUS_CODE_KEY_VALUE_NOT_FOUND = BTRIEVE_STATUS_CODE_KEY_VALUE_NOT_FOUND,
		/// \brief 5 - Duplicate key value.
      STATUS_CODE_DUPLICATE_KEY_VALUE = BTRIEVE_STATUS_CODE_DUPLICATE_KEY_VALUE,
		/// \brief 6 - Invalid index number.
      STATUS_CODE_INVALID_INDEX_NUMBER = BTRIEVE_STATUS_CODE_INVALID_INDEX_NUMBER,
		/// \brief 7 - Different index number.
      STATUS_CODE_DIFFERENT_INDEX_NUMBER = BTRIEVE_STATUS_CODE_DIFFERENT_INDEX_NUMBER,
		/// \brief 8 - Position not set.
      STATUS_CODE_POSITION_NOT_SET = BTRIEVE_STATUS_CODE_POSITION_NOT_SET,
		/// \brief 9 - End of file.
      STATUS_CODE_END_OF_FILE = BTRIEVE_STATUS_CODE_END_OF_FILE,
		/// \brief 10 - Modifiable key value error.
      STATUS_CODE_MODIFIABLE_KEYVALUE_ERROR = BTRIEVE_STATUS_CODE_MODIFIABLE_KEYVALUE_ERROR,
		/// \brief 11 - File name bad.
      STATUS_CODE_FILENAME_BAD = BTRIEVE_STATUS_CODE_FILENAME_BAD,
		/// \brief 12 - File not found.
      STATUS_CODE_FILE_NOT_FOUND = BTRIEVE_STATUS_CODE_FILE_NOT_FOUND,
		/// \brief 13 - Extended file error.
      STATUS_CODE_EXTENDED_FILE_ERROR = BTRIEVE_STATUS_CODE_EXTENDED_FILE_ERROR,
		/// \brief 14 - Preimage open error.
      STATUS_CODE_PREIMAGE_OPEN_ERROR = BTRIEVE_STATUS_CODE_PREIMAGE_OPEN_ERROR,
		/// \brief 15 - Preimage input/output error.
      STATUS_CODE_PREIMAGE_IO_ERROR = BTRIEVE_STATUS_CODE_PREIMAGE_IO_ERROR,
		/// \brief 16 - Expansion error.
      STATUS_CODE_EXPANSION_ERROR = BTRIEVE_STATUS_CODE_EXPANSION_ERROR,
		/// \brief 17 - Close error.
      STATUS_CODE_CLOSE_ERROR = BTRIEVE_STATUS_CODE_CLOSE_ERROR,
		/// \brief 18 - Disk full.
      STATUS_CODE_DISKFULL = BTRIEVE_STATUS_CODE_DISKFULL,
		/// \brief 19 - Unrecoverable error.
      STATUS_CODE_UNRECOVERABLE_ERROR = BTRIEVE_STATUS_CODE_UNRECOVERABLE_ERROR,
		/// \brief 20 - Record manager inactive.
      STATUS_CODE_RECORD_MANAGER_INACTIVE = BTRIEVE_STATUS_CODE_RECORD_MANAGER_INACTIVE,
		/// \brief 21 - Key buffer too short.
      STATUS_CODE_KEYBUFFER_TOO_SHORT = BTRIEVE_STATUS_CODE_KEYBUFFER_TOO_SHORT,
		/// \brief 22 - Data length error.
      STATUS_CODE_DATALENGTH_ERROR = BTRIEVE_STATUS_CODE_DATALENGTH_ERROR,
		/// \brief 23 - Position block length.
      STATUS_CODE_POSITIONBLOCK_LENGTH = BTRIEVE_STATUS_CODE_POSITIONBLOCK_LENGTH,
		/// \brief 24 - Page size error.
      STATUS_CODE_PAGE_SIZE_ERROR = BTRIEVE_STATUS_CODE_PAGE_SIZE_ERROR,
		/// \brief 25 - Create input/output error.
      STATUS_CODE_CREATE_IO_ERROR = BTRIEVE_STATUS_CODE_CREATE_IO_ERROR,
		/// \brief 26 - Number of indexes.
      STATUS_CODE_NUMBER_OF_INDEXES = BTRIEVE_STATUS_CODE_NUMBER_OF_INDEXES,
		/// \brief 27 - Invalid key position.
      STATUS_CODE_INVALID_KEY_POSITION = BTRIEVE_STATUS_CODE_INVALID_KEY_POSITION,
		/// \brief 28 - Invalid record length.
      STATUS_CODE_INVALID_RECORD_LENGTH = BTRIEVE_STATUS_CODE_INVALID_RECORD_LENGTH,
		/// \brief 29 - Invalid keylength.
      STATUS_CODE_INVALID_KEYLENGTH = BTRIEVE_STATUS_CODE_INVALID_KEYLENGTH,
		/// \brief 30 - Not a %Btrieve file.
      STATUS_CODE_NOT_A_BTRIEVE_FILE = BTRIEVE_STATUS_CODE_NOT_A_BTRIEVE_FILE,
		/// \brief 31 - File already extended.
      STATUS_CODE_FILE_ALREADY_EXTENDED = BTRIEVE_STATUS_CODE_FILE_ALREADY_EXTENDED,
		/// \brief 32 - Extend input/output error.
      STATUS_CODE_EXTEND_IO_ERROR = BTRIEVE_STATUS_CODE_EXTEND_IO_ERROR,
		/// \brief 33 - %Btrieve cannot unload.
      STATUS_CODE_BTR_CANNOT_UNLOAD = BTRIEVE_STATUS_CODE_BTR_CANNOT_UNLOAD,
		/// \brief 34 - Invalid extension name.
      STATUS_CODE_INVALID_EXTENSION_NAME = BTRIEVE_STATUS_CODE_INVALID_EXTENSION_NAME,
		/// \brief 35 - Directory error.
      STATUS_CODE_DIRECTORY_ERROR = BTRIEVE_STATUS_CODE_DIRECTORY_ERROR,
		/// \brief 36 - Transaction error.
      STATUS_CODE_TRANSACTION_ERROR = BTRIEVE_STATUS_CODE_TRANSACTION_ERROR,
		/// \brief 37 - Transaction is active.
      STATUS_CODE_TRANSACTION_IS_ACTIVE = BTRIEVE_STATUS_CODE_TRANSACTION_IS_ACTIVE,
		/// \brief 38 - Transaction file input/output error.
      STATUS_CODE_TRANSACTION_FILE_IO_ERROR = BTRIEVE_STATUS_CODE_TRANSACTION_FILE_IO_ERROR,
		/// \brief 39 - End transaction error.
      STATUS_CODE_END_TRANSACTION_ERROR = BTRIEVE_STATUS_CODE_END_TRANSACTION_ERROR,
		/// \brief 40 - Transaction maximum files.
      STATUS_CODE_TRANSACTION_MAX_FILES = BTRIEVE_STATUS_CODE_TRANSACTION_MAX_FILES,
		/// \brief 41 - Operation not allowed.
      STATUS_CODE_OPERATION_NOT_ALLOWED = BTRIEVE_STATUS_CODE_OPERATION_NOT_ALLOWED,
		/// \brief 42 - Incomplete accelerated access.
      STATUS_CODE_INCOMPLETE_ACCEL_ACCESS = BTRIEVE_STATUS_CODE_INCOMPLETE_ACCEL_ACCESS,
		/// \brief 43 - Invalid record address.
      STATUS_CODE_INVALID_RECORD_ADDRESS = BTRIEVE_STATUS_CODE_INVALID_RECORD_ADDRESS,
		/// \brief 44 - Null key path.
      STATUS_CODE_NULL_KEYPATH = BTRIEVE_STATUS_CODE_NULL_KEYPATH,
		/// \brief 45 - Inconsistent key flags.
      STATUS_CODE_INCONSISTENT_KEY_FLAGS = BTRIEVE_STATUS_CODE_INCONSISTENT_KEY_FLAGS,
		/// \brief 46 - Access to file denied.
      STATUS_CODE_ACCESS_TO_FILE_DENIED = BTRIEVE_STATUS_CODE_ACCESS_TO_FILE_DENIED,
		/// \brief 47 - Maximum open files.
      STATUS_CODE_MAXIMUM_OPEN_FILES = BTRIEVE_STATUS_CODE_MAXIMUM_OPEN_FILES,
		/// \brief 48 - Invalid alternate collating sequence definition.
      STATUS_CODE_INVALID_ALT_SEQUENCE_DEF = BTRIEVE_STATUS_CODE_INVALID_ALT_SEQUENCE_DEF,
		/// \brief 49 - Key type error.
      STATUS_CODE_KEY_TYPE_ERROR = BTRIEVE_STATUS_CODE_KEY_TYPE_ERROR,
		/// \brief 50 - Owner already set.
      STATUS_CODE_OWNER_ALREADY_SET = BTRIEVE_STATUS_CODE_OWNER_ALREADY_SET,
		/// \brief 51 - Invalid owner.
      STATUS_CODE_INVALID_OWNER = BTRIEVE_STATUS_CODE_INVALID_OWNER,
		/// \brief 52 - Error writing cache.
      STATUS_CODE_ERROR_WRITING_CACHE = BTRIEVE_STATUS_CODE_ERROR_WRITING_CACHE,
		/// \brief 53 - Invalid interface.
      STATUS_CODE_INVALID_INTERFACE = BTRIEVE_STATUS_CODE_INVALID_INTERFACE,
		/// \brief 54 - Variable page error.
      STATUS_CODE_VARIABLE_PAGE_ERROR = BTRIEVE_STATUS_CODE_VARIABLE_PAGE_ERROR,
		/// \brief 55 - Autoincrement error.
      STATUS_CODE_AUTOINCREMENT_ERROR = BTRIEVE_STATUS_CODE_AUTOINCREMENT_ERROR,
		/// \brief 56 - Incomplete index.
      STATUS_CODE_INCOMPLETE_INDEX = BTRIEVE_STATUS_CODE_INCOMPLETE_INDEX,
		/// \brief 57 - Expaned memory error.
      STATUS_CODE_EXPANED_MEM_ERROR = BTRIEVE_STATUS_CODE_EXPANED_MEM_ERROR,
		/// \brief 58 - Compress buffer too short.
      STATUS_CODE_COMPRESS_BUFFER_TOO_SHORT = BTRIEVE_STATUS_CODE_COMPRESS_BUFFER_TOO_SHORT,
		/// \brief 59 - File already exists.
      STATUS_CODE_FILE_ALREADY_EXISTS = BTRIEVE_STATUS_CODE_FILE_ALREADY_EXISTS,
		/// \brief 60 - Reject count reached.
      STATUS_CODE_REJECT_COUNT_REACHED = BTRIEVE_STATUS_CODE_REJECT_COUNT_REACHED,
		/// \brief 61 - Small extended get buffer error.
      STATUS_CODE_SMALL_EX_GET_BUFFER_ERROR = BTRIEVE_STATUS_CODE_SMALL_EX_GET_BUFFER_ERROR,
		/// \brief 62 - Invalid get expression.
      STATUS_CODE_INVALID_GET_EXPRESSION = BTRIEVE_STATUS_CODE_INVALID_GET_EXPRESSION,
		/// \brief 63 - Invalid extended insert buffer.
      STATUS_CODE_INVALID_EXT_INSERT_BUFF = BTRIEVE_STATUS_CODE_INVALID_EXT_INSERT_BUFF,
		/// \brief 64 - Optimize limit reached.
      STATUS_CODE_OPTIMIZE_LIMIT_REACHED = BTRIEVE_STATUS_CODE_OPTIMIZE_LIMIT_REACHED,
		/// \brief 65 - Invalid extractor.
      STATUS_CODE_INVALID_EXTRACTOR = BTRIEVE_STATUS_CODE_INVALID_EXTRACTOR,
		/// \brief 66 - Referential integrity too many databases.
      STATUS_CODE_RI_TOO_MANY_DATABASES = BTRIEVE_STATUS_CODE_RI_TOO_MANY_DATABASES,
		/// \brief 67 - Referential integrity SQL data dictionary files cannot open.
      STATUS_CODE_RIDDF_CANNOT_OPEN = BTRIEVE_STATUS_CODE_RIDDF_CANNOT_OPEN,
		/// \brief 68 - Referential integrity cascade too deep.
      STATUS_CODE_RI_CASCADE_TOO_DEEP = BTRIEVE_STATUS_CODE_RI_CASCADE_TOO_DEEP,
		/// \brief 69 - Referential integrity cascade error.
      STATUS_CODE_RI_CASCADE_ERROR = BTRIEVE_STATUS_CODE_RI_CASCADE_ERROR,
		/// \brief 71 - Referential integrity violation.
      STATUS_CODE_RI_VIOLATION = BTRIEVE_STATUS_CODE_RI_VIOLATION,
		/// \brief 72 - Referential integrity referenced file cannot open.
      STATUS_CODE_RI_REFERENCED_FILE_CANNOT_OPEN = BTRIEVE_STATUS_CODE_RI_REFERENCED_FILE_CANNOT_OPEN,
		/// \brief 73 - Referential integrity out of sync.
      STATUS_CODE_RI_OUT_OF_SYNC = BTRIEVE_STATUS_CODE_RI_OUT_OF_SYNC,
		/// \brief 74 - End changed to abort.
      STATUS_CODE_END_CHANGED_TO_ABORT = BTRIEVE_STATUS_CODE_END_CHANGED_TO_ABORT,
		/// \brief 76 - Referential integrity conflict.
      STATUS_CODE_RI_CONFLICT = BTRIEVE_STATUS_CODE_RI_CONFLICT,
		/// \brief 77 - Can't loop in server.
      STATUS_CODE_CANT_LOOP_IN_SERVER = BTRIEVE_STATUS_CODE_CANT_LOOP_IN_SERVER,
		/// \brief 78 - Dead lock.
      STATUS_CODE_DEAD_LOCK = BTRIEVE_STATUS_CODE_DEAD_LOCK,
		/// \brief 79 - Programming error.
      STATUS_CODE_PROGRAMMING_ERROR = BTRIEVE_STATUS_CODE_PROGRAMMING_ERROR,
		/// \brief 80 - Conflict.
      STATUS_CODE_CONFLICT = BTRIEVE_STATUS_CODE_CONFLICT,
		/// \brief 81 - Lock error.
      STATUS_CODE_LOCKERROR = BTRIEVE_STATUS_CODE_LOCKERROR,
		/// \brief 82 - Lost position.
      STATUS_CODE_LOST_POSITION = BTRIEVE_STATUS_CODE_LOST_POSITION,
		/// \brief 83 - Read outside transaction.
      STATUS_CODE_READ_OUTSIDE_TRANSACTION = BTRIEVE_STATUS_CODE_READ_OUTSIDE_TRANSACTION,
		/// \brief 84 - Record in use.
      STATUS_CODE_RECORD_INUSE = BTRIEVE_STATUS_CODE_RECORD_INUSE,
		/// \brief 85 - File in use.
      STATUS_CODE_FILE_INUSE = BTRIEVE_STATUS_CODE_FILE_INUSE,
		/// \brief 86 - File table full.
      STATUS_CODE_FILE_TABLE_FULL = BTRIEVE_STATUS_CODE_FILE_TABLE_FULL,
		/// \brief 87 - No handles available.
      STATUS_CODE_NOHANDLES_AVAILABLE = BTRIEVE_STATUS_CODE_NOHANDLES_AVAILABLE,
		/// \brief 88 - Incompatible mode error.
      STATUS_CODE_INCOMPATIBLE_MODE_ERROR = BTRIEVE_STATUS_CODE_INCOMPATIBLE_MODE_ERROR,
		/// \brief 90 - Device table full.
      STATUS_CODE_DEVICE_TABLE_FULL = BTRIEVE_STATUS_CODE_DEVICE_TABLE_FULL,
		/// \brief 91 - Server error.
      STATUS_CODE_SERVER_ERROR = BTRIEVE_STATUS_CODE_SERVER_ERROR,
		/// \brief 92 - Transaction table full.
      STATUS_CODE_TRANSACTION_TABLE_FULL = BTRIEVE_STATUS_CODE_TRANSACTION_TABLE_FULL,
		/// \brief 93 - Incompatible lock type.
      STATUS_CODE_INCOMPATIBLE_LOCK_TYPE = BTRIEVE_STATUS_CODE_INCOMPATIBLE_LOCK_TYPE,
		/// \brief 94 - Permission error.
      STATUS_CODE_PERMISSION_ERROR = BTRIEVE_STATUS_CODE_PERMISSION_ERROR,
		/// \brief 95 - Session no longer valid.
      STATUS_CODE_SESSION_NO_LONGER_VALID = BTRIEVE_STATUS_CODE_SESSION_NO_LONGER_VALID,
		/// \brief 96 - Communications error.
      STATUS_CODE_COMMUNICATIONS_ERROR = BTRIEVE_STATUS_CODE_COMMUNICATIONS_ERROR,
		/// \brief 97 - Data message too small.
      STATUS_CODE_DATA_MESSAGE_TOO_SMALL = BTRIEVE_STATUS_CODE_DATA_MESSAGE_TOO_SMALL,
		/// \brief 98 - Internal transaction error.
      STATUS_CODE_INTERNAL_TRANSACTION_ERROR = BTRIEVE_STATUS_CODE_INTERNAL_TRANSACTION_ERROR,
		/// \brief 99 - Requester can't access runtime.
      STATUS_CODE_REQUESTER_CANT_ACCESS_RUNTIME = BTRIEVE_STATUS_CODE_REQUESTER_CANT_ACCESS_RUNTIME,
		/// \brief 100 - No cache buffers available.
      STATUS_CODE_NO_CACHE_BUFFERS_AVAIL = BTRIEVE_STATUS_CODE_NO_CACHE_BUFFERS_AVAIL,
		/// \brief 101 - No operating system memory available.
      STATUS_CODE_NO_OS_MEMORY_AVAIL = BTRIEVE_STATUS_CODE_NO_OS_MEMORY_AVAIL,
		/// \brief 102 - No stack available.
      STATUS_CODE_NO_STACK_AVAIL = BTRIEVE_STATUS_CODE_NO_STACK_AVAIL,
		/// \brief 103 - Chunk offset too long.
      STATUS_CODE_CHUNK_OFFSET_TOO_LONG = BTRIEVE_STATUS_CODE_CHUNK_OFFSET_TOO_LONG,
		/// \brief 104 - Locale error.
      STATUS_CODE_LOCALE_ERROR = BTRIEVE_STATUS_CODE_LOCALE_ERROR,
		/// \brief 105 - Cannot create with variable tail allocation table.
      STATUS_CODE_CANNOT_CREATE_WITH_VAT = BTRIEVE_STATUS_CODE_CANNOT_CREATE_WITH_VAT,
		/// \brief 106 - Chunk cannot get next.
      STATUS_CODE_CHUNK_CANNOT_GET_NEXT = BTRIEVE_STATUS_CODE_CHUNK_CANNOT_GET_NEXT,
		/// \brief 107 - Chunk incompatible file.
      STATUS_CODE_CHUNK_INCOMPATIBLE_FILE = BTRIEVE_STATUS_CODE_CHUNK_INCOMPATIBLE_FILE,
		/// \brief 109 - Transaction too complex.
      STATUS_CODE_TRANSACTION_TOO_COMPLEX = BTRIEVE_STATUS_CODE_TRANSACTION_TOO_COMPLEX,
		/// \brief 110 - Archival BLOG open error.
      STATUS_CODE_ARCH_BLOG_OPEN_ERROR = BTRIEVE_STATUS_CODE_ARCH_BLOG_OPEN_ERROR,
		/// \brief 111 - Archival file not logged.
      STATUS_CODE_ARCH_FILE_NOT_LOGGED = BTRIEVE_STATUS_CODE_ARCH_FILE_NOT_LOGGED,
		/// \brief 112 - Archival file in use.
      STATUS_CODE_ARCH_FILE_IN_USE = BTRIEVE_STATUS_CODE_ARCH_FILE_IN_USE,
		/// \brief 113 - Archival log file not found.
      STATUS_CODE_ARCH_LOGFILE_NOT_FOUND = BTRIEVE_STATUS_CODE_ARCH_LOGFILE_NOT_FOUND,
		/// \brief 114 - Archival log file invalid.
      STATUS_CODE_ARCH_LOGFILE_INVALID = BTRIEVE_STATUS_CODE_ARCH_LOGFILE_INVALID,
		/// \brief 115 - Archival dump file access error.
      STATUS_CODE_ARCH_DUMPFILE_ACCESS_ERROR = BTRIEVE_STATUS_CODE_ARCH_DUMPFILE_ACCESS_ERROR,
		/// \brief 116 - Locator file indicator.
      STATUS_CODE_LOCATOR_FILE_INDICATOR = BTRIEVE_STATUS_CODE_LOCATOR_FILE_INDICATOR,
		/// \brief 130 - No system locks available.
      STATUS_CODE_NO_SYSTEM_LOCKS_AVAILABLE = BTRIEVE_STATUS_CODE_NO_SYSTEM_LOCKS_AVAILABLE,
		/// \brief 132 - File full.
      STATUS_CODE_FILE_FULL = BTRIEVE_STATUS_CODE_FILE_FULL,
		/// \brief 133 - More than 5 concurrent users.
      STATUS_CODE_MORE_THAN_5_CONCURRENT_USERS = BTRIEVE_STATUS_CODE_MORE_THAN_5_CONCURRENT_USERS,
		/// \brief 134 - International sorting rule not found.
      STATUS_CODE_ISR_NOT_FOUND = BTRIEVE_STATUS_CODE_ISR_NOT_FOUND,
		/// \brief 135 - International sorting rule invalid.
      STATUS_CODE_ISR_INVALID = BTRIEVE_STATUS_CODE_ISR_INVALID,
		/// \brief 136 - Alternate collating sequence not found.
      STATUS_CODE_ACS_NOT_FOUND = BTRIEVE_STATUS_CODE_ACS_NOT_FOUND,
		/// \brief 137 - Cannot convert RP.
      STATUS_CODE_CANNOT_CONVERT_RP = BTRIEVE_STATUS_CODE_CANNOT_CONVERT_RP,
		/// \brief 138 - Invalid null indicator.
      STATUS_CODE_INVALID_NULL_INDICATOR = BTRIEVE_STATUS_CODE_INVALID_NULL_INDICATOR,
		/// \brief 139 - Invalid key option.
      STATUS_CODE_INVALID_KEY_OPTION = BTRIEVE_STATUS_CODE_INVALID_KEY_OPTION,
		/// \brief 140 - Incompatible close.
      STATUS_CODE_INCOMPATIBLE_CLOSE = BTRIEVE_STATUS_CODE_INCOMPATIBLE_CLOSE,
		/// \brief 141 - Invalid user name.
      STATUS_CODE_INVALID_USERNAME = BTRIEVE_STATUS_CODE_INVALID_USERNAME,
		/// \brief 142 - Invalid database.
      STATUS_CODE_INVALID_DATABASE = BTRIEVE_STATUS_CODE_INVALID_DATABASE,
		/// \brief 143 - No SSQL rights.
      STATUS_CODE_NO_SSQL_RIGHTS = BTRIEVE_STATUS_CODE_NO_SSQL_RIGHTS,
		/// \brief 144 - Already logged in.
      STATUS_CODE_ALREADY_LOGGED_IN = BTRIEVE_STATUS_CODE_ALREADY_LOGGED_IN,
		/// \brief 145 - No database services.
      STATUS_CODE_NO_DATABASE_SERVICES = BTRIEVE_STATUS_CODE_NO_DATABASE_SERVICES,
		/// \brief 146 - Duplicate system key.
      STATUS_CODE_DUPLICATE_SYSTEM_KEY = BTRIEVE_STATUS_CODE_DUPLICATE_SYSTEM_KEY,
		/// \brief 147 - Log segment missing.
      STATUS_CODE_LOG_SEGMENT_MISSING = BTRIEVE_STATUS_CODE_LOG_SEGMENT_MISSING,
		/// \brief 148 - Roll forward error.
      STATUS_CODE_ROLL_FORWARD_ERROR = BTRIEVE_STATUS_CODE_ROLL_FORWARD_ERROR,
		/// \brief 149 - System key internal.
      STATUS_CODE_SYSTEM_KEY_INTERNAL = BTRIEVE_STATUS_CODE_SYSTEM_KEY_INTERNAL,
		/// \brief 150 - DBS internal error.
      STATUS_CODE_DBS_INTERNAL_ERROR = BTRIEVE_STATUS_CODE_DBS_INTERNAL_ERROR,
		/// \brief 151 - Nesting depth error.
      STATUS_CODE_NESTING_DEPTH_ERROR = BTRIEVE_STATUS_CODE_NESTING_DEPTH_ERROR,
		/// \brief 160 - Invalid parameter to MicroKernel.
      STATUS_CODE_INVALID_PARAMETER_TO_MKDE = BTRIEVE_STATUS_CODE_INVALID_PARAMETER_TO_MKDE,
		/// \brief 161 - User count limit exceeded.
      STATUS_CODE_USER_COUNT_LIMIT_EXCEEDED = BTRIEVE_STATUS_CODE_USER_COUNT_LIMIT_EXCEEDED,
		/// \brief 162 - Client table full.
      STATUS_CODE_CLIENT_TABLE_FULL = BTRIEVE_STATUS_CODE_CLIENT_TABLE_FULL,
		/// \brief 163 - Last segment error.
      STATUS_CODE_LAST_SEGMENT_ERROR = BTRIEVE_STATUS_CODE_LAST_SEGMENT_ERROR,
		/// \brief 170 - Login failed bad user name.
      STATUS_CODE_LOGIN_FAILED_BAD_USERNAME = BTRIEVE_STATUS_CODE_LOGIN_FAILED_BAD_USERNAME,
		/// \brief 171 - Login failed bad password.
      STATUS_CODE_LOGIN_FAILED_BAD_PASSWORD = BTRIEVE_STATUS_CODE_LOGIN_FAILED_BAD_PASSWORD,
		/// \brief 172 - Login failed bad database.
      STATUS_CODE_LOGIN_FAILED_BAD_DATABASE = BTRIEVE_STATUS_CODE_LOGIN_FAILED_BAD_DATABASE,
		/// \brief 173 - Login already logged in.
      STATUS_CODE_LOGIN_ALREADY_LOGGED_IN = BTRIEVE_STATUS_CODE_LOGIN_ALREADY_LOGGED_IN,
		/// \brief 174 - Login logout failed.
      STATUS_CODE_LOGIN_LOGOUT_FAILED = BTRIEVE_STATUS_CODE_LOGIN_LOGOUT_FAILED,
		/// \brief 175 - Login wrong uniform resource indicator format.
      STATUS_CODE_LOGIN_WRONG_URI_FORMAT = BTRIEVE_STATUS_CODE_LOGIN_WRONG_URI_FORMAT,
		/// \brief 176 - Login file and table not found.
      STATUS_CODE_LOGIN_FILE_AND_TABLE_NOT_FOUND = BTRIEVE_STATUS_CODE_LOGIN_FILE_AND_TABLE_NOT_FOUND,
		/// \brief 177 - Login table not in database.
      STATUS_CODE_LOGIN_TABLE_NOT_IN_DATABASE = BTRIEVE_STATUS_CODE_LOGIN_TABLE_NOT_IN_DATABASE,
		/// \brief 178 - Login directory not in database.
      STATUS_CODE_LOGIN_DIRECTORY_NOT_IN_DATABASE = BTRIEVE_STATUS_CODE_LOGIN_DIRECTORY_NOT_IN_DATABASE,
		/// \brief 1001 - Lock parameter out of range.
      STATUS_CODE_LOCK_PARM_OUTOFRANGE = BTRIEVE_STATUS_CODE_LOCK_PARM_OUTOFRANGE,
		/// \brief 1002 - Memory allocation error.
      STATUS_CODE_MEM_ALLOCATION_ERR = BTRIEVE_STATUS_CODE_MEM_ALLOCATION_ERR,
		/// \brief 1003 - Memory parameter too small.
      STATUS_CODE_MEM_PARM_TOO_SMALL = BTRIEVE_STATUS_CODE_MEM_PARM_TOO_SMALL,
		/// \brief 1004 - Page size parameter out of range.
      STATUS_CODE_PAGE_SIZE_PARM_OUTOFRANGE = BTRIEVE_STATUS_CODE_PAGE_SIZE_PARM_OUTOFRANGE,
		/// \brief 1005 - Invalid preimage parameter.
      STATUS_CODE_INVALID_PREIMAGE_PARM = BTRIEVE_STATUS_CODE_INVALID_PREIMAGE_PARM,
		/// \brief 1006 - Preimage buffer parameter out of range.
      STATUS_CODE_PREIMAGE_BUF_PARM_OUTOFRANGE = BTRIEVE_STATUS_CODE_PREIMAGE_BUF_PARM_OUTOFRANGE,
		/// \brief 1007 - Files parameter out of range.
      STATUS_CODE_FILES_PARM_OUTOFRANGE = BTRIEVE_STATUS_CODE_FILES_PARM_OUTOFRANGE,
		/// \brief 1008 - Invalid initialization parameter.
      STATUS_CODE_INVALID_INIT_PARM = BTRIEVE_STATUS_CODE_INVALID_INIT_PARM,
		/// \brief 1009 - Invalid transaction parameter.
      STATUS_CODE_INVALID_TRANS_PARM = BTRIEVE_STATUS_CODE_INVALID_TRANS_PARM,
		/// \brief 1010 - Error access transaction control file.
      STATUS_CODE_ERROR_ACC_TRANS_CONTROL_FILE = BTRIEVE_STATUS_CODE_ERROR_ACC_TRANS_CONTROL_FILE,
		/// \brief 1011 - Compression buffer parameter out of range.
      STATUS_CODE_COMPRESSION_BUF_PARM_OUTOFRANGE = BTRIEVE_STATUS_CODE_COMPRESSION_BUF_PARM_OUTOFRANGE,
		/// \brief 1012 - Invalid "Maximum Number Of Files In A Transaction" option.
      STATUS_CODE_INV_N_OPTION = BTRIEVE_STATUS_CODE_INV_N_OPTION,
		/// \brief 1013 - Task list full.
      STATUS_CODE_TASK_LIST_FULL = BTRIEVE_STATUS_CODE_TASK_LIST_FULL,
		/// \brief 1014 - Stop warning.
      STATUS_CODE_STOP_WARNING = BTRIEVE_STATUS_CODE_STOP_WARNING,
		/// \brief 1015 - Pointer parameter invalid.
      STATUS_CODE_POINTER_PARM_INVALID = BTRIEVE_STATUS_CODE_POINTER_PARM_INVALID,
		/// \brief 1016 - Already initialized.
      STATUS_CODE_ALREADY_INITIALIZED = BTRIEVE_STATUS_CODE_ALREADY_INITIALIZED,
		/// \brief 1017 - %Btrieve Requester can't find resource DLL.
      STATUS_CODE_REQ_CANT_FIND_RES_DLL = BTRIEVE_STATUS_CODE_REQ_CANT_FIND_RES_DLL,
		/// \brief 1018 - Already inside %Btrieve function.
      STATUS_CODE_ALREADY_INSIDE_BTR_FUNCTION = BTRIEVE_STATUS_CODE_ALREADY_INSIDE_BTR_FUNCTION,
		/// \brief 1019 - Callback abort.
      STATUS_CODE_CALLBACK_ABORT = BTRIEVE_STATUS_CODE_CALLBACK_ABORT,
		/// \brief 1020 - Interface communications error.
      STATUS_CODE_INTF_COMM_ERROR = BTRIEVE_STATUS_CODE_INTF_COMM_ERROR,
		/// \brief 1021 - Failed to initialize.
      STATUS_CODE_FAILED_TO_INITIALIZE = BTRIEVE_STATUS_CODE_FAILED_TO_INITIALIZE,
		/// \brief 1022 - MicroKernel shutting down.
      STATUS_CODE_MKDE_SHUTTING_DOWN = BTRIEVE_STATUS_CODE_MKDE_SHUTTING_DOWN,
		/// \brief 2000 - Internal error.
      STATUS_CODE_INTERNAL_ERROR = BTRIEVE_STATUS_CODE_INTERNAL_ERROR,
		/// \brief 2001 - Insufficient memory allocation.
      STATUS_CODE_INSUFFICIENT_MEM_ALLOC = BTRIEVE_STATUS_CODE_INSUFFICIENT_MEM_ALLOC,
		/// \brief 2002 - Invalid option.
      STATUS_CODE_INVALID_OPTION = BTRIEVE_STATUS_CODE_INVALID_OPTION,
		/// \brief 2003 - No local access allowed.
      STATUS_CODE_NO_LOCAL_ACCESS_ALLOWED = BTRIEVE_STATUS_CODE_NO_LOCAL_ACCESS_ALLOWED,
		/// \brief 2004 - SPX not installed.
      STATUS_CODE_SPX_NOT_INSTALLED = BTRIEVE_STATUS_CODE_SPX_NOT_INSTALLED,
		/// \brief 2005 - Incorrect SPX version.
      STATUS_CODE_INCORRECT_SPX_VERSION = BTRIEVE_STATUS_CODE_INCORRECT_SPX_VERSION,
		/// \brief 2006 - No available SPX connection.
      STATUS_CODE_NO_AVAIL_SPX_CONNECTION = BTRIEVE_STATUS_CODE_NO_AVAIL_SPX_CONNECTION,
		/// \brief 2007 - Invalid pointer parameter.
      STATUS_CODE_INVALID_PTR_PARM = BTRIEVE_STATUS_CODE_INVALID_PTR_PARM,
		/// \brief 2008 - Can't connect to 615.
      STATUS_CODE_CANT_CONNECT_TO_615 = BTRIEVE_STATUS_CODE_CANT_CONNECT_TO_615,
		/// \brief 2009 - Can't load MicroKernel router.
      STATUS_CODE_CANT_LOAD_MKDE_ROUTER = BTRIEVE_STATUS_CODE_CANT_LOAD_MKDE_ROUTER,
		/// \brief 2010 - UT thunk not loaded.
      STATUS_CODE_UT_THUNK_NOT_LOADED = BTRIEVE_STATUS_CODE_UT_THUNK_NOT_LOADED,
		/// \brief 2011 - No resource DLL.
      STATUS_CODE_NO_RESOURCE_DLL = BTRIEVE_STATUS_CODE_NO_RESOURCE_DLL,
		/// \brief 2012 - Operating system error.
      STATUS_CODE_OS_ERROR = BTRIEVE_STATUS_CODE_OS_ERROR,
		/// \brief 3000 - MicroKernel router memory error.
      STATUS_CODE_MK_ROUTER_MEM_ERROR = BTRIEVE_STATUS_CODE_MK_ROUTER_MEM_ERROR,
		/// \brief 3001 - MicroKernel no local access allowed.
      STATUS_CODE_MK_NO_LOCAL_ACCESS_ALLOWED = BTRIEVE_STATUS_CODE_MK_NO_LOCAL_ACCESS_ALLOWED,
		/// \brief 3002 - MicroKernel no resource DLL.
      STATUS_CODE_MK_NO_RESOURCE_DLL = BTRIEVE_STATUS_CODE_MK_NO_RESOURCE_DLL,
		/// \brief 3003 - MicroKernel incompatible component.
      STATUS_CODE_MK_INCOMPAT_COMPONENT = BTRIEVE_STATUS_CODE_MK_INCOMPAT_COMPONENT,
		/// \brief 3004 - MicroKernel timeout error.
      STATUS_CODE_MK_TIMEOUT_ERROR = BTRIEVE_STATUS_CODE_MK_TIMEOUT_ERROR,
		/// \brief 3005 - MicroKernel operating system error.
      STATUS_CODE_MK_OS_ERROR = BTRIEVE_STATUS_CODE_MK_OS_ERROR,
		/// \brief 3006 - MicroKernel invalid session.
      STATUS_CODE_MK_INVALID_SESSION = BTRIEVE_STATUS_CODE_MK_INVALID_SESSION,
		/// \brief 3007 - MicroKernel server not found.
      STATUS_CODE_MK_SERVER_NOT_FOUND = BTRIEVE_STATUS_CODE_MK_SERVER_NOT_FOUND,
		/// \brief 3008 - MicroKernel invalid configuration.
      STATUS_CODE_MK_INVALID_CONFIG = BTRIEVE_STATUS_CODE_MK_INVALID_CONFIG,
		/// \brief 3009 - MicroKernel NETAPI not loaded.
      STATUS_CODE_MK_NETAPI_NOT_LOADED = BTRIEVE_STATUS_CODE_MK_NETAPI_NOT_LOADED,
		/// \brief 3010 - MicroKernel NWAPI not loaded.
      STATUS_CODE_MK_NWAPI_NOT_LOADED = BTRIEVE_STATUS_CODE_MK_NWAPI_NOT_LOADED,
		/// \brief 3011 - MicroKernel thunk not loaded.
      STATUS_CODE_MK_THUNK_NOT_LOADED = BTRIEVE_STATUS_CODE_MK_THUNK_NOT_LOADED,
		/// \brief 3012 - MicroKernel local not loaded.
      STATUS_CODE_MK_LOCAL_NOT_LOADED = BTRIEVE_STATUS_CODE_MK_LOCAL_NOT_LOADED,
		/// \brief 3013 - MicroKernel PSQL Network Services Layer not loaded.
      STATUS_CODE_MK_PNSL_NOT_LOADED = BTRIEVE_STATUS_CODE_MK_PNSL_NOT_LOADED,
		/// \brief 3014 - MicroKernel can't find engine.
      STATUS_CODE_MK_CANT_FIND_ENGINE = BTRIEVE_STATUS_CODE_MK_CANT_FIND_ENGINE,
		/// \brief 3015 - MicroKernel initialization error.
      STATUS_CODE_MK_INIT_ERROR = BTRIEVE_STATUS_CODE_MK_INIT_ERROR,
		/// \brief 3016 - MicroKernel internal error.
      STATUS_CODE_MK_INTERNAL_ERROR = BTRIEVE_STATUS_CODE_MK_INTERNAL_ERROR,
		/// \brief 3017 - MicroKernel local MicroKernel data buffer too small.
      STATUS_CODE_MK_LOCAL_MKDE_DATABUF_TOO_SMALL = BTRIEVE_STATUS_CODE_MK_LOCAL_MKDE_DATABUF_TOO_SMALL,
		/// \brief 3018 - MicroKernel closed error.
      STATUS_CODE_MK_CLOSED_ERROR = BTRIEVE_STATUS_CODE_MK_CLOSED_ERROR,
		/// \brief 3019 - MicroKernel semaphore error.
      STATUS_CODE_MK_SEMAPHORE_ERROR = BTRIEVE_STATUS_CODE_MK_SEMAPHORE_ERROR,
		/// \brief 3020 - MicroKernel loading error.
      STATUS_CODE_MK_LOADING_ERROR = BTRIEVE_STATUS_CODE_MK_LOADING_ERROR,
		/// \brief 3021 - MicroKernel bad SRB format.
      STATUS_CODE_MK_BAD_SRB_FORMAT = BTRIEVE_STATUS_CODE_MK_BAD_SRB_FORMAT,
		/// \brief 3022 - MicroKernel data buffer length too large.
      STATUS_CODE_MK_DATABUF_LEN_TOO_LARGE = BTRIEVE_STATUS_CODE_MK_DATABUF_LEN_TOO_LARGE,
		/// \brief 3023 - MicroKernel task table full.
      STATUS_CODE_MK_TASK_TABLE_FULL = BTRIEVE_STATUS_CODE_MK_TASK_TABLE_FULL,
		/// \brief 3024 - MicroKernel invalid operation on remote.
      STATUS_CODE_MK_INVALID_OP_ON_REMOTE = BTRIEVE_STATUS_CODE_MK_INVALID_OP_ON_REMOTE,
		/// \brief 3025 - MicroKernel PIDs not loaded.
      STATUS_CODE_MK_PIDS_NOT_LOADED = BTRIEVE_STATUS_CODE_MK_PIDS_NOT_LOADED,
		/// \brief 3026 - MicroKernel bad PIDs.
      STATUS_CODE_MK_BAD_PIDS = BTRIEVE_STATUS_CODE_MK_BAD_PIDS,
		/// \brief 3027 - MicroKernel IDS connect failure.
      STATUS_CODE_MK_IDS_CONNECT_FAILURE = BTRIEVE_STATUS_CODE_MK_IDS_CONNECT_FAILURE,
		/// \brief 3028 - MicroKernel IDS login failure.
      STATUS_CODE_MK_IDS_LOGIN_FAILURE = BTRIEVE_STATUS_CODE_MK_IDS_LOGIN_FAILURE,
		/// \brief 3101 - Network layer failure.
      STATUS_CODE_NL_FAILURE = BTRIEVE_STATUS_CODE_NL_FAILURE,
		/// \brief 3102 - Network layer not initialized.
      STATUS_CODE_NL_NOT_INITIALIZED = BTRIEVE_STATUS_CODE_NL_NOT_INITIALIZED,
		/// \brief 3103 - Network layer name not found.
      STATUS_CODE_NL_NAME_NOT_FOUND = BTRIEVE_STATUS_CODE_NL_NAME_NOT_FOUND,
		/// \brief 3104 - Network layer permission error.
      STATUS_CODE_NL_PERMISSION_ERROR = BTRIEVE_STATUS_CODE_NL_PERMISSION_ERROR,
		/// \brief 3105 - Network layer no available transport.
      STATUS_CODE_NL_NO_AVAILABLE_TRANSPORT = BTRIEVE_STATUS_CODE_NL_NO_AVAILABLE_TRANSPORT,
		/// \brief 3106 - Network layer connection failure.
      STATUS_CODE_NL_CONNECTION_FAILURE = BTRIEVE_STATUS_CODE_NL_CONNECTION_FAILURE,
		/// \brief 3107 - Network layer out of memory.
      STATUS_CODE_NL_OUT_OF_MEMORY = BTRIEVE_STATUS_CODE_NL_OUT_OF_MEMORY,
		/// \brief 3108 - Network layer invalid session.
      STATUS_CODE_NL_INVALID_SESSION = BTRIEVE_STATUS_CODE_NL_INVALID_SESSION,
		/// \brief 3109 - Network layer more data.
      STATUS_CODE_NL_MORE_DATA = BTRIEVE_STATUS_CODE_NL_MORE_DATA,
		/// \brief 3110 - Network layer not connected.
      STATUS_CODE_NL_NOT_CONNECTED = BTRIEVE_STATUS_CODE_NL_NOT_CONNECTED,
		/// \brief 3111 - Network layer send failure.
      STATUS_CODE_NL_SEND_FAILURE = BTRIEVE_STATUS_CODE_NL_SEND_FAILURE,
		/// \brief 3112 - Network layer receive failure.
      STATUS_CODE_NL_RECEIVE_FAILURE = BTRIEVE_STATUS_CODE_NL_RECEIVE_FAILURE,
		/// \brief 3113 - Network layer invalid server type.
      STATUS_CODE_NL_INVALID_SERVER_TYPE = BTRIEVE_STATUS_CODE_NL_INVALID_SERVER_TYPE,
		/// \brief 3114 - Network layer server routing table full.
      STATUS_CODE_NL_SRT_FULL = BTRIEVE_STATUS_CODE_NL_SRT_FULL,
		/// \brief 3115 - Network layer transport failure.
      STATUS_CODE_NL_TRANSPORT_FAILURE = BTRIEVE_STATUS_CODE_NL_TRANSPORT_FAILURE,
		/// \brief 3116 - Network layer receive data overflow.
      STATUS_CODE_NL_RCV_DATA_OVERFLOW = BTRIEVE_STATUS_CODE_NL_RCV_DATA_OVERFLOW,
		/// \brief 3117 - Network layer CST full.
      STATUS_CODE_NL_CST_FULL = BTRIEVE_STATUS_CODE_NL_CST_FULL,
		/// \brief 3118 - Network layer invalid address family.
      STATUS_CODE_NL_INVALID_ADDRESS_FAMILY = BTRIEVE_STATUS_CODE_NL_INVALID_ADDRESS_FAMILY,
		/// \brief 3119 - Network layer no authentication context available.
      STATUS_CODE_NL_NO_AUTH_CONTEXT_AVAILABLE = BTRIEVE_STATUS_CODE_NL_NO_AUTH_CONTEXT_AVAILABLE,
		/// \brief 3120 - Network layer invalid authentication type.
      STATUS_CODE_NL_INVALID_AUTH_TYPE = BTRIEVE_STATUS_CODE_NL_INVALID_AUTH_TYPE,
		/// \brief 3121 - Network layer invalid authentication object.
      STATUS_CODE_NL_INVALID_AUTH_OBJECT = BTRIEVE_STATUS_CODE_NL_INVALID_AUTH_OBJECT,
		/// \brief 3122 - Network layer authentication length too small.
      STATUS_CODE_NL_AUTH_LEN_TOO_SMALL = BTRIEVE_STATUS_CODE_NL_AUTH_LEN_TOO_SMALL,
		/// \brief 3123 - Network layer invalid session level parameter.
      STATUS_CODE_NL_INVALID_SESSION_LEVEL_PARM = BTRIEVE_STATUS_CODE_NL_INVALID_SESSION_LEVEL_PARM,
		/// \brief 3124 - Network layer task table full.
      STATUS_CODE_NL_TASK_TABLE_FULL = BTRIEVE_STATUS_CODE_NL_TASK_TABLE_FULL,
		/// \brief 3125 - Network layer NDS name resolution error.
      STATUS_CODE_NL_NDS_NAME_RESOLUTION_ERROR = BTRIEVE_STATUS_CODE_NL_NDS_NAME_RESOLUTION_ERROR,
		/// \brief 3126 - Network layer file name resolution error.
      STATUS_CODE_NL_FILE_NAME_RESOLUTION_ERROR = BTRIEVE_STATUS_CODE_NL_FILE_NAME_RESOLUTION_ERROR,
		/// \brief 3127 - Network layer IDS send failure.
      STATUS_CODE_NL_IDS_SEND_FAILURE = BTRIEVE_STATUS_CODE_NL_IDS_SEND_FAILURE,
		/// \brief 3128 - Network layer IDS receive failure.
      STATUS_CODE_NL_IDS_RCV_FAILURE = BTRIEVE_STATUS_CODE_NL_IDS_RCV_FAILURE,
		/// \brief -7 - Unknown.
      STATUS_CODE_UNKNOWN = BTRIEVE_STATUS_CODE_UNKNOWN
   };

   /// \brief The %Btrieve system data modes.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SystemDataMode
   /// \see Btrieve::SystemDataModeToString
   enum SystemDataMode {
      /// \brief Yes.
      SYSTEM_DATA_MODE_YES = BTRIEVE_SYSTEM_DATA_MODE_YES, 
      /// \brief No.
      SYSTEM_DATA_MODE_NO = BTRIEVE_SYSTEM_DATA_MODE_NO,
      /// \brief Default.
      SYSTEM_DATA_MODE_DEFAULT = BTRIEVE_SYSTEM_DATA_MODE_DEFAULT,
      /// \brief Unknown.
      SYSTEM_DATA_MODE_UNKNOWN = BTRIEVE_SYSTEM_DATA_MODE_UNKNOWN
   };

   /// \brief The %Btrieve transaction modes.
   enum TransactionMode {
      /// \brief Exclusive.
      TRANSACTION_MODE_EXCLUSIVE = BTRIEVE_TRANSACTION_MODE_EXCLUSIVE,
      /// \brief Concurrent with write wait.
      TRANSACTION_MODE_CONCURRENT_WRITE_WAIT = BTRIEVE_TRANSACTION_MODE_CONCURRENT_WRITE_WAIT,
      /// \brief Concurrent with no write wait.
      TRANSACTION_MODE_CONCURRENT_NO_WRITE_WAIT = BTRIEVE_TRANSACTION_MODE_CONCURRENT_NO_WRITE_WAIT,
      /// \brief Unknown.
      TRANSACTION_MODE_UNKNOWN = BTRIEVE_TRANSACTION_MODE_UNKNOWN
   };

   /// \brief The %Btrieve unlock modes.
   /// \par \SNIPPET
   /// \snippet block.cpp UnlockMode
   enum UnlockMode {
      /// \brief Single.
      UNLOCK_MODE_SINGLE = BTRIEVE_UNLOCK_MODE_SINGLE,
      /// \brief Multiple.
      UNLOCK_MODE_MULTIPLE = BTRIEVE_UNLOCK_MODE_MULTIPLE,
      /// \brief Unknown.
      UNLOCK_MODE_UNKNOWN = BTRIEVE_UNLOCK_MODE_UNKNOWN
   };

   /// \brief The %Btrieve variable length records modes.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp VariableLengthRecordsMode
   /// \see Btrieve::VariableLengthRecordsModeToString
   enum VariableLengthRecordsMode {
      /// \brief No.
      VARIABLE_LENGTH_RECORDS_MODE_NO = BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_NO, 
      /// \brief Yes.
      VARIABLE_LENGTH_RECORDS_MODE_YES = BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_YES,
      /// \brief Yes with variable allocation tails.
      VARIABLE_LENGTH_RECORDS_MODE_YES_VARIABLE_ALLOCATION_TAILS = BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_YES_VARIABLE_ALLOCATION_TAILS,
      /// \brief Unknown.
      VARIABLE_LENGTH_RECORDS_MODE_UNKNOWN = BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_UNKNOWN
   };

   /// \brief The %Btrieve version types.
   /// \see Btrieve::VersionTypeToString
   enum VersionType {
      /// \brief None.
      VERSION_TYPE_NONE = BTRIEVE_VERSION_TYPE_NONE, 
      /// \brief %Btrieve engine.
      VERSION_TYPE_BTRIEVE_ENGINE = BTRIEVE_VERSION_TYPE_BTRIEVE_ENGINE, 
      /// \brief Workgroup engine.
      VERSION_TYPE_WORKGROUP_ENGINE = BTRIEVE_VERSION_TYPE_WORKGROUP_ENGINE,
      /// \brief DOS workstation.
      VERSION_TYPE_DOS_WORKSTATION = BTRIEVE_VERSION_TYPE_DOS_WORKSTATION, 
      /// \brief Client.
      VERSION_TYPE_CLIENT_REQUESTOR = BTRIEVE_VERSION_TYPE_CLIENT_REQUESTOR,
      /// \brief Windows server engine.
      VERSION_TYPE_WINDOWS_SERVER_ENGINE = BTRIEVE_VERSION_TYPE_WINDOWS_SERVER_ENGINE, 
      /// \brief UNIX.
      VERSION_TYPE_UNIX = BTRIEVE_VERSION_TYPE_UNIX, 
      /// \brief Client engine.
      VERSION_TYPE_CLIENT_ENGINE = BTRIEVE_VERSION_TYPE_CLIENT_ENGINE, 
      /// \brief Unknown.
      VERSION_TYPE_UNKNOWN = BTRIEVE_VERSION_TYPE_UNKNOWN
   };

   /// \brief Return an alternate collation sequence mode as a string.
   /// \param[in] ACSMode The alternate collation sequence mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp ACSModeToString
   /// \return The string.
   static const char *ACSModeToString(ACSMode ACSMode);
   /// \brief Return a duplicate mode as a string.
   /// \param[in] duplicateMode The duplicate mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp DuplicateModeToString
   /// \return The string.
   static const char *DuplicateModeToString(DuplicateMode duplicateMode);
   /// \brief Return a data type as a string.
   /// \param[in] dataType The data type.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp DataTypeToString
   /// \return The string.
   static const char *DataTypeToString(DataType dataType);
   /// \brief Return a file version as a string.
   /// \param[in] fileVersion The file version.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp FileVersionToString
   /// \return The string.
   static const char *FileVersionToString(FileVersion fileVersion);
   /// \brief Return a free space threshold as a string.
   /// \param[in] freeSpaceThreshold The free space threshold.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp FreeSpaceThresholdToString
   /// \return The string.
   static const char *FreeSpaceThresholdToString(FreeSpaceThreshold freeSpaceThreshold);
   /// \brief Return an index as a string.
   /// \param[in] index The index.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp IndexToString
   /// \return The string.
   static const char *IndexToString(Index index);
   /// \brief Return a null key mode as a string.
   /// \param[in] nullKeyMode The null key mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp NullKeyModeToString
   /// \return The string.
   static const char *NullKeyModeToString(NullKeyMode nullKeyMode);
   /// \brief Return a page size as a string.
   /// \param[in] pageSize The page size.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp PageSizeToString
   /// \return The string.
   static const char *PageSizeToString(PageSize pageSize);
   /// \brief Return an record compression mode as a string.
   /// \param[in] recordCompressionMode The record compression mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp RecordCompressionModeToString
   /// \return The string.
   static const char *RecordCompressionModeToString(RecordCompressionMode recordCompressionMode);
   /// \brief Return a status code as a string.
   /// \param[in] statusCode The status code.
   /// \par \SNIPPET
   /// \snippet btest.cpp StatusCodeToString
   /// \return The string.
   static const char *StatusCodeToString(StatusCode statusCode);
   /// \brief Return a system data mode as a string.
   /// \param[in] systemDataMode The system data mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp SystemDataModeToString
   /// \return The string.
   static const char *SystemDataModeToString(SystemDataMode systemDataMode);
   /// \brief Return a version type as a string.
   /// \param[in] versionType The version type.
   /// \par \SNIPPET
   /// \snippet bversion.cpp VersionTypeToString
   /// \return The string.
   static const char *VersionTypeToString(VersionType versionType);
   /// \brief Return a page lock type as a string.
   /// \param[in] pageLockType The page lock type.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp PageLockTypeToString
   /// \return The string.
   static const char *PageLockTypeToString(PageLockType pageLockType);
   /// \brief Return a lock mode as a string.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp LockModeToString
   /// \return The string.
   static const char *LockModeToString(LockMode lockMode);
   /// \brief Return an owner mode as a string.
   /// \param[in] ownerMode The owner mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp OwnerModeToString
   /// \return The string.
   static const char *OwnerModeToString(OwnerMode ownerMode);
   /// \brief Return a variable length records mode as a string.
   /// \param[in] variableLengthRecordsMode The variable length records mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp VariableLengthRecordsModeToString
   /// \return The string.
   static const char *VariableLengthRecordsModeToString(VariableLengthRecordsMode variableLengthRecordsMode);
   /// \brief Convert a Unix Epoch based timestamp in microseconds to a TIMESTAMP.
   /// \param[in] microseconds The Unix Epoch timestamp in microseconds granularity.
   /// \return The Btrieve TIMESTAMP.
   static long long UnixEpochMicrosecondsToTimestamp(long long microseconds);
   /// \brief Convert a Btrieve TIMESTAMP to a Unix Epoch timestamp in microseconds.
   /// \param[in] timestamp The Btrieve TIMESTAMP.
   /// \return The Epoch based timestamp in microseconds.
   static long long TimestampToUnixEpochMicroseconds(long long timestamp);

private:
   Btrieve();
   ~Btrieve();
};

/// \brief The %Btrieve client class.
class LINKAGE BtrieveClient
{
public:
   /// \param[in] serviceAgentIdentifier The service agent identifier.
   /// \param[in] clientIdentifier The client identifier.
   /// \par \SNIPPET
   /// \snippet btest.cpp BtrieveClient
   BtrieveClient(int serviceAgentIdentifier, int clientIdentifier);
   BtrieveClient();
   ~BtrieveClient();

   /// \brief Get the version.
   /// \param[out] btrieveVersion The version.
   /// \param[in] btrieveFile The %Btrieve file.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetVersion
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetVersion(BtrieveVersion *btrieveVersion, BtrieveFile *btrieveFile = NULL);
   /// \brief Open a file.
   /// \param[out] btrieveFile The %Btrieve file.
   /// \param[in] fileName The file name.
   /// \param[in] ownerName The owner name.
   /// \param[in] openMode The open mode.
   /// \param[in] locationMode The location mode.
   /// \par \SNIPPET
   /// \snippet btest.cpp FileOpen
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileOpen(BtrieveFile *btrieveFile, const char *fileName, const char *ownerName, Btrieve::OpenMode openMode, Btrieve::LocationMode locationMode = Btrieve::LOCATION_MODE_NO_PREFERENCE);
   /// \brief Open a file.
   /// \param[out] btrieveFile The %Btrieve file.
   /// \param[in] fileName The file name.
   /// \param[in] ownerName The owner name.
   /// \param[in] openMode The open mode.
   /// \param[in] locationMode The location mode.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileOpen(BtrieveFile *btrieveFile, const wchar_t *fileName, const char *ownerName, Btrieve::OpenMode openMode, Btrieve::LocationMode locationMode = Btrieve::LOCATION_MODE_NO_PREFERENCE);

// Avoid Windows renaming of GetCurrentDirectory.
#ifdef GetCurrentDirectory
   #undef GetCurrentDirectory
#endif

   /// \brief Get the current directory.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \param[in] diskDrive The disk drive. \MUST_USE_DISK_DRIVE_DEFAULT
   /// \retval "!= NULL" The current directory.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *GetCurrentDirectory(Btrieve::DiskDrive diskDrive);
   #ifndef SWIG
   /// \brief Get the current directory.
   /// \note The method is available only in C++.
   /// \param[in] diskDrive The disk drive. \MUST_USE_DISK_DRIVE_DEFAULT
   /// \param[out] currentDirectory The current directory.
   /// \param[in] currentDirectorySize The current directory size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetCurrentDirectory(Btrieve::DiskDrive diskDrive, char *currentDirectory, int currentDirectorySize);
   #endif
   /// \brief Get the current directory.
   /// \param[in] diskDrive The disk drive. \MUST_USE_DISK_DRIVE_DEFAULT
   /// \param[out] currentDirectory The current directory.
   /// \param[in] currentDirectorySize The current directory size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetCurrentDirectory(Btrieve::DiskDrive diskDrive, wchar_t *currentDirectory, int currentDirectorySize);
   /// \brief Begin continuous operation.
   /// \param[in] pathNames The path names.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode ContinuousOperationBegin(const char *pathNames);
   /// \brief Begin continuous operation.
   /// \param[in] pathNames The path names.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode ContinuousOperationBegin(const wchar_t *pathNames);
   /// \brief End continuous operation.
   /// \param[in] pathNames The path names.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode ContinuousOperationEnd(const char *pathNames);
   /// \brief End continuous operation.
   /// \param[in] pathNames The path names.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode ContinuousOperationEnd(const wchar_t *pathNames);
   /// \brief Close a file.
   /// \param[in] btrieveFile The %Btrieve file.
   /// \par \SNIPPET
   /// \snippet btest.cpp FileClose
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileClose(BtrieveFile *btrieveFile);  
   /// \brief Create a file.
   /// \param[in] btrieveFileAttributes The file attributes.
   /// \param[in] fileName The file name.
   /// \param[in] createMode The create mode.
   /// \param[in] locationMode The location mode.
   /// \par \SNIPPET
   /// \snippet btest.cpp FileCreate
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileCreate(BtrieveFileAttributes *btrieveFileAttributes, const char *fileName, Btrieve::CreateMode createMode, Btrieve::LocationMode locationMode = Btrieve::LOCATION_MODE_NO_PREFERENCE);
   /// \brief Create a file.
   /// \param[in] btrieveFileAttributes The file attributes.
   /// \param[in] btrieveIndexAttributes The index attributes.
   /// \param[in] fileName The file name.
   /// \param[in] createMode The create mode.
   /// \param[in] locationMode The location mode.
   /// \par \SNIPPET
   /// \snippet bkeyonly.cpp FileCreate
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileCreate(BtrieveFileAttributes *btrieveFileAttributes, BtrieveIndexAttributes *btrieveIndexAttributes, const char *fileName, Btrieve::CreateMode createMode, Btrieve::LocationMode locationMode = Btrieve::LOCATION_MODE_NO_PREFERENCE);
   /// \brief Create a file.
   /// \param[in] btrieveFileAttributes The file attributes.
   /// \param[in] fileName The file name.
   /// \param[in] createMode The create mode.
   /// \param[in] locationMode The location mode.
   /// \par \SNIPPET
   /// \snippet btest.cpp FileCreate
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileCreate(BtrieveFileAttributes *btrieveFileAttributes, const wchar_t *fileName, Btrieve::CreateMode createMode, Btrieve::LocationMode locationMode = Btrieve::LOCATION_MODE_NO_PREFERENCE);
   /// \brief Create a file.
   /// \param[in] btrieveFileAttributes The file attributes.
   /// \param[in] btrieveIndexAttributes The index attributes.
   /// \param[in] fileName The file name.
   /// \param[in] createMode The create mode.
   /// \param[in] locationMode The location mode.
   /// \par \SNIPPET
   /// \snippet bkeyonly.cpp FileCreate
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileCreate(BtrieveFileAttributes *btrieveFileAttributes, BtrieveIndexAttributes *btrieveIndexAttributes, const wchar_t *fileName, Btrieve::CreateMode createMode, Btrieve::LocationMode locationMode = Btrieve::LOCATION_MODE_NO_PREFERENCE);
   /// \brief Delete a file.
   /// \param[in] fileName The file name.
   /// \par \SNIPPET
   /// \snippet btest.cpp FileDelete
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileDelete(const char *fileName);
   /// \brief Delete a file.
   /// \param[in] fileName The file name.
   /// \par \SNIPPET
   /// \snippet btest.cpp FileDelete
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileDelete(const wchar_t *fileName);
   /// \brief Rename a file.
   /// \param[in] existingFileName The existing file name.
   /// \param[in] newFileName The new file name.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileRename(const char *existingFileName, const char *newFileName);
   /// \brief Rename a file.
   /// \param[in] existingFileName The existing file name.
   /// \param[in] newFileName The new file name.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode FileRename(const wchar_t *existingFileName, const wchar_t *newFileName);
   /// \brief Get the last status code.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Login.
   /// \param[in] databaseURI The database uniform resource indicator.
   /// \par \SNIPPET
   /// \snippet bversion.cpp Login
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Login(const char *databaseURI);
   /// \brief Login.
   /// \param[in] databaseURI The database uniform resource indicator.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Login(const wchar_t *databaseURI);
   /// \brief Logout.
   /// \param[in] databaseURI The database uniform resource indicator.
   /// \par \SNIPPET
   /// \snippet bversion.cpp Logout
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Logout(const char *databaseURI);
   /// \brief Logout.
   /// \param[in] databaseURI The database uniform resource indicator.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Logout(const wchar_t *databaseURI);
   /// \brief Reset.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Reset();

// Avoid Windows renaming of SetCurrentDirectory.
#ifdef SetCurrentDirectory
   #undef SetCurrentDirectory
#endif

   /// \brief Set the current directory.
   /// \param[in] currentDirectory The current directory.
   /// \par \DESCRIPTION
   /// Current directory defaults to the current working directory.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetCurrentDirectory(const char *currentDirectory);
   /// \brief Set the current directory.
   /// \param[in] currentDirectory The current directory.
   /// \par \DESCRIPTION
   /// Current directory defaults to the current working directory.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetCurrentDirectory(const wchar_t *currentDirectory);
   /// \brief Stop.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Stop();
   /// \brief Abort a transaction.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode TransactionAbort();
   /// \brief Begin a transaction.
   /// \param[in] transactionMode The transaction mode.
   /// \param[in] lockMode The lock mode.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode TransactionBegin(Btrieve::TransactionMode transactionMode, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief End a transaction.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode TransactionEnd();
   /// \brief Get the service agent identifier.
   /// \retval ">= 0" The service agent identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveClient::GetLastStatusCode}
   int GetServiceAgentIdentifier();
   /// \brief Get the client identifier.
   /// \retval ">= 0" The client identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveClient::GetLastStatusCode}
   int GetClientIdentifier();
   /// \brief Create a collection.
   /// \param[in] collectionName The collection name.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode CollectionCreate(const char *collectionName);
   /// \brief Delete a collection.
   /// \param[in] collectionName The collection name.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode CollectionDelete(const char *collectionName);
   /// \brief Rename a collection.
   /// \param[in] existingCollectionName The existing collection name.
   /// \param[in] newCollectionName The new collection name.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode CollectionRename(const char *existingCollectionName, const char *newCollectionName);
   /// \brief Open a collection.
   /// \param[out] btrieveCollection The %Btrieve collection.
   /// \param[in] collectionName The collection name.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode CollectionOpen(BtrieveCollection *btrieveCollection, const char *collectionName);
   /// \brief Close a collection.
   /// \param[in] btrieveCollection The %Btrieve collection.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode CollectionClose(BtrieveCollection *btrieveCollection);  

private:
   btrieve_client_t btrieveClient;
};

/// \brief The %Btrieve file class.
///
/// \details In order to retrieve, update, and delete records in a %Btrieve file the cursor must be established. The following methods are among those used to establish the cursor:
/// - BtrieveFile::RecordRetrieve
/// - BtrieveFile::RecordRetrieveFirst
/// - BtrieveFile::RecordRetrieveLast
///
/// \details Once established, the cursor enables traversal over the records in the file. The following methods are among those used to traverse over the file:
/// - BtrieveFile::RecordRetrieveNext
/// - BtrieveFile::RecordRetrievePrevious
///
/// \details The cursor may be re-established repeatedly.
class LINKAGE BtrieveFile
{
   friend class BtrieveClient;

protected:
   btrieve_file_t GetBtrieveFile();
   btrieve_file_t *GetBtrieveFilePtr();
   BtrieveFile(btrieve_file_t btrieveFileIn);

public:
   /// \par \SNIPPET
   /// \snippet btest.cpp BtrieveFile
   /// \see BtrieveClient::FileOpen
   BtrieveFile();
   /// \see BtrieveClient::FileClose
   ~BtrieveFile();

   /// \brief Delete a record.
   /// \par \SNIPPET
   /// \snippet bkeyonly.cpp RecordDelete
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode RecordDelete();
   /// \brief Retrieve a record by fraction.
   /// \param[in] index An index or Btrieve::INDEX_NONE.
   /// \param[in] numerator The numerator given as 0 through denominator.
   /// \param[in] denominator The denominator.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp RecordRetrieveByFraction
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveByFraction(Btrieve::Index index, int numerator, int denominator, char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve a record by percentage.
   /// \param[in] index An index or Btrieve::INDEX_NONE.
   /// \param[in] percentage The percentage given as 0 through 10,000, corresponding to 0% through 100.00%.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp RecordRetrieveByPercentage
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveByPercentage(Btrieve::Index index, int percentage, char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve a record by cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in] index An index or Btrieve::INDEX_NONE.
   /// \param[in] cursorPosition The cursor position.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp RecordRetrieveByCursorPosition
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveByCursorPosition(Btrieve::Index index, long long cursorPosition, char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve a record using the given comparison, index, and key.
   /// \param[in] comparison The comparison. Btrieve::COMPARISON_NOT_EQUAL isn't supported.
   /// \param[in] index The index.
   /// \param[in] key The key.
   /// \param[in] keyLength The key length.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet btest.cpp RecordRetrieve
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieve(Btrieve::Comparison comparison, Btrieve::Index index, const char *key, int keyLength, char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve a key using the given comparison, index, and key.
   /// \param[in] comparison The comparison. Btrieve::COMPARISON_NOT_EQUAL isn't supported.
   /// \param[in] index The index.
   /// \param[in] key The key.
   /// \param[in] keyLength The key length.
   /// \par \SNIPPET
   /// \snippet bkeyonly.cpp KeyRetrieve
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode KeyRetrieve(Btrieve::Comparison comparison, Btrieve::Index index, const char *key, int keyLength);
   /// \brief Retrieve bulk next.
   /// \param[in] bulkRetrieveAttributes The bulk retrieve attributes.
   /// \param[out] bulkRetrieveResult The bulk retrieve result.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkRetrieveNext
   /// \par \CURSOR 
   /// The cursor must be established. The cursor is traversed forward to the last record examined.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode BulkRetrieveNext(BtrieveBulkRetrieveAttributes *bulkRetrieveAttributes, BtrieveBulkRetrieveResult *bulkRetrieveResult, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Get bulk previous.
   /// \param[in] bulkRetrieveAttributes The bulk retrieve attributes.
   /// \param[out] bulkRetrieveResult The bulk retrieve result.
   /// \param[in] lockMode The lock mode.
   /// \par \CURSOR 
   /// The cursor must be established. The cursor is traversed backwards to the last record examined.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode BulkRetrievePrevious(BtrieveBulkRetrieveAttributes *bulkRetrieveAttributes, BtrieveBulkRetrieveResult *bulkRetrieveResult, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Get the file information.
   /// \param[out] btrieveFileInformation The file information.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetInformation
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetInformation(BtrieveFileInformation *btrieveFileInformation);
   /// \brief Retrieve the first record.
   /// \param[in] index An index or Btrieve::INDEX_NONE.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp RecordRetrieveFirst
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveFirst(Btrieve::Index index, char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve the first key.
   /// \param[in] index The index.
   /// \param[out] key The key.
   /// \param[in] keySize The key size.
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode KeyRetrieveFirst(Btrieve::Index index, char *key, int keySize);
   /// \brief Get the numerator which best approximates the location of the cursor position within the file relative to the denominator.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in] cursorPosition The cursor position.
   /// \param[in] denominator The denominator.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp GetNumeratorCursorPosition
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval ">= 0" The numerator returned as 0 through denominator.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int GetNumerator(long long cursorPosition, int denominator);
   /// \brief Get the numerator which best approximates the location of the key within the index relative to the denominator.
   /// \param[in] index The index.
   /// \param[in] key The key.
   /// \param[in] keyLength The key length.
   /// \param[in] denominator The denominator.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp GetNumeratorIndex
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval ">= 0" The numerator returned as 0 through denominator.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int GetNumerator(Btrieve::Index index, const char *key, int keyLength, int denominator);
   /// \brief Retrieve the last record.
   /// \param[in] index An index or Btrieve::INDEX_NONE.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp RecordRetrieveLast
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveLast(Btrieve::Index index, char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve the last key.
   /// \param[in] index The index.
   /// \param[out] key The key.
   /// \param[in] keySize The key size.
   /// \par \CURSOR 
   /// The cursor is established.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode KeyRetrieveLast(Btrieve::Index index, char *key, int keySize);
   /// \brief Get the last status code.
   /// \par \SNIPPET
   /// \snippet btest.cpp GetLastStatusCode
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Retrieve the next key.
   /// \param[out] key The key.
   /// \param[in] keySize The key size.
   /// \par \CURSOR 
   /// The cursor must be established. The cursor is traversed forward one key.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode KeyRetrieveNext(char *key, int keySize);
   /// \brief Retrieve the next record.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp RecordRetrieveNext
   /// \par \CURSOR 
   /// The cursor must be established. The cursor is traversed forward one record.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveNext(char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Get the percentage which best approximates the location of the cursor position within the file.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in] cursorPosition The cursor position.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp GetPercentageCursorPosition
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval ">= 0" The percentage returned as 0 through 10,000, corresponding to 0% through 100.00%.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int GetPercentage(long long cursorPosition);
   /// \brief Get the percentage which best approximates the location of the key within the given index.
   /// \param[in] index The index.
   /// \param[in] key The key.
   /// \param[in] keyLength The key length.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp GetPercentageIndex
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval ">= 0" The percentage returned as 0 through 10,000, corresponding to 0% through 100.00%.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int GetPercentage(Btrieve::Index index, const char *key, int keyLength);
   /// \brief Get the cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \par \SNIPPET
   /// \snippet bpercentage.cpp GetCursorPosition
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval ">= 0" The cursor position.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   long long GetCursorPosition();
   /// \brief Retrieve the previous key.
   /// \param[out] key The key.
   /// \param[in] keySize The key size.
   /// \par \CURSOR 
   /// The cursor must be established. The cursor is traversed backward one key.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode KeyRetrievePrevious(char *key, int keySize);
   /// \brief Retrieve the previous record.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \param[in] lockMode The lock mode.
   /// \par \CURSOR 
   /// The cursor must be established. The cursor is traversed backward one record.
   /// \par \CURRENT_OFFSET
   /// The current offset is destroyed.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN \DATA_LENGTH_ERROR
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrievePrevious(char *record, int recordSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve a record chunk.
   /// \param[in] offset The offset.
   /// \param[in] length The length.
   /// \param[out] chunk The chunk.
   /// \param[in] chunkSize The chunk size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet btestchunk.cpp RecordRetrieveChunk
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is established at the end of the retrieved chunk.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ You may retrieve multiple chunks.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveChunk(int offset, int length, char *chunk, int chunkSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Retrieve a record chunk at the current offset.
   /// \param[in] length The length.
   /// \param[out] chunk The chunk.
   /// \param[in] chunkSize The chunk size.
   /// \param[in] lockMode The lock mode.
   /// \par \SNIPPET
   /// \snippet btestchunk.cpp RecordRetrieveChunkNoOffset
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset must be established and is then traversed forward to the end of the retrieved chunk.
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ You may retrieve multiple chunks.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFile::GetLastStatusCode}
   int RecordRetrieveChunk(int length, char *chunk, int chunkSize, Btrieve::LockMode lockMode = Btrieve::LOCK_MODE_NONE);
   /// \brief Create an index.
   /// \param[in] btrieveIndexAttributes The index attributes.
   /// \par \SNIPPET
   /// \snippet btest.cpp IndexCreate
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode IndexCreate(BtrieveIndexAttributes *btrieveIndexAttributes);
   /// \brief Drop an index.
   /// \param[in] index The index.
   /// \par \CURSOR 
   /// If the cursor index is dropped the cursor is destroyed. Otherwise, the cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode IndexDrop(Btrieve::Index index);
   /// \brief Create a record.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in,out] record The record. If the current record contains an autoincrement key segment then the passed in record may be modifed.
   /// \param[in] recordLength The record length. Record length is limited to Btrieve::MAXIMUM_RECORD_LENGTH. See BtrieveFile::RecordAppendChunk for creating records greater than Btrieve::MAXIMUM_RECORD_LENGTH in length.
   /// \par \SNIPPET
   /// \snippet btest.cpp RecordCreate
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode RecordCreate(char *record, int recordLength);
   /// \brief Bulk create.
   /// \param[in] btrieveBulkCreatePayload The bulk create payload.
   /// \param[out] btrieveBulkCreateResult The bulk create result.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkCreate
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode BulkCreate(BtrieveBulkCreatePayload *btrieveBulkCreatePayload, BtrieveBulkCreateResult *btrieveBulkCreateResult);
   /// \brief Set the owner.
   /// \param[in] ownerMode The owner mode.
   /// \param[in] ownerName The owner name.
   /// \param[in] ownerNameAgain The owner name (again).
   /// \param[in] useLongOwnerName Use a long owner name?
   /// \par \DESCRIPTION
   /// Owner mode defaults to Btrieve::OWNER_MODE_NONE.
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetOwner(Btrieve::OwnerMode ownerMode, const char *ownerName = NULL, const char *ownerNameAgain = NULL, bool useLongOwnerName = true);
   /// \brief Truncate a record.
   /// \param[in] offset The offset.
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is established at the end of the record.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   Btrieve::StatusCode RecordTruncate(int offset);
   /// \brief Truncate a record at the current offset.
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset must be established and remains unchanged.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   Btrieve::StatusCode RecordTruncate();
   /// \brief Unlock a record or records.
   /// \param[in] unlockMode The unlock mode.
   /// \par \SNIPPET
   /// \snippet block.cpp RecordUnlock
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode RecordUnlock(Btrieve::UnlockMode unlockMode);
   /// \brief Unlock the cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in] cursorPosition The cursor position.
   /// \par \CURSOR 
   /// The cursor is unaffected.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode UnlockCursorPosition(long long cursorPosition);
   /// \brief Update a record.
   /// \param[in] record The record.
   /// \param[in] recordLength The record length. Record length is limited to Btrieve::MAXIMUM_RECORD_LENGTH. See BtrieveFile::RecordUpdateChunk for updating records greater than Btrieve::MAXIMUM_RECORD_LENGTH in length.
   /// \par \SNIPPET
   /// \snippet block.cpp RecordUpdate
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is unaffected.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode RecordUpdate(const char *record, int recordLength);
   /// \brief Append a record chunk.
   /// \param[in] chunk The chunk.
   /// \param[in] chunkLength The chunk length.
   /// \par \SNIPPET
   /// \snippet btestappend.cpp RecordAppendChunk
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is established at the end of the appended chunk.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode RecordAppendChunk(const char *chunk, int chunkLength);
   /// \brief Update a record chunk.
   /// \param[in] offset The offset.
   /// \param[in] chunk The chunk.
   /// \param[in] chunkLength The chunk length.
   /// \par \SNIPPET
   /// \snippet btestchunk.cpp RecordUpdateChunk
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset is established at the end of the updated chunk.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   Btrieve::StatusCode RecordUpdateChunk(int offset, const char *chunk, int chunkLength);
   /// \brief Update a record chunk at the current offset.
   /// \param[in] chunk The chunk.
   /// \param[in] chunkLength The chunk length.
   /// \par \SNIPPET
   /// \snippet btestchunk.cpp RecordUpdateChunkNoOffset
   /// \par \CURSOR 
   /// The cursor is unaffected but must be established.
   /// \par \CURRENT_OFFSET
   /// The current offset must be established and is then traversed forward to the end of the updated chunk.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   Btrieve::StatusCode RecordUpdateChunk(const char *chunk, int chunkLength);

private:
   btrieve_file_t btrieveFile;
};

/// \brief The %Btrieve file attributes class.
class LINKAGE BtrieveFileAttributes
{
   friend class BtrieveClient;

protected:
   btrieve_file_attributes_t GetBtrieveFileAttributes();

public:
   /// \par \SNIPPET
   /// \snippet btest.cpp BtrieveFileAttributes
   BtrieveFileAttributes();
   ~BtrieveFileAttributes();

   /// \brief Set balanced indexes.
   /// \param[in] enableBalancedIndexes Enable balanced indexes?
   /// \par \DESCRIPTION
   /// Balanced indexes are disabled by default.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetBalancedIndexes
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetBalancedIndexes(bool enableBalancedIndexes);
   /// \brief Set record compression mode.
   /// \param[in] recordCompressionMode The record compression mode.
   /// \par \DESCRIPTION
   /// Record compression defaults to Btrieve::RECORD_COMPRESSION_MODE_NONE.
   /// Compression mode blank truncation requires variable length records be enabled.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetRecordCompressionMode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetRecordCompressionMode(Btrieve::RecordCompressionMode recordCompressionMode);
   /// \brief Set the reserved duplicate pointer count.
   /// \param[in] reservedDuplicatePointerCount The reserved duplicate pointer count. The reserved duplicate pointer count must be between 0 and 119, inclusive.
   /// \par \DESCRIPTION
   /// Reserved duplicate pointer count defaults to zero.
   /// The maximum reserved duplicate pointer count may be less than 119 depending on file version and page size.
   /// For example, a file version of Btrieve::FILE_VERSION_9_0 and page size of Btrieve::PAGE_SIZE_3584 allows for a maximum reserved duplicate pointer count of 54.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetReservedDuplicatePointerCount
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetReservedDuplicatePointerCount(int reservedDuplicatePointerCount);
   /// \brief Set the file version.
   /// \param[in] fileVersion The file version.
   /// \par \DESCRIPTION
   /// File version defaults to Btrieve::FILE_VERSION_DEFAULT. 
   /// A file version of Btrieve::FILE_VERSION_6_0 is mapped to Btrieve::FILE_VERSION_6_1.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetFileVersion
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetFileVersion(Btrieve::FileVersion fileVersion);
   /// \brief Set the free space threshold.
   /// \param[in] freeSpaceThreshold The free space threshold.
   /// \par \DESCRIPTION
   /// Free space threshold defaults to Btrieve::FREE_SPACE_THRESHOLD_DEFAULT.
   /// The free space threshold setting is ignored unless variable length records are enabled.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetFreeSpaceThreshold
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetFreeSpaceThreshold(Btrieve::FreeSpaceThreshold freeSpaceThreshold);
   /// \brief Set the page size.
   /// \param[in] pageSize The page size.
   /// \param[in] enablePageCompression Enable page compression?
   /// \par \DESCRIPTION
   /// Page size defaults to Btrieve::PAGE_SIZE_4096.
   /// Page compression is disabled by default and requires file version Btrieve::FILE_VERSION_9_5 or greater.
   /// Not all page sizes are valid for all file versions.
   /// Pages sizes greater than 4096 require file version Btrieve::FILE_VERSION_9_0 or greater.
   /// Pages sizes which are unsupported for a particular file version will be rounded up to the next supported size.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetPageSize
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetPageSize(Btrieve::PageSize pageSize, bool enablePageCompression = false);
   /// \brief Set the fixed record length.
   /// \param[in] fixedRecordLength The fixed record length. The fixed record length must be between 1 and Btrieve::MAXIMUM_RECORD_LENGTH, inclusive.
   /// \par \DESCRIPTION
   /// Fixed record length defaults to zero.
   /// \par \SNIPPET
   /// \snippet btest.cpp SetFixedRecordLength
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetFixedRecordLength(int fixedRecordLength);
   /// \brief Set the preallocated page count.
   /// \param[in] preallocatedPageCount The preallocated page count. The preallocated page count must be between 0 and 65535, inclusive.
   /// \par \DESCRIPTION
   /// Preallocated page count defaults to zero.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetPreallocatedPageCount
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetPreallocatedPageCount(int preallocatedPageCount);
   /// \brief Set the system data mode.
   /// \param[in] systemDataMode The system data mode.
   /// \par \DESCRIPTION
   /// System data mode defaults to Btrieve::SYSTEM_DATA_MODE_DEFAULT.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetSystemDataMode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetSystemDataMode(Btrieve::SystemDataMode systemDataMode);
   /// \brief Set the variable length records mode.
   /// \param[in] variableLengthRecordsMode The variable length records mode.
   /// \par \DESCRIPTION
   /// Variable length records mode defaults to Btrieve::VARIABLE_LENGTH_RECORDS_MODE_NO.
   /// \par \SNIPPET
   /// \snippet bfileattributes.cpp SetVariableLengthRecordsMode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetVariableLengthRecordsMode(Btrieve::VariableLengthRecordsMode variableLengthRecordsMode);
   /// \brief Set key only.
   /// \param[in] enableKeyOnly Enable key only?
   /// \par \DESCRIPTION
   /// Key only is disabled by default.
   /// Enabling key only will cause the system data mode to be ignored.
   /// \par \SNIPPET
   /// \snippet bkeyonly.cpp SetKeyOnly
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetKeyOnly(bool enableKeyOnly);

private:
   btrieve_file_attributes_t btrieveFileAttributes;
};

/// \brief The %Btrieve file information class.
class LINKAGE BtrieveFileInformation
{
   friend class BtrieveFile;

protected:
   btrieve_file_information_t GetBtrieveFileInformation();

public:
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp BtrieveFileInformation
   /// \see BtrieveFile::GetInformation
   BtrieveFileInformation();
   ~BtrieveFileInformation();

   /// \brief Get the last status code.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp FileInformationGetLastStatusCode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Get the file version.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetFileVersion
   /// \retval "!= Btrieve::FILE_VERSION_UNKNOWN" The file version.
   /// \retval "= Btrieve::FILE_VERSION_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::FileVersionToString
   Btrieve::FileVersion GetFileVersion();
   /// \brief Get the free space threshold.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetFreeSpaceThreshold
   /// \retval "!= Btrieve::FREE_SPACE_THRESHOLD_UNKNOWN" The free space threshold.
   /// \retval "= Btrieve::FREE_SPACE_THRESHOLD_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::FreeSpaceThresholdToString
   Btrieve::FreeSpaceThreshold GetFreeSpaceThreshold();
   /// \brief Get the page size.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetPageSize
   /// \retval "!= Btrieve::PAGE_SIZE_UNKNOWN" The page size.
   /// \retval "= Btrieve::PAGE_SIZE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::PageSizeToString
   Btrieve::PageSize GetPageSize();
   /// \brief Get the system data mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSystemDataMode
   /// \retval "!= Btrieve::SYSTEM_DATA_MODE_UNKNOWN" \SUCCESS
   /// \retval "= Btrieve::SYSTEM_DATA_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   Btrieve::SystemDataMode GetSystemDataMode();
   /// \brief Get a key segment.
   /// \param[in] btrieveKeySegment The key segment.
   /// \param[in] keySegmentNumber The key segment number. The number is one-based.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetKeySegment
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetKeySegment(BtrieveKeySegment *btrieveKeySegment, int keySegmentNumber);
   /// \brief Get balanced indexes.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetBalancedIndexes
   /// \retval "> 0" Balanced indexes enabled.
   /// \retval 0 Balanced indexes disabled.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetBalancedIndexes();
   /// \brief Get the record compression mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetRecordCompressionMode
   /// \retval "!= Btrieve::RECORD_COMPRESSION_MODE_UNKNOWN" \SUCCESS
   /// \retval "= Btrieve::RECORD_COMPRESSION_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   Btrieve::RecordCompressionMode GetRecordCompressionMode();
   /// \brief Get key only.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetKeyOnly
   /// \retval "> 0" File is key only.
   /// \retval 0 File isn't key only.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetKeyOnly();
   /// \brief Get page compression.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetPageCompression
   /// \retval "> 0" Page compression enabled.
   /// \retval 0 Page compression disabled.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetPageCompression();
   /// \brief Get page preallocation.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetPagePreallocation
   /// \retval "> 0" Page preallocation enabled.
   /// \retval 0 Page preallocation disabled.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetPagePreallocation();
   /// \brief Get the variable length records mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetVariableLengthRecordsMode
   /// \retval "!= Btrieve::SYSTEM_DATA_MODE_UNKNOWN" \SUCCESS
   /// \retval "= Btrieve::SYSTEM_DATA_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   Btrieve::VariableLengthRecordsMode GetVariableLengthRecordsMode();
   /// \brief Get the unused duplicate pointer count.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetUnusedDuplicatePointerCount
   /// \retval ">= 0" The unused duplicate pointer count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetUnusedDuplicatePointerCount();
   /// \brief Get the index count.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetIndexCount
   /// \retval ">= 0" The index count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetIndexCount();
   /// \brief Get the fixed record length.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetFixedRecordLength
   /// \retval ">= 0" The fixed record length.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetFixedRecordLength();
   /// \brief Get the record count.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetRecordCount
   /// \retval ">= 0" The record count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   long long GetRecordCount();
   /// \brief Get segmented.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSegmented
   /// \retval "> 0" File is segmented.
   /// \retval 0 File isn't segmented.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetSegmented();
   /// \brief Get the unused page count.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetUnusedPageCount
   /// \retval ">= 0" The unused page count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetUnusedPageCount();
   /// \brief Get the log index.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLogIndex
   /// \retval "!= Btrieve::INDEX_UNKNOWN" The index.
   /// \retval "= Btrieve::INDEX_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::IndexToString
   Btrieve::Index GetLogIndex();
   /// \brief Get loggable.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLoggable
   /// \retval "> 0" File is loggable.
   /// \retval 0 File isn't loggable.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLoggable();
   /// \brief Get system index present.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSystemIndexPresent
   /// \retval "> 0" The system index is present.
   /// \retval 0 The system index isn't present.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetSystemIndexPresent();
   /// \brief Get the system index size.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSystemIndexSize
   /// \retval ">= 0" The system index size.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetSystemIndexSize();
   /// \brief Get system index used.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSystemIndexUsed
   /// \retval "> 0" The system index is used.
   /// \retval 0 The system index isn't used.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetSystemIndexUsed();
   /// \brief Get the system index version.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSystemIndexVersion
   /// \retval ">= 0" The system index version.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetSystemIndexVersion();
   /// \brief Get the duplicate record conflict cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetDuplicateRecordConflictCursorPosition
   /// \retval ">= 0" The duplicate record conflict cursor position.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   long long GetDuplicateRecordConflictCursorPosition();
   /// \brief Get the duplicate record conflict index.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetDuplicateRecordConflictIndex
   /// \retval "!= Btrieve::INDEX_UNKNOWN" The duplicate record conflict index.
   /// \retval "= Btrieve::INDEX_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::IndexToString
   Btrieve::Index GetDuplicateRecordConflictIndex();
   /// \brief Get the identifier.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetIdentifier
   /// \retval ">= 0" The identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetIdentifier();
   /// \brief Get the handle count.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetHandleCount
   /// \retval ">= 0" The handle count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetHandleCount();
   /// \brief Get the open timestamp.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetOpenTimestamp
   /// \retval ">= 0" The open timestamp.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetOpenTimestamp();
   /// \brief Get the usage count.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetUsageCount
   /// \retval ">= 0" The usage count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetUsageCount();
   /// \brief Get explicit locks.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetExplicitLocks
   /// \retval "> 0" Explicit locks are active.
   /// \retval 0 Explicit locks are not active.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetExplicitLocks();
   /// \brief Get client transactions.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetClientTransactions
   /// \retval "> 0" Client transactions are active.
   /// \retval 0 Client transactions are not active.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetClientTransactions();
   /// \brief Get read only.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetReadOnly
   /// \retval "> 0" The file is opened read only.
   /// \retval 0 The file isn't opened read only.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetReadOnly();
   /// \brief Get continuous operation.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetContinuousOperation
   /// \retval "> 0" The file is in continuous operation.
   /// \retval 0 The file isn't in continuous operation.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetContinuousOperation();
   /// \brief Get referential integrity constraints.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetReferentialIntegrityConstraints
   /// \retval "> 0" The file has referential integrity constraints.
   /// \retval 0 The file doesn't have referential integrity constraints.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetReferentialIntegrityConstraints();
   /// \brief Get the owner mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetOwnerMode
   /// \retval "!= Btrieve::OWNER_MODE_UNKNOWN" The owner mode.
   /// \retval "= Btrieve::OWNER_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::OwnerModeToString
   Btrieve::OwnerMode GetOwnerMode();
   /// \brief Get wrong owner.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetWrongOwner
   /// \retval "> 0" The file was opened with an incorrect owner name.
   /// \retval 0 The file wasn't opened with an incorrect owner name.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetWrongOwner();
   /// \brief Get the gateway major version.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetGatewayMajorVersion
   /// \retval ">= 0" The gateway major version.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetGatewayMajorVersion();
   /// \brief Get the gateway minor version.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetGatewayMinorVersion
   /// \retval ">= 0" The gateway minor version.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetGatewayMinorVersion();
   /// \brief Get the gateway patch level.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetGatewayPatchLevel
   /// \retval ">= 0" The gateway patch version.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetGatewayPatchLevel();
   /// \brief Get the gateway platform.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetGatewayPlatform
   /// \retval ">= 0" The gateway platform.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetGatewayPlatform();
   /// \brief Get the gateway name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetGatewayName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *GetGatewayName();
   #ifndef SWIG
   /// \brief Get the gateway name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetGatewayName(char *name, int nameSize);
   #endif
   /// \brief Get lock owner implicit lock.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerImplicitLock
   /// \retval "> 0" The lock owner has an implicit lock.
   /// \retval 0 The lock owner doesn't have an implicit lock.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerImplicitLock();
   /// \brief Get lock owner file lock.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerFileLock
   /// \retval "> 0" The lock owner has a file lock.
   /// \retval 0 The lock owner doesn't have a file lock.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerFileLock();
   /// \brief Get lock owner record lock.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerRecordLock
   /// \retval "> 0" The lock owner has a record lock.
   /// \retval 0 The lock owner doesn't have a record lock.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerRecordLock();
   /// \brief Get lock owner same process.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerSameProcess
   /// \retval "> 0" The lock owner is the same process.
   /// \retval 0 The lock owner isn't the same process.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerSameProcess();
   /// \brief Get lock owner write no wait.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerWriteNoWait
   /// \retval "> 0" The lock owner is performing a write with no wait.
   /// \retval 0 The lock owner isn't performing a write with no wait.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerWriteNoWait();
   /// \brief Get lock owner write hold.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerWriteHold
   /// \retval "> 0" The lock owner has a write hold.
   /// \retval 0 The lock owner doesn't have a write hold.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerWriteHold();
   /// \brief Get the lock owner time in transaction.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerTimeInTransaction
   /// \retval ">= 0" The lock owner time in transaction.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerTimeInTransaction();
   /// \brief Get the lock owner transaction level.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerTransactionLevel
   /// \retval ">= 0" The lock owner transaction level.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerTransactionLevel();
   /// \brief Get the lock owner name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *GetLockOwnerName();
   #ifndef SWIG
   /// \brief Get the lock owner name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLockOwnerName(char *name, int nameSize);
   #endif
   /// \brief Get the lock owner service agent identifier.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerServiceAgentIdentifier
   /// \retval ">= 0" The lock owner service agent identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerServiceAgentIdentifier();
   /// \brief Get the lock owner client identifier.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerClientIdentifier
   /// \retval ">= 0" The lock owner client identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetLockOwnerClientIdentifier();
   /// \brief Get the lock owner explcit lock mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerExplicitLockMode
   /// \retval "!= Btrieve::LOCK_MODE_UNKNOWN" The lock owner explcit lock mode.
   /// \retval "= Btrieve::LOCK_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::LockModeToString
   Btrieve::LockMode GetLockOwnerExplicitLockMode();
   /// \brief Get the lock owner page lock type.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerPageLockType
   /// \retval "!= Btrieve::PAGE_LOCK_TYPE_UNKNOWN" The lock owner page lock type.
   /// \retval "= Btrieve::PAGE_LOCK_TYPE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::PageLockTypeToString
   Btrieve::PageLockType GetLockOwnerPageLockType();
   /// \brief Get the lock owner index.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLockOwnerIndex
   /// \retval "!= Btrieve::INDEX_UNKNOWN" The lock owner index.
   /// \retval "= Btrieve::INDEX_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   /// \see Btrieve::IndexToString
   Btrieve::Index GetLockOwnerIndex();
   /// \brief Get the referential integrity file name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetReferentialIntegrityFileName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *GetReferentialIntegrityFileName();
   #ifndef SWIG
   /// \brief Get the referential integrity file name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetReferentialIntegrityFileName(char *name, int nameSize);
   #endif
   /// \brief Get the referential integrity operation code.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetReferentialIntegrityOperationCode
   /// \retval ">= 0" The operation code.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetReferentialIntegrityOperationCode();
   /// \brief Get the referential integrity cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetReferentialIntegrityCursorPosition
   /// \retval ">= 0" The cursor position.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   long long GetReferentialIntegrityCursorPosition();
   /// \brief Get the segment count.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSegmentCount
   /// \retval ">= 0" The exists count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
   int GetSegmentCount();
   /// \brief Get the segment file name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \param[in] segmentFileNumber The segment file number.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSegmentFileName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *GetSegmentFileName(int segmentFileNumber);
   #ifndef SWIG
   /// \brief Get the segment file name.
   /// \note The method is available only in C++.
   /// \param[in] segmentFileNumber The segment file number.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetSegmentFileName(int segmentFileNumber, char *name, int nameSize);
   #endif

   // TODO: Coalesce some of the following.
   /// \brief Get security handle trusted.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleTrusted
   /// \retval "> 0" Security handle trusted.
   /// \retval 0 Security handle not trusted.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleTrusted();
   /// \brief Get security handle implicit.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleImplicit
   /// \retval "> 0" Security handle implicit.
   /// \retval 0 Security handle not implicit.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleImplicit();
   /// \brief Get security handle explicit.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleExplicit
   /// \retval "> 0" Security handle explicit.
   /// \retval 0 Security handle not explicit.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleExplicit();
   /// \brief Get security handle authentication by database.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleAuthenticationByDatabase
   /// \retval "> 0" Security handle authentication by database.
   /// \retval 0 Security handle not authentication by database.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleAuthenticationByDatabase();
   /// \brief Get security handle authorization by database.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleAuthorizationByDatabase
   /// \retval "> 0" Security handle authorization by database.
   /// \retval 0 Security handle not authorization by database.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleAuthorizationByDatabase();
   /// \brief Get security handle Windows named pipe.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleWindowsNamedPipe
   /// \retval "> 0" Security handle Windows named pipe.
   /// \retval 0 Security handle not Windows named pipe.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleWindowsNamedPipe();
   /// \brief Get security handle workgroup.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleWorkgroup
   /// \retval "> 0" Security handle workgroup.
   /// \retval 0 Security handle not workgroup.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleWorkgroup();
   /// \brief Get security handle Btpasswd.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleBtpasswd
   /// \retval "> 0" Security handle Btpasswd.
   /// \retval 0 Security handle not Btpasswd.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleBtpasswd();
   /// \brief Get security handle PAM (Pluggable Authentication Module).
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandlePAM
   /// \retval "> 0" Security handle PAM.
   /// \retval 0 Security handle not PAM.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandlePAM();
   /// \brief Get security handle RTSS  (Runtime Server Support) complete.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleRTSSComplete
   /// \retval "> 0" Security handle RTSS complete.
   /// \retval 0 Security handle not RTSS complete.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleRTSSComplete();
   /// \brief Get security handle RTSS  (Runtime Server Support) preautorized.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleRTSSPreauthorized
   /// \retval "> 0" Security handle RTSS preautorized.
   /// \retval 0 Security handle not RTSS preautorized.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleRTSSPreauthorized();
   /// \brief Get security handle RTSS  (Runtime Server Support) disabled.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleRTSSDisabled
   /// \retval "> 0" Security handle RTSS disabled.
   /// \retval 0 Security handle not RTSS disabled.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityHandleRTSSDisabled();
   /// \brief Get security current database trusted.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseTrusted
   /// \retval "> 0" Security current database trusted.
   /// \retval 0 Security current database not trusted.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseTrusted();
   /// \brief Get security current database implicit.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseImplicit
   /// \retval "> 0" Security current database implicit.
   /// \retval 0 Security current database not implicit.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseImplicit();
   /// \brief Get security current database explicit.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseExplicit
   /// \retval "> 0" Security current database explicit.
   /// \retval 0 Security current database not explicit.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseExplicit();
   /// \brief Get security current database authentication by database.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseAuthenticationByDatabase
   /// \retval "> 0" Security current database authentication by database.
   /// \retval 0 Security current database not authentication by database.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseAuthenticationByDatabase();
   /// \brief Get security current database authorization by database.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseAuthorizationByDatabase
   /// \retval "> 0" Security current database authorization by database.
   /// \retval 0 Security current database not authorization by database.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseAuthorizationByDatabase();
   /// \brief Get security current database Windows named pipe.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseWindowsNamedPipe
   /// \retval "> 0" Security current database Windows named pipe.
   /// \retval 0 Security current database not Windows named pipe.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseWindowsNamedPipe();
   /// \brief Get security current database workgroup.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseWorkgroup
   /// \retval "> 0" Security current database workgroup.
   /// \retval 0 Security current database not workgroup.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseWorkgroup();
   /// \brief Get security current database Btpasswd.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseBtpasswd
   /// \retval "> 0" Security current database Btpasswd.
   /// \retval 0 Security current database not Btpasswd.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseBtpasswd();
   /// \brief Get security current database PAM (Pluggable Authentication Module).
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabasePAM
   /// \retval "> 0" Security current database PAM.
   /// \retval 0 Security current database not PAM.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabasePAM();
   /// \brief Get security current database RTSS (Runtime Server Support) complete.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseRTSSComplete
   /// \retval "> 0" Security current database RTSS complete.
   /// \retval 0 Security current database not RTSS complete.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseRTSSComplete();
   /// \brief Get security current database RTSS  (Runtime Server Support) preauthorized.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseRTSSPreauthorized
   /// \retval "> 0" Security current database RTSS preauthorized.
   /// \retval 0 Security current database not RTSS preauthorized.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseRTSSPreauthorized();
   /// \brief Get security current database RTSS  (Runtime Server Support) disabled.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseRTSSDisabled
   /// \retval "> 0" Security current database RTSS disabled.
   /// \retval 0 Security current database not RTSS disabled.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityCurrentDatabaseRTSSDisabled();
   /// \brief Get security permission no rights.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionNoRights
   /// \retval "> 0" Security permission no rights.
   /// \retval 0 Security permission rights.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionNoRights();
   /// \brief Get security permission open.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionOpen
   /// \retval "> 0" Security permission open.
   /// \retval 0 Security permission no open.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionOpen();
   /// \brief Get security permission read.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionRead
   /// \retval "> 0" Security permission read.
   /// \retval 0 Security permission no read.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionRead();
   /// \brief Get security permission file create.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionCreateFile
   /// \retval "> 0" Security permission file create.
   /// \retval 0 Security permission no file create.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionCreateFile();
   /// \brief Get security permission update.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionUpdate
   /// \retval "> 0" Security permission update.
   /// \retval 0 Security permission no update.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionUpdate();
   /// \brief Get security permission record create.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionCreateRecord
   /// \retval "> 0" Security permission record create.
   /// \retval 0 Security permission no record create.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionCreateRecord();
   /// \brief Get security permission delete.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionDelete
   /// \retval "> 0" Security permission delete.
   /// \retval 0 Security permission no delete.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionDelete();
   /// \brief Get security permission execute.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionExecute
   /// \retval "> 0" Security permission execute.
   /// \retval 0 Security permission no execute.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionExecute();
   /// \brief Get security permission alter.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionAlter
   /// \retval "> 0" Security permission alter.
   /// \retval 0 Security permission no alter.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionAlter();
   /// \brief Get security permission refer.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionRefer
   /// \retval "> 0" Security permission refer.
   /// \retval 0 Security permission no refer.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionRefer();
   /// \brief Get security permission create view.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionCreateView
   /// \retval "> 0" Security permission create view.
   /// \retval 0 Security permission no create view.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionCreateView();
   /// \brief Get security permission create stored procedure.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityPermissionCreateStoredProcedure
   /// \retval "> 0" Security permission create stored procedure.
   /// \retval 0 Security permission no create stored procedure.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveFileInformation::GetLastStatusCode}
	int GetSecurityPermissionCreateStoredProcedure();
   /// \brief Get the security handle database name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleDatabaseName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
	const char *GetSecurityHandleDatabaseName();
   #ifndef SWIG
   /// \brief Get the security handle database name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
	Btrieve::StatusCode GetSecurityHandleDatabaseName(char *name, int nameSize);
   #endif
   /// \brief Get the security handle table name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleTableName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
	const char *GetSecurityHandleTableName();
   #ifndef SWIG
   /// \brief Get the security handle table name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
	Btrieve::StatusCode GetSecurityHandleTableName(char *name, int nameSize);
   #endif
   /// \brief Get the security handle user name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityHandleUserName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
	const char *GetSecurityHandleUserName();
   #ifndef SWIG
   /// \brief Get the security handle user name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
	Btrieve::StatusCode GetSecurityHandleUserName(char *name, int nameSize);
   #endif
   /// \brief Get the security current database name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentDatabaseName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
	const char *GetSecurityCurrentDatabaseName();
   #ifndef SWIG
   /// \brief Get the security current database name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
	Btrieve::StatusCode GetSecurityCurrentDatabaseName(char *name, int nameSize);
   #endif
   /// \brief Get the security current user name.
   /// \note This method is not thread safe. The string returned will be overwritten on subsequent calls.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetSecurityCurrentUserName
   /// \retval "!= NULL" The name.
   /// \retval NULL \ERROR_HAS_OCCURRED
	const char *GetSecurityCurrentUserName();
   #ifndef SWIG
   /// \brief Get the security current user name.
   /// \note The method is available only in C++.
   /// \param[out] name The name.
   /// \param[in] nameSize The name size.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
	Btrieve::StatusCode GetSecurityCurrentUserName(char *name, int nameSize);
   #endif

private:
   btrieve_file_information_t btrieveFileInformation;
};

/// \brief The %Btrieve filter class.
class LINKAGE BtrieveFilter
{
   friend class BtrieveBulkRetrieveAttributes;

protected:
   btrieve_filter_t GetBtrieveFilter();

public:
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BtrieveFilter
   BtrieveFilter();
   ~BtrieveFilter();

   /// \brief Set the comparison.
   /// \param[in] comparison The comparison.
   /// \par \DESCRIPTION
   /// Comparison defaults to Btrieve::COMPARISON_NONE.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp SetComparison
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetComparison(Btrieve::Comparison comparison);
   /// \brief Set the comparison constant.
   /// \param[in] constant The comparison constant.
   /// \param[in] constantLength The comparison constant length. Comparison constant length is limited to Btrieve::MAXIMUM_KEY_LENGTH.
   /// \par \DESCRIPTION
   /// Filters have no comparison constant initially.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp SetComparisonConstant
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetComparisonConstant(const char *constant, int constantLength);
   /// \brief Set the comparison field.
   /// \param[in] offset The comparison field offset. Offset must be less than Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \par \DESCRIPTION
   /// Filters have no comparison field initially.
   /// \par \SNIPPET
   /// \snippet bfilter.cpp SetComparisonField
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetComparisonField(int offset);
   /// \brief Set the field.
   /// \param[in] offset The offset. Offset must be less than Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \param[in] length The length. Length is limited to Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \param[in] dataType The data type. Btrieve::DATA_TYPE_LEGACY_BINARY and Btrieve::DATA_TYPE_LEGACY_STRING are not supported.
   /// \par \DESCRIPTION
   /// Filters have no field initially.
   /// Offset plus length is limited to Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp SetField
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetField(int offset, int length, Btrieve::DataType dataType);
   /// \brief Set the code page name to be used for the comparison types Like or Not Like.
   /// \param[in] name The name of the code page.
   /// \par \DESCRIPTION
   /// Supply the name of the code page to be used for string comparisons for the Like/Not Like comparisons.  The comparison constant and data must use the same code page for accurate comparison.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetLikeCodePageName(const char *name);
   /// \brief Set the field connector.
   /// \param[in] connector The connector.
   /// \par \DESCRIPTION
   /// Field connector defaults to Btrieve::CONNECTOR_LAST.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetConnector(Btrieve::Connector connector);
   /// \brief Set the alternate collation sequence mode.
   /// \note This method replaced BtrieveFilter::SetCaseSensitivity in PSQL 13.20.
   /// \param[in] ACSMode The alternate collation sequence mode.
   /// \par \DESCRIPTION
   /// Alternate collation sequence mode defaults to Btrieve::ACS_MODE_NONE. To set the alternate collation sequence mode to Btrieve::ACS_MODE_NAMED use BtrieveFilter::SetACSName or BtrieveFilter::SetACSUserDefined. Btrieve::ACS_MODE_NUMBERED is unsupported.
   /// \par \SNIPPET
   /// \snippet bfilter.cpp SetACSMode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSMode(Btrieve::ACSMode ACSMode);
   /// \brief Set the user defined alternate collation sequence name.
   /// \param[in] name The name.
   /// \par \DESCRIPTION
   /// Filters have no user defined alternate collation sequence name initially. To reference a user defined alternate collation sequence it must exist in the file. A user defined alternate collation sequence may be added to a file when an index is created. See BtrieveFile::IndexCreate.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSUserDefined(const char *name);
   /// \brief Set the alternate collation sequence name.
   /// \param[in] name The name.
   /// \par \DESCRIPTION
   /// Filters have no alternate collation sequence name initially. To reference an alternate collation sequence name it must exist in the file. An alternate collation sequence name may be added to a file when an index is created. See BtrieveFile::IndexCreate.
   /// \par \SNIPPET
   /// \snippet bfilter.cpp SetACSName
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSName(const char *name);

private:
   btrieve_filter_t btrieveFilter;
};

/// \brief The %Btrieve bulk retrieve attributes class.
class LINKAGE BtrieveBulkRetrieveAttributes
{
   friend class BtrieveFile;

protected:
   btrieve_bulk_retrieve_attributes_t GetBtrieveBulkRetrieveAttributes();

public:
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BtrieveBulkRetrieveAttributes
   BtrieveBulkRetrieveAttributes();
   ~BtrieveBulkRetrieveAttributes();

   /// \brief Add a field.
   /// \param[in] offset The offset. Offset must be less than Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \param[in] length The length. Length is limited to Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \par \DESCRIPTION
   /// Get bulk attributes have no fields initially.
   /// Offset plus length is limited to Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp AddField
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode AddField(int offset, int length);
   /// \brief Add a filter.
   /// \param[in] btrieveFilter The filter.
   /// \par \DESCRIPTION
   /// Get bulk attributes have no filters initially.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp AddFilter
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode AddFilter(BtrieveFilter *btrieveFilter);
   /// \brief Set the maximum record count.
   /// \param[in] maximumRecordCount The maximum record count. The maximum record count must be greater than 0 and less than 65536.
   /// \par \DESCRIPTION
   /// Maximum record count defaults to zero.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp SetMaximumRecordCount
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetMaximumRecordCount(int maximumRecordCount);
   /// \brief Set the maximum reject count.
   /// \param[in] maximumRejectCount The maximum reject count. The maximum reject count must be greater than or equal to 0 and less than 65536. A value of zero sets the maximum reject count to the PSQL defined value.
   /// \par \DESCRIPTION
   /// Maximum reject count defaults to the PSQL defined value.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp SetMaximumRejectCount
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetMaximumRejectCount(int maximumRejectCount);
   /// \brief Set skip current record.
   /// \param[in] skipCurrentRecord Skip current record?
   /// \par \DESCRIPTION
   /// Skip current record is disabled by default.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp SetSkipCurrentRecord
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetSkipCurrentRecord(bool skipCurrentRecord);

private:
   btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes;
};

/// \brief The %Btrieve bulk retrieve result class.
class LINKAGE BtrieveBulkRetrieveResult
{
   friend class BtrieveFile;

protected:
   btrieve_bulk_retrieve_result_t GetBtrieveBulkRetrieveResult();

public:
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BtrieveBulkRetrieveResult
   BtrieveBulkRetrieveResult();
   ~BtrieveBulkRetrieveResult();

   /// \brief Get the last status code.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkRetrieveResultGetLastStatusCode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Get the record.
   /// \param[in] recordNumber The record number.
   /// \param[out] record The record.
   /// \param[in] recordSize The record size.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp GetRecord
   /// \retval ">= 0" \NUMBER_OF_BYTES_READ_LIMITED \RETRIEVING_RECORDS_GREATER_THAN
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveBulkRetrieveResult::GetLastStatusCode}
   int GetRecord(int recordNumber, char *record, int recordSize);
   /// \brief Get the record count.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkRetrieveResultGetRecordCount
   /// \retval ">= 0" The record count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveBulkRetrieveResult::GetLastStatusCode}
   int GetRecordCount();
   /// \brief Get the record length.
   /// \param[in] recordNumber The record number.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp GetRecordLength
   /// \retval ">= 0" The record length.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveBulkRetrieveResult::GetLastStatusCode}
   int GetRecordLength(int recordNumber);
   /// \brief Get the record cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in] recordNumber The record number.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkRetrieveResultGetRecordCursorPosition
   /// \retval ">= 0" The record cursor position.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveBulkRetrieveResult::GetLastStatusCode}
   long long GetRecordCursorPosition(int recordNumber);

private:
   btrieve_bulk_retrieve_result_t bulkRetrieveResult;
};

/// \brief The %Btrieve index attributes class.
class LINKAGE BtrieveIndexAttributes
{
   friend class BtrieveClient;
   friend class BtrieveFile;

protected:
   btrieve_index_attributes_t GetBtrieveIndexAttributes();

public:
   /// \par \SNIPPET
   /// \snippet btest.cpp BtrieveIndexAttributes
   BtrieveIndexAttributes();
   ~BtrieveIndexAttributes();

   /// \brief Add a key segment.
   /// \param[in] btrieveKeySegment The key segment.
   /// \par \DESCRIPTION
   /// Index attributes have no key segments initially.
   /// \par \SNIPPET
   /// \snippet btest.cpp AddKeySegment
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode AddKeySegment(BtrieveKeySegment *btrieveKeySegment);
   /// \brief Set the index.
   /// \param[in] index The index.
   /// \par \DESCRIPTION
   /// Index defaults to the first available index starting at Btrieve::INDEX_1.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetIndex
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetIndex(Btrieve::Index index);
   /// \brief Set the duplicate mode.
   /// \param[in] duplicateMode The duplicate mode.
   /// \par \DESCRIPTION
   /// Duplicate mode defaults to Btrieve::DUPLICATE_MODE_NOT_ALLOWED.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetDuplicateMode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetDuplicateMode(Btrieve::DuplicateMode duplicateMode);
   /// \brief Set modifiable.
   /// \param[in] enableModifiable Enable modifiable?
   /// \par \DESCRIPTION
   /// Modifiable is enabled by default.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetModifiable
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetModifiable(bool enableModifiable);
   /// \brief Set the alternate collation sequence mode.
   /// \param[in] ACSMode The alternate collation sequence mode.
   /// \par \DESCRIPTION
   /// Alternate collation sequence mode defaults to Btrieve::ACS_MODE_NONE. To set the alternate collation sequence mode to Btrieve::ACS_MODE_NAMED use BtrieveIndexAttributes::SetACSName or BtrieveIndexAttributes::SetACSUserDefined. To set the alternate collation sequence mode to Btrieve::ACS_MODE_NUMBERED use BtrieveIndexAttributes::SetACSNumber.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSMode(Btrieve::ACSMode ACSMode);
   /// \brief Set the alternate collation sequence name.
   /// \note This method accepts international sort rule and unicode alternate collation sequence names only. Use BtrieveIndexAttributes::SetACSUserDefined to specify a user defined alternate collation sequence.
   /// \param[in] ACSName The alternate collation sequence name.
   /// \par \DESCRIPTION
   /// By default there is no alternate collation sequence name. Setting the alternate collation sequence name also sets the alternate collation sequence mode to Btrieve::ACS_MODE_NAMED.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetACSName
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSName(const char *ACSName);
   /// \brief Set the alternate collation sequence number.
   /// \param[in] ACSNumber The alternate collation sequence number.
   /// \par \DESCRIPTION
   /// By default there is no alternate collation sequence number. Setting the alternate collation sequence number also sets the alternate collation sequence mode to Btrieve::ACS_MODE_NUMBERED.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSNumber(int ACSNumber);
   /// \brief Set the user defined alternate collation sequence.
   /// \param[in] ACSName The alternate collation sequence name.
   /// \param[in] ACSMap The alternate collation sequence map.
   /// \param[in] ACSMapLength The alternate collation sequence map length.
   /// \par \DESCRIPTION
   /// By default there is no user defined alternate collation sequence. Setting the user defined alternate collation sequence also sets the alternate collation sequence mode to Btrieve::ACS_MODE_NAMED.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetACSUserDefined(const char *ACSName, const char *ACSMap, int ACSMapLength);

private:
   btrieve_index_attributes_t btrieveIndexAttributes;
};

/// \brief The %Btrieve bulk create payload class.
class LINKAGE BtrieveBulkCreatePayload
{
   friend class BtrieveFile;

protected:
   btrieve_bulk_create_payload_t GetBtrieveBulkCreatePayload();

public:
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BtrieveBulkCreatePayload
   BtrieveBulkCreatePayload();
   ~BtrieveBulkCreatePayload();

   /// \brief Add a record.
   /// \param[in] record The record.
   /// \param[in] recordLength The record length. Record length is limited to Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \par \DESCRIPTION
   /// Bulk create attributes have no records initially.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp AddRecord
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode AddRecord(const char *record, int recordLength);

private:
   btrieve_bulk_create_payload_t btrieveBulkCreatePayload;
};

/// \brief The %Btrieve bulk create result class.
class LINKAGE BtrieveBulkCreateResult
{
   friend class BtrieveFile;

protected:
   btrieve_bulk_create_result_t GetBtrieveBulkCreateResult();

public:
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BtrieveBulkCreateResult
   BtrieveBulkCreateResult();
   ~BtrieveBulkCreateResult();

   /// \brief Get the last status code.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkCreateResultGetLastStatusCode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Get the record count.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkCreateResultGetRecordCount
   /// \retval ">= 0" The record count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveBulkCreateResult::GetLastStatusCode}
   int GetRecordCount();
   /// \brief Get the record cursor position.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \param[in] recordNumber The record number.
   /// \par \SNIPPET
   /// \snippet btestbulk.cpp BulkCreateResultGetRecordCursorPosition
   /// \retval ">= 0" The record cursor position.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveBulkCreateResult::GetLastStatusCode}
   long long GetRecordCursorPosition(int recordNumber);

private:
   btrieve_bulk_create_result_t btrieveBulkCreateResult;
};

/// \brief The %Btrieve key segment class.
class LINKAGE BtrieveKeySegment
{
   friend class BtrieveIndexAttributes;
   friend class BtrieveFileInformation;

protected:
   btrieve_key_segment_t GetBtrieveKeySegment();
   BtrieveKeySegment(btrieve_key_segment_t btrieveKeySegmentIn);

public:
   /// \par \SNIPPET
   /// \snippet btest.cpp BtrieveKeySegment
   BtrieveKeySegment();
   ~BtrieveKeySegment();

   /// \brief Get the last status code.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp KeySegmentGetLastStatusCode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Get the alternate collation sequence mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetACSMode
   /// \retval "!= Btrieve::ACS_MODE_UNKNOWN" The alternate collation sequence mode.
   /// \retval "= Btrieve::ACS_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   /// \see Btrieve::ACSModeToString
   Btrieve::ACSMode GetACSMode();
   /// \brief Get modifiable.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetModifiable
   /// \retval "> 0" Modifications are allowed.
   /// \retval 0 Modifications are not allowed.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetModifiable();
   /// \brief Get key continues.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetKeyContinues
   /// \retval "> 0" Key continues is set.
   /// \retval 0 Key continues isn't set.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetKeyContinues();
   /// \brief Get the data type.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetDataType
   /// \retval "!= Btrieve::DATA_TYPE_UNKNOWN" The data type.
   /// \retval "= Btrieve::DATA_TYPE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   /// \see Btrieve::DataTypeToString
   Btrieve::DataType GetDataType();
   /// \brief Get the alternate collation sequence number.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetACSNumber
   /// \retval ">= 0" The alternate collation sequence number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetACSNumber();
   /// \brief Get string.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetDescendingSortOrder
   /// \retval "> 0" Descending sort order is set.
   /// \retval 0 Descending sort order isn't set.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetDescendingSortOrder();
   /// \brief Get the duplicate mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetDuplicateMode
   /// \retval "!= Btrieve::DUPLICATE_MODE_UNKNOWN" The duplicate mode.
   /// \retval "= Btrieve::DUPLICATE_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   /// \see Btrieve::DuplicateModeToString
   Btrieve::DuplicateMode GetDuplicateMode();
   /// \brief Get the index.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetIndex
   /// \retval "!= Btrieve::INDEX_UNKNOWN" The index.
   /// \retval "= Btrieve::INDEX_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   /// \see Btrieve::IndexToString
   Btrieve::Index GetIndex();
   /// \brief Get the length.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetLength
   /// \retval ">= 0" The length.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetLength();
   /// \brief Get the null key mode.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetNullKeyMode
   /// \retval "!= Btrieve::NULL_KEY_MODE_UNKNOWN" The null key mode.
   /// \retval "= Btrieve::NULL_KEY_MODE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   /// \see Btrieve::NullKeyModeToString
   Btrieve::NullKeyMode GetNullKeyMode();
   /// \brief Get the null value.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetNullValue
   /// \retval ">= 0" The null value.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetNullValue();
   /// \brief Get the offset.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetOffset
   /// \retval ">= 0" The offset.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   int GetOffset();
   /// \brief Get the unique value count.
   /// \note The signature for this method changed in PSQL 13.20.
   /// \par \SNIPPET
   /// \snippet bfileinformation.cpp GetUniqueValueCount
   /// \retval ">= 0" The unique value count.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveKeySegment::GetLastStatusCode}
   long long GetUniqueValueCount();
   /// \brief Set descending sort order.
   /// \param[in] setDescendingSortOrder Enable descending sort order?
   /// \par \DESCRIPTION
   /// Descending sort order is disabled by default.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetDescendingSortOrder
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetDescendingSortOrder(bool setDescendingSortOrder);
   /// \brief Set the field.
   /// \param[in] offset The offset. Offset must be less than Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \param[in] length The length. Length is limited to Btrieve::MAXIMUM_KEY_LENGTH.
   /// \param[in] dataType The data type.
   /// \par \DESCRIPTION
   /// Key segments have no field initially.
   /// Offset plus length is limited to Btrieve::MAXIMUM_RECORD_LENGTH.
   /// \par \SNIPPET
   /// \snippet btest.cpp SetField
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetField(int offset, int length, Btrieve::DataType dataType);
   /// \brief Set the null key mode.
   /// \param[in] nullKeyMode The null key mode.
   /// \par \DESCRIPTION
   /// Null key mode defaults to Btrieve::NULL_KEY_MODE_NONE.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetNullKeyMode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetNullKeyMode(Btrieve::NullKeyMode nullKeyMode);
   /// \brief Set the null value.
   /// \param[in] nullValue The null value.
   /// \par \DESCRIPTION
   /// Null value defaults to zero.
   /// \par \SNIPPET
   /// \snippet bindexattributes.cpp SetNullValue
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode SetNullValue(int nullValue);

private:
   btrieve_key_segment_t btrieveKeySegment;
};

/// \brief The %Btrieve version class.
class LINKAGE BtrieveVersion
{
   friend class BtrieveClient;

protected:
   btrieve_version_t GetBtrieveVersion();

public:
   /// \par \SNIPPET
   /// \snippet bversion.cpp BtrieveVersion
   /// \see BtrieveClient::GetVersion
   BtrieveVersion();
   ~BtrieveVersion();

   /// \brief Get the last status code.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetLastStatusCode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();
   /// \brief Get the client version type.
   /// \par \DESCRIPTION
   /// Client refers to the instance of PSQL used by the caller.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetClientVersionType
   /// \retval "!= Btrieve::VERSION_TYPE_UNKNOWN" The client version type.
   /// \retval "= Btrieve::VERSION_TYPE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   /// \see Btrieve::VersionTypeToString
   Btrieve::VersionType GetClientVersionType();
   /// \brief Get the remote version type.
   /// \par \DESCRIPTION
   /// Remote refers to the instance of PSQL used to access the optionally supplied Btrieve file.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetRemoteVersionType
   /// \retval "!= Btrieve::VERSION_TYPE_UNKNOWN" The remote version type.
   /// \retval "= Btrieve::VERSION_TYPE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   /// \see Btrieve::VersionTypeToString
   Btrieve::VersionType GetRemoteVersionType();
   /// \brief Get the local version type.
   /// \par \DESCRIPTION
   /// Local refers to the instance of PSQL running locally with the caller.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetLocalVersionType
   /// \retval "!= Btrieve::VERSION_TYPE_UNKNOWN" The local version type.
   /// \retval "= Btrieve::VERSION_TYPE_UNKNOWN" \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   /// \see Btrieve::VersionTypeToString
   Btrieve::VersionType GetLocalVersionType();
   /// \brief Get the client revision number.
   /// \par \DESCRIPTION
   /// Client refers to the instance of PSQL used by the caller.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetClientRevisionNumber
   /// \retval ">= 0" The revision number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   int GetClientRevisionNumber();
   /// \brief Get the client version number.
   /// \par \DESCRIPTION
   /// Client refers to the instance of PSQL used by the caller.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetClientVersionNumber
   /// \retval ">= 0" The version number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   int GetClientVersionNumber();
   /// \brief Get the remote revision number.
   /// \par \DESCRIPTION
   /// Remote refers to the instance of PSQL used to access the optionally supplied Btrieve file.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetRemoteRevisionNumber
   /// \retval ">= 0" The revision number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   int GetRemoteRevisionNumber();
   /// \brief Get the remote version number.
   /// \par \DESCRIPTION
   /// Remote refers to the instance of PSQL used to access the optionally supplied Btrieve file.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetRemoteVersionNumber
   /// \retval ">= 0" The version number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   int GetRemoteVersionNumber();
   /// \brief Get the local revision number.
   /// \par \DESCRIPTION
   /// Local refers to the instance of PSQL running locally with the caller.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetLocalRevisionNumber
   /// \retval ">= 0" The revision number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   int GetLocalRevisionNumber();
   /// \brief Get the local version number.
   /// \par \DESCRIPTION
   /// Local refers to the instance of PSQL running locally with the caller.
   /// \par \SNIPPET
   /// \snippet bversion.cpp GetLocalVersionNumber
   /// \retval ">= 0" The version number.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveVersion::GetLastStatusCode}
   int GetLocalVersionNumber();

private:
   btrieve_version_t btrieveVersion;
};

/// \example btest.cpp
/// This is an example of file creation, load, access, and deletion.
///
/// \example bkeyonly.cpp
/// This is an example of a key only file.
///
/// \example btestvlr.cpp
/// This is an example of variable length records based on \ref btest.cpp .
///
/// \example bfileattributes.cpp
/// This is an example of file attributes use.
///
/// \example bfilter.cpp
/// This is an example of filter use.
///
/// \example bindexattributes.cpp
/// This is an example of index attributes use.
//
/// \example bpercentage.cpp
/// This is an example of record retrieve both by percentage and fraction based on \ref btest.cpp .
///
/// \example btestbulk.cpp
/// This is an example of bulk create and retrieve based on \ref btest.cpp .
///
/// \example btestappend.cpp
/// This is an example of record append and retrieve chunk based on \ref btest.cpp .
///
/// \example btestchunk.cpp
/// This is an example of record update and retrieve chunk based on \ref btest.cpp .
///
/// \example bfileinformation.cpp
/// This is an example of file information use.
///
/// \example block.cpp
/// This is an example of record locking and unlocking.
///
/// \example bversion.cpp
/// This is an example of version use.
///
/// \mainpage The %Btrieve C++ and C API
///
/// \section gettingStarted Getting Started
///
/// If you're already familiar with the current %Btrieve API and want to understand how your current knowledge maps to the %Btrieve C++ and C API then the \ref btrieveOperationToBtrieve2APIMapping guide is a good place to start.
///
/// If you want an introduction to the %Btrieve C++ API paradigm then the simple example, \ref btest.cpp , is a good place to start.
///
/// If you want to explore the %Btrieve C++ API via its documentation then the <a href="annotated.html"><b>class list</b></a> is a good place to start.
///
/// If you want an introduction to the %Btrieve C API paradigm then the simple example, \ref btest.c , is a good place to start.
///
/// \remark There's a search function available. Take advantage of it. It's located near the top right of most pages.
///
/// \remark The %Btrieve API isn't available only for C++ and C, it's also available for Perl, PHP, and Python.
/// 
/// \page btrieveOperationToBtrieve2APIMapping %Btrieve Operation to %Btrieve C++ and C API Mapping Guide
///
/// <table>
/// <tr><th>%Btrieve Operation<th>%Btrieve C++ API<th>%Btrieve C API
/// <tr><td>Abort Transaction
///                                                <td>BtrieveClient::TransactionAbort
///                                                <td>BtrieveClientTransactionAbort()
/// <tr><td>Begin Transaction
///                                                <td>BtrieveClient::TransactionBegin
///                                                <td>BtrieveClientTransactionBegin()
/// <tr><td>Clear Owner
///                                                <td>BtrieveFile::SetOwner
///                                                <td>BtrieveFileSetOwner()
/// <tr><td>Close
///                                                <td>BtrieveClient::FileClose
///                                                <td>BtrieveClientFileClose()
/// <tr><td rowspan="2">Continuous Operation
///                                                <td>BtrieveClient::ContinuousOperationBegin
///                                                <td>BtrieveClientContinuousOperationBegin()
/// <tr>                                           <td>BtrieveClient::ContinuousOperationEnd
///                                                <td>BtrieveClientContinuousOperationEnd()
/// <tr><td rowspan="3">Create
///                                                <td>BtrieveClient::FileCreate
///                                                <td>BtrieveClientFileCreate()
/// <tr>                                           <td>BtrieveClient::FileDelete
///                                                <td>BtrieveClientFileDelete()
/// <tr>                                           <td>BtrieveClient::FileRename
///                                                <td>BtrieveClientFileRename()
/// <tr><td>Create Index
///                                                <td>BtrieveFile::IndexCreate
///                                                <td>BtrieveFileIndexCreate()
/// <tr><td>Delete
///                                                <td>BtrieveFile::RecordDelete
///                                                <td>BtrieveFileRecordDelete()
/// <tr><td>Drop Index
///                                                <td>BtrieveFile::IndexDrop
///                                                <td>BtrieveFileIndexDrop()
/// <tr><td>End Transaction
///                                                <td>BtrieveClient::TransactionEnd
///                                                <td>BtrieveClientTransactionEnd()
/// <tr><td rowspan="2">Find Percentage
///                                                <td>BtrieveFile::GetNumerator
///                                                <td>BtrieveFileGetNumerator()
/// <tr>                                           <td>BtrieveFile::GetPercentage
///                                                <td>BtrieveFileGetPercentage()
/// <tr><td rowspan="2">Get By Percentage
///                                                <td>BtrieveFile::RecordRetrieveByFraction
///                                                <td>BtrieveFileRecordRetrieveByFraction()
/// <tr>                                           <td>BtrieveFile::RecordRetrieveByPercentage
///                                                <td>BtrieveFileRecordRetrieveByPercentage()
/// <tr><td rowspan="1">Get Direct/Chunk
///                                                <td>BtrieveFile::RecordRetrieveChunk
///                                                <td>BtrieveFileRecordRetrieveChunk()
/// <tr><td>Get Direct/Record
///                                                <td>BtrieveFile::RecordRetrieveByCursorPosition
///                                                <td>BtrieveFileRecordRetrieveByCursorPosition()
/// <tr><td>Get Directory
///                                                <td>BtrieveClient::GetCurrentDirectory
///                                                <td>BtrieveClientGetCurrentDirectory()
/// <tr><td>Get Equal
///                                                <td>BtrieveFile::RecordRetrieve
///                                                <td>BtrieveFileRecordRetrieve()
/// <tr><td>Get First
///                                                <td>BtrieveFile::RecordRetrieveFirst
///                                                <td>BtrieveFileRecordRetrieveFirst()
/// <tr><td>Get Greater Than
///                                                <td>BtrieveFile::RecordRetrieve
///                                                <td>BtrieveFileRecordRetrieve()
/// <tr><td>Get Greater Than or Equal
///                                                <td>BtrieveFile::RecordRetrieve
///                                                <td>BtrieveFileRecordRetrieve()
/// <tr><td rowspan="5">Get Key
///                                                <td>BtrieveFile::KeyRetrieve
///                                                <td>BtrieveFileKeyRetrieve()
/// <tr>                                           <td>BtrieveFile::KeyRetrieveFirst
///                                                <td>BtrieveFileKeyRetrieveFirst()
/// <tr>                                           <td>BtrieveFile::KeyRetrieveLast
///                                                <td>BtrieveFileKeyRetrieveLast()
/// <tr>                                           <td>BtrieveFile::KeyRetrieveNext
///                                                <td>BtrieveFileKeyRetrieveNext()
/// <tr>                                           <td>BtrieveFile::KeyRetrievePrevious 
///                                                <td>BtrieveFileKeyRetrievePrevious()
/// <tr><td>Get Last
///                                                <td>BtrieveFile::RecordRetrieveLast
///                                                <td>BtrieveFileRecordRetrieveLast()
/// <tr><td>Get Less Than
///                                                <td>BtrieveFile::RecordRetrieve
///                                                <td>BtrieveFileRecordRetrieve()
/// <tr><td>Get Less Than or Equal
///                                                <td>BtrieveFile::RecordRetrieve
///                                                <td>BtrieveFileRecordRetrieve()
/// <tr><td>Get Next
///                                                <td>BtrieveFile::RecordRetrieveNext
///                                                <td>BtrieveFileRecordRetrieveNext()
/// <tr><td>Get Next Extended
///                                                <td>BtrieveFile::BulkRetrieveNext
///                                                <td>BtrieveFileBulkRetrieveNext()
/// <tr><td>Get Cursor Position
///                                                <td>BtrieveFile::GetCursorPosition
///                                                <td>BtrieveFileGetCursorPosition()
/// <tr><td>Get Previous
///                                                <td>BtrieveFile::RecordRetrievePrevious
///                                                <td>BtrieveFileRecordRetrievePrevious()
/// <tr><td>Get Previous Extended
///                                                <td>BtrieveFile::BulkRetrievePrevious
///                                                <td>BtrieveFileBulkRetrievePrevious()
/// <tr><td>Insert
///                                                <td>BtrieveFile::RecordCreate
///                                                <td>BtrieveFileRecordCreate()
/// <tr><td>Insert Extended
///                                                <td>BtrieveFile::BulkCreate
///                                                <td>BtrieveFileBulkCreate()
/// <tr><td rowspan="2">Login/Logout
///                                                <td>BtrieveClient::Login
///                                                <td>BtrieveClientLogin()
/// <tr>                                           <td>BtrieveClient::Logout
///                                                <td>BtrieveClientLogout()
/// <tr><td>Open
///                                                <td>BtrieveClient::FileOpen
///                                                <td>BtrieveClientFileOpen()
/// <tr><td>Reset
///                                                <td>BtrieveClient::Reset
///                                                <td>BtrieveClientReset()
/// <tr><td>Set Directory
///                                                <td>BtrieveClient::SetCurrentDirectory
///                                                <td>BtrieveClientSetCurrentDirectory()
/// <tr><td>Set Owner
///                                                <td>BtrieveFile::SetOwner
///                                                <td>BtrieveFileSetOwner()
/// <tr><td>Stat
///                                                <td>BtrieveFile::GetInformation 
///                                                <td>BtrieveFileGetInformation()
/// <tr><td>Stat Extended
///                                                <td>BtrieveFile::GetInformation 
///                                                <td>BtrieveFileGetInformation()
/// <tr><td>Step First
///                                                <td>BtrieveFile::RecordRetrieveFirst
///                                                <td>BtrieveFileRecordRetrieveFirst()
/// <tr><td>Step Last
///                                                <td>BtrieveFile::RecordRetrieveLast
///                                                <td>BtrieveFileRecordRetrieveLast()
/// <tr><td>Step Next
///                                                <td>BtrieveFile::RecordRetrieveNext
///                                                <td>BtrieveFileRecordRetrieveNext()
/// <tr><td>Step Next Extended
///                                                <td>BtrieveFile::BulkRetrieveNext
///                                                <td>BtrieveFileBulkRetrieveNext()
/// <tr><td>Step Previous
///                                                <td>BtrieveFile::RecordRetrievePrevious
///                                                <td>BtrieveFileRecordRetrievePrevious()
/// <tr><td>Step Previous Extended
///                                                <td>BtrieveFile::BulkRetrievePrevious
///                                                <td>BtrieveFileBulkRetrievePrevious()
/// <tr><td>Stop
///                                                <td>BtrieveClient::Stop
///                                                <td>BtrieveClientStop()
/// <tr><td rowspan="2">Unlock
///                                                <td>BtrieveFile::RecordUnlock
///                                                <td>BtrieveFileRecordUnlock()
/// <tr>                                           <td>BtrieveFile::UnlockCursorPosition
///                                                <td>BtrieveFileUnlockCursorPosition()
/// <tr><td>Update
///                                                <td>BtrieveFile::RecordUpdate
///                                                <td>BtrieveFileRecordUpdate()
/// <tr><td rowspan="3">Update Chunk
///                                                <td>BtrieveFile::RecordAppendChunk
///                                                <td>BtrieveFileRecordAppendChunk()
/// <tr>                                           <td>BtrieveFile::RecordTruncate
///                                                <td>BtrieveFileRecordTruncate()
/// <tr>                                           <td>BtrieveFile::RecordUpdateChunk
///                                                <td>BtrieveFileRecordUpdateChunk()
/// <tr><td rowspan="11">Version
///                                                <td>BtrieveVersion::GetClientRevisionNumber
///                                                <td>BtrieveVersionGetClientRevisionNumber()
/// <tr>                                           <td>BtrieveVersion::GetClientVersionNumber
///                                                <td>BtrieveVersionGetClientVersionNumber()
/// <tr>                                           <td>BtrieveVersion::GetClientVersionType
///                                                <td>BtrieveVersionGetClientVersionType()
/// <tr>                                           <td>BtrieveVersion::GetRemoteRevisionNumber
///                                                <td>BtrieveVersionGetRemoteRevisionNumber()
/// <tr>                                           <td>BtrieveVersion::GetRemoteVersionNumber
///                                                <td>BtrieveVersionGetRemoteVersionNumber()
/// <tr>                                           <td>BtrieveVersion::GetRemoteVersionType
///                                                <td>BtrieveVersionGetRemoteVersionType()
/// <tr>                                           <td>BtrieveVersion::GetLocalRevisionNumber
///                                                <td>BtrieveVersionGetLocalRevisionNumber()
/// <tr>                                           <td>BtrieveVersion::GetLocalVersionNumber
///                                                <td>BtrieveVersionGetLocalVersionNumber()
/// <tr>                                           <td>BtrieveVersion::GetLocalVersionType
///                                                <td>BtrieveVersionGetLocalVersionType()
///

/// \cond
/// \brief The %Btrieve collection class.
class LINKAGE BtrieveCollection
{
   friend class BtrieveClient;

protected:
   void SetBtrieveClient(BtrieveClient *btrieveClient);
   BtrieveFile *GetBtrieveFile();

public:
   /// \see BtrieveClient::CollectionOpen
   BtrieveCollection();
   /// \see BtrieveClient::CollectionClose
   ~BtrieveCollection();

   /// \brief Create a document.
   /// \param[in] json The json.
   /// \param[in] blob The blob.
   /// \param[in] blobLength The blob length.
   /// \retval ">= 0" The document identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveCollection::GetLastStatusCode}
   long long DocumentCreate(const char *json, const char *blob, int blobLength);
   /// \brief Retrieve a document using the given identifier.
   /// \param[in] id The identifier.
   /// \param[out] blob The blob.
   /// \param[in] blobSize The blob size.
   /// \retval "!= NULL" The json.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *DocumentRetrieve(long long id, char *blob, int blobSize);
   /// \brief Retrieve a document using the given identifier.
   /// \param[in] id The identifier.
   /// \retval "!= NULL" The json.
   /// \retval NULL \ERROR_HAS_OCCURRED
   const char *DocumentRetrieve(long long id);
   /// \brief Update a document.
   /// \param[in] id The identifier.
   /// \param[in] json The json.
   /// \param[in] blob The blob.
   /// \param[in] blobLength The blob length.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode DocumentUpdate(long long id, const char *json, const char *blob, int blobLength);
   /// \brief Delete a document.
   /// \param[in] id The identifier.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode DocumentDelete(long long id);
   // TODO: Support case insensitive names in query.
   /// \brief Query the collection.
   /// \param[out] btrieveDocumentSet The %Btrieve document set.
   /// \param[in] query The query.
   /// \par \DESCRIPTION
   /// \code
   ///   query := { expression, ... }
   ///
   ///   expression :=
   ///      "$and" : [ { expression }, { expression  } ... ]
   ///      "$or" : [ { expression }, { expression } ... ]
   ///      "$not" : { expression }
   ///      field : value
   ///      field : { "$eq" : value }
   ///      field : { "$exists" : false | true }
   ///      field : { "$gt" : value }
   ///      field : { "$gte" : value }
   ///      field : { "$in" : [ value, value ... ]
   ///      field : { "$lt" : value }
   ///      field : { "$lte" : value }
   ///      field : { "$ne" : value }
   ///      field : { "$nin" : [ value, value ... ]
   ///      field : { "$type" : <string> }
   ///
   ///   field := <string>
   ///
   ///   value := false | true | NULL | <string> | <number> | <array>
   /// \endcode
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode Query(BtrieveDocumentSet *btrieveDocumentSet, const char *query);
   /// \brief Get the last status code.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();

private:
   BtrieveClient *btrieveClient;
   BtrieveFile *btrieveFile;
   Btrieve::StatusCode lastStatusCode;
};

/// \brief The %Btrieve document set class.
class LINKAGE BtrieveDocumentSet
{
   friend class BtrieveCollection;

protected:
   std::set<long long> *GetStdSet();
   
public:
   /// \see BtrieveCollection::Query
   BtrieveDocumentSet();
   ~BtrieveDocumentSet();

   /// \brief Return the number of document identifiers in the set.
   /// \retval ">= 0" The number of document identifiers in the set.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveDocumentSet::GetLastStatusCode}
   long long Size();
   /// \brief Remove and return an arbitrary document identifier from the set.
   /// \retval ">= 0" The popped document identifier.
   /// \retval -1 \ERROR_HAS_OCCURRED
   /// \TO_DETERMINE_STATUS_CODE{BtrieveDocumentSet::GetLastStatusCode}
   long long Pop();
   /// \brief Get the last status code.
   /// \retval "= Btrieve::STATUS_CODE_NO_ERROR" \SUCCESS
   /// \retval "!= Btrieve::STATUS_CODE_NO_ERROR" \ERROR_HAS_OCCURRED
   /// \see Btrieve::StatusCodeToString
   Btrieve::StatusCode GetLastStatusCode();

private:
   // TODO: Use unordered sets?
   std::set<long long> *stdSet;
   Btrieve::StatusCode lastStatusCode;
};
/// \endcond

#endif
