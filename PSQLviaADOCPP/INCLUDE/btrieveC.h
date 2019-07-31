////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 - Actian Corp.
//
////////////////////////////////////////////////////////////

#ifndef _BTRIEVEC_H
#define _BTRIEVEC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LINKAGE
	#ifdef __GNUC__
		#define LINKAGE
	#else
		#define LINKAGE __declspec(dllimport)
	#endif
#endif

#define BTRIEVE_MAXIMUM_RECORD_LENGTH (60 * 1024)

#define BTRIEVE_MAXIMUM_KEY_LENGTH 255

typedef enum {
	BTRIEVE_STATUS_CODE_NO_ERROR = 0,
	BTRIEVE_STATUS_CODE_INVALID_FUNCTION = 1,
	BTRIEVE_STATUS_CODE_IO_ERROR = 2,
	BTRIEVE_STATUS_CODE_FILE_NOT_OPEN = 3,
	BTRIEVE_STATUS_CODE_KEY_VALUE_NOT_FOUND = 4,
	BTRIEVE_STATUS_CODE_DUPLICATE_KEY_VALUE = 5,
	BTRIEVE_STATUS_CODE_INVALID_INDEX_NUMBER = 6,
	BTRIEVE_STATUS_CODE_DIFFERENT_INDEX_NUMBER = 7,
	BTRIEVE_STATUS_CODE_POSITION_NOT_SET = 8,
	BTRIEVE_STATUS_CODE_END_OF_FILE = 9,
	BTRIEVE_STATUS_CODE_MODIFIABLE_KEYVALUE_ERROR = 10,
	BTRIEVE_STATUS_CODE_FILENAME_BAD = 11,
	BTRIEVE_STATUS_CODE_FILE_NOT_FOUND = 12,
	BTRIEVE_STATUS_CODE_EXTENDED_FILE_ERROR = 13,
	BTRIEVE_STATUS_CODE_PREIMAGE_OPEN_ERROR = 14,
	BTRIEVE_STATUS_CODE_PREIMAGE_IO_ERROR = 15,
	BTRIEVE_STATUS_CODE_EXPANSION_ERROR = 16,
	BTRIEVE_STATUS_CODE_CLOSE_ERROR = 17,
	BTRIEVE_STATUS_CODE_DISKFULL = 18,
	BTRIEVE_STATUS_CODE_UNRECOVERABLE_ERROR = 19,
	BTRIEVE_STATUS_CODE_RECORD_MANAGER_INACTIVE = 20,
	BTRIEVE_STATUS_CODE_KEYBUFFER_TOO_SHORT = 21,
	BTRIEVE_STATUS_CODE_DATALENGTH_ERROR = 22,
	BTRIEVE_STATUS_CODE_POSITIONBLOCK_LENGTH = 23,
	BTRIEVE_STATUS_CODE_PAGE_SIZE_ERROR = 24,
	BTRIEVE_STATUS_CODE_CREATE_IO_ERROR = 25,
	BTRIEVE_STATUS_CODE_NUMBER_OF_INDEXES = 26,
	BTRIEVE_STATUS_CODE_INVALID_KEY_POSITION = 27,
	BTRIEVE_STATUS_CODE_INVALID_RECORD_LENGTH = 28,
	BTRIEVE_STATUS_CODE_INVALID_KEYLENGTH = 29,
	BTRIEVE_STATUS_CODE_NOT_A_BTRIEVE_FILE = 30,
	BTRIEVE_STATUS_CODE_FILE_ALREADY_EXTENDED = 31,
	BTRIEVE_STATUS_CODE_EXTEND_IO_ERROR = 32,
	BTRIEVE_STATUS_CODE_BTR_CANNOT_UNLOAD = 33,
	BTRIEVE_STATUS_CODE_INVALID_EXTENSION_NAME = 34,
	BTRIEVE_STATUS_CODE_DIRECTORY_ERROR = 35,
	BTRIEVE_STATUS_CODE_TRANSACTION_ERROR = 36,
	BTRIEVE_STATUS_CODE_TRANSACTION_IS_ACTIVE = 37,
	BTRIEVE_STATUS_CODE_TRANSACTION_FILE_IO_ERROR = 38,
	BTRIEVE_STATUS_CODE_END_TRANSACTION_ERROR = 39,
	BTRIEVE_STATUS_CODE_TRANSACTION_MAX_FILES = 40,
	BTRIEVE_STATUS_CODE_OPERATION_NOT_ALLOWED = 41,
	BTRIEVE_STATUS_CODE_INCOMPLETE_ACCEL_ACCESS = 42,
	BTRIEVE_STATUS_CODE_INVALID_RECORD_ADDRESS = 43,
	BTRIEVE_STATUS_CODE_NULL_KEYPATH = 44,
	BTRIEVE_STATUS_CODE_INCONSISTENT_KEY_FLAGS = 45,
	BTRIEVE_STATUS_CODE_ACCESS_TO_FILE_DENIED = 46,
	BTRIEVE_STATUS_CODE_MAXIMUM_OPEN_FILES = 47,
	BTRIEVE_STATUS_CODE_INVALID_ALT_SEQUENCE_DEF = 48,
	BTRIEVE_STATUS_CODE_KEY_TYPE_ERROR = 49,
	BTRIEVE_STATUS_CODE_OWNER_ALREADY_SET = 50,
	BTRIEVE_STATUS_CODE_INVALID_OWNER = 51,
	BTRIEVE_STATUS_CODE_ERROR_WRITING_CACHE = 52,
	BTRIEVE_STATUS_CODE_INVALID_INTERFACE = 53,
	BTRIEVE_STATUS_CODE_VARIABLE_PAGE_ERROR = 54,
	BTRIEVE_STATUS_CODE_AUTOINCREMENT_ERROR = 55,
	BTRIEVE_STATUS_CODE_INCOMPLETE_INDEX = 56,
	BTRIEVE_STATUS_CODE_EXPANED_MEM_ERROR = 57,
	BTRIEVE_STATUS_CODE_COMPRESS_BUFFER_TOO_SHORT = 58,
	BTRIEVE_STATUS_CODE_FILE_ALREADY_EXISTS = 59,
	BTRIEVE_STATUS_CODE_REJECT_COUNT_REACHED = 60,
	BTRIEVE_STATUS_CODE_SMALL_EX_GET_BUFFER_ERROR = 61,
	BTRIEVE_STATUS_CODE_INVALID_GET_EXPRESSION = 62,
	BTRIEVE_STATUS_CODE_INVALID_EXT_INSERT_BUFF = 63,
	BTRIEVE_STATUS_CODE_OPTIMIZE_LIMIT_REACHED = 64,
	BTRIEVE_STATUS_CODE_INVALID_EXTRACTOR = 65,
	BTRIEVE_STATUS_CODE_RI_TOO_MANY_DATABASES = 66,
	BTRIEVE_STATUS_CODE_RIDDF_CANNOT_OPEN = 67,
	BTRIEVE_STATUS_CODE_RI_CASCADE_TOO_DEEP = 68,
	BTRIEVE_STATUS_CODE_RI_CASCADE_ERROR = 69,
	BTRIEVE_STATUS_CODE_RI_VIOLATION = 71,
	BTRIEVE_STATUS_CODE_RI_REFERENCED_FILE_CANNOT_OPEN = 72,
	BTRIEVE_STATUS_CODE_RI_OUT_OF_SYNC = 73,
	BTRIEVE_STATUS_CODE_END_CHANGED_TO_ABORT = 74,
	BTRIEVE_STATUS_CODE_RI_CONFLICT = 76,
	BTRIEVE_STATUS_CODE_CANT_LOOP_IN_SERVER = 77,
	BTRIEVE_STATUS_CODE_DEAD_LOCK = 78,
	BTRIEVE_STATUS_CODE_PROGRAMMING_ERROR = 79,
	BTRIEVE_STATUS_CODE_CONFLICT = 80,
	BTRIEVE_STATUS_CODE_LOCKERROR = 81,
	BTRIEVE_STATUS_CODE_LOST_POSITION = 82,
	BTRIEVE_STATUS_CODE_READ_OUTSIDE_TRANSACTION = 83,
	BTRIEVE_STATUS_CODE_RECORD_INUSE = 84,
	BTRIEVE_STATUS_CODE_FILE_INUSE = 85,
	BTRIEVE_STATUS_CODE_FILE_TABLE_FULL = 86,
	BTRIEVE_STATUS_CODE_NOHANDLES_AVAILABLE = 87,
	BTRIEVE_STATUS_CODE_INCOMPATIBLE_MODE_ERROR = 88,
	BTRIEVE_STATUS_CODE_DEVICE_TABLE_FULL = 90,
	BTRIEVE_STATUS_CODE_SERVER_ERROR = 91,
	BTRIEVE_STATUS_CODE_TRANSACTION_TABLE_FULL = 92,
	BTRIEVE_STATUS_CODE_INCOMPATIBLE_LOCK_TYPE = 93,
	BTRIEVE_STATUS_CODE_PERMISSION_ERROR = 94,
	BTRIEVE_STATUS_CODE_SESSION_NO_LONGER_VALID = 95,
	BTRIEVE_STATUS_CODE_COMMUNICATIONS_ERROR = 96,
	BTRIEVE_STATUS_CODE_DATA_MESSAGE_TOO_SMALL = 97,
	BTRIEVE_STATUS_CODE_INTERNAL_TRANSACTION_ERROR = 98,
	BTRIEVE_STATUS_CODE_REQUESTER_CANT_ACCESS_RUNTIME = 99,
	BTRIEVE_STATUS_CODE_NO_CACHE_BUFFERS_AVAIL = 100,
	BTRIEVE_STATUS_CODE_NO_OS_MEMORY_AVAIL = 101,
	BTRIEVE_STATUS_CODE_NO_STACK_AVAIL = 102,
	BTRIEVE_STATUS_CODE_CHUNK_OFFSET_TOO_LONG = 103,
	BTRIEVE_STATUS_CODE_LOCALE_ERROR = 104,
	BTRIEVE_STATUS_CODE_CANNOT_CREATE_WITH_VAT = 105,
	BTRIEVE_STATUS_CODE_CHUNK_CANNOT_GET_NEXT = 106,
	BTRIEVE_STATUS_CODE_CHUNK_INCOMPATIBLE_FILE = 107,
	BTRIEVE_STATUS_CODE_TRANSACTION_TOO_COMPLEX = 109,
	BTRIEVE_STATUS_CODE_ARCH_BLOG_OPEN_ERROR = 110,
	BTRIEVE_STATUS_CODE_ARCH_FILE_NOT_LOGGED = 111,
	BTRIEVE_STATUS_CODE_ARCH_FILE_IN_USE = 112,
	BTRIEVE_STATUS_CODE_ARCH_LOGFILE_NOT_FOUND = 113,
	BTRIEVE_STATUS_CODE_ARCH_LOGFILE_INVALID = 114,
	BTRIEVE_STATUS_CODE_ARCH_DUMPFILE_ACCESS_ERROR = 115,
	BTRIEVE_STATUS_CODE_LOCATOR_FILE_INDICATOR = 116,
	BTRIEVE_STATUS_CODE_NO_SYSTEM_LOCKS_AVAILABLE = 130,
	BTRIEVE_STATUS_CODE_FILE_FULL = 132,
	BTRIEVE_STATUS_CODE_MORE_THAN_5_CONCURRENT_USERS = 133,
	BTRIEVE_STATUS_CODE_ISR_NOT_FOUND = 134,
	BTRIEVE_STATUS_CODE_ISR_INVALID = 135,
	BTRIEVE_STATUS_CODE_ACS_NOT_FOUND = 136,
	BTRIEVE_STATUS_CODE_CANNOT_CONVERT_RP = 137,
	BTRIEVE_STATUS_CODE_INVALID_NULL_INDICATOR = 138,
	BTRIEVE_STATUS_CODE_INVALID_KEY_OPTION = 139,
	BTRIEVE_STATUS_CODE_INCOMPATIBLE_CLOSE = 140,
	BTRIEVE_STATUS_CODE_INVALID_USERNAME = 141,
	BTRIEVE_STATUS_CODE_INVALID_DATABASE = 142,
	BTRIEVE_STATUS_CODE_NO_SSQL_RIGHTS = 143,
	BTRIEVE_STATUS_CODE_ALREADY_LOGGED_IN = 144,
	BTRIEVE_STATUS_CODE_NO_DATABASE_SERVICES = 145,
	BTRIEVE_STATUS_CODE_DUPLICATE_SYSTEM_KEY = 146,
	BTRIEVE_STATUS_CODE_LOG_SEGMENT_MISSING = 147,
	BTRIEVE_STATUS_CODE_ROLL_FORWARD_ERROR = 148,
	BTRIEVE_STATUS_CODE_SYSTEM_KEY_INTERNAL = 149,
	BTRIEVE_STATUS_CODE_DBS_INTERNAL_ERROR = 150,
	BTRIEVE_STATUS_CODE_NESTING_DEPTH_ERROR = 151,
	BTRIEVE_STATUS_CODE_INVALID_PARAMETER_TO_MKDE = 160,
	BTRIEVE_STATUS_CODE_USER_COUNT_LIMIT_EXCEEDED = 161,
	BTRIEVE_STATUS_CODE_CLIENT_TABLE_FULL = 162,
	BTRIEVE_STATUS_CODE_LAST_SEGMENT_ERROR = 163,
	BTRIEVE_STATUS_CODE_LOGIN_FAILED_BAD_USERNAME = 170,
	BTRIEVE_STATUS_CODE_LOGIN_FAILED_BAD_PASSWORD = 171,
	BTRIEVE_STATUS_CODE_LOGIN_FAILED_BAD_DATABASE = 172,
	BTRIEVE_STATUS_CODE_LOGIN_ALREADY_LOGGED_IN = 173,
	BTRIEVE_STATUS_CODE_LOGIN_LOGOUT_FAILED = 174,
	BTRIEVE_STATUS_CODE_LOGIN_WRONG_URI_FORMAT = 175,
	BTRIEVE_STATUS_CODE_LOGIN_FILE_AND_TABLE_NOT_FOUND = 176,
	BTRIEVE_STATUS_CODE_LOGIN_TABLE_NOT_IN_DATABASE = 177,
	BTRIEVE_STATUS_CODE_LOGIN_DIRECTORY_NOT_IN_DATABASE = 178,
	BTRIEVE_STATUS_CODE_LOCK_PARM_OUTOFRANGE = 1001,
	BTRIEVE_STATUS_CODE_MEM_ALLOCATION_ERR = 1002,
	BTRIEVE_STATUS_CODE_MEM_PARM_TOO_SMALL = 1003,
	BTRIEVE_STATUS_CODE_PAGE_SIZE_PARM_OUTOFRANGE = 1004,
	BTRIEVE_STATUS_CODE_INVALID_PREIMAGE_PARM = 1005,
	BTRIEVE_STATUS_CODE_PREIMAGE_BUF_PARM_OUTOFRANGE = 1006,
	BTRIEVE_STATUS_CODE_FILES_PARM_OUTOFRANGE = 1007,
	BTRIEVE_STATUS_CODE_INVALID_INIT_PARM = 1008,
	BTRIEVE_STATUS_CODE_INVALID_TRANS_PARM = 1009,
	BTRIEVE_STATUS_CODE_ERROR_ACC_TRANS_CONTROL_FILE = 1010,
	BTRIEVE_STATUS_CODE_COMPRESSION_BUF_PARM_OUTOFRANGE = 1011,
	BTRIEVE_STATUS_CODE_INV_N_OPTION = 1012,
	BTRIEVE_STATUS_CODE_TASK_LIST_FULL = 1013,
	BTRIEVE_STATUS_CODE_STOP_WARNING = 1014,
	BTRIEVE_STATUS_CODE_POINTER_PARM_INVALID = 1015,
	BTRIEVE_STATUS_CODE_ALREADY_INITIALIZED = 1016,
	BTRIEVE_STATUS_CODE_REQ_CANT_FIND_RES_DLL = 1017,
	BTRIEVE_STATUS_CODE_ALREADY_INSIDE_BTR_FUNCTION = 1018,
	BTRIEVE_STATUS_CODE_CALLBACK_ABORT = 1019,
	BTRIEVE_STATUS_CODE_INTF_COMM_ERROR = 1020,
	BTRIEVE_STATUS_CODE_FAILED_TO_INITIALIZE = 1021,
	BTRIEVE_STATUS_CODE_MKDE_SHUTTING_DOWN = 1022,
	BTRIEVE_STATUS_CODE_INTERNAL_ERROR = 2000,
	BTRIEVE_STATUS_CODE_INSUFFICIENT_MEM_ALLOC = 2001,
	BTRIEVE_STATUS_CODE_INVALID_OPTION = 2002,
	BTRIEVE_STATUS_CODE_NO_LOCAL_ACCESS_ALLOWED = 2003,
	BTRIEVE_STATUS_CODE_SPX_NOT_INSTALLED = 2004,
	BTRIEVE_STATUS_CODE_INCORRECT_SPX_VERSION = 2005,
	BTRIEVE_STATUS_CODE_NO_AVAIL_SPX_CONNECTION = 2006,
	BTRIEVE_STATUS_CODE_INVALID_PTR_PARM = 2007,
	BTRIEVE_STATUS_CODE_CANT_CONNECT_TO_615 = 2008,
	BTRIEVE_STATUS_CODE_CANT_LOAD_MKDE_ROUTER = 2009,
	BTRIEVE_STATUS_CODE_UT_THUNK_NOT_LOADED = 2010,
	BTRIEVE_STATUS_CODE_NO_RESOURCE_DLL = 2011,
	BTRIEVE_STATUS_CODE_OS_ERROR = 2012,
	BTRIEVE_STATUS_CODE_MK_ROUTER_MEM_ERROR = 3000,
	BTRIEVE_STATUS_CODE_MK_NO_LOCAL_ACCESS_ALLOWED = 3001,
	BTRIEVE_STATUS_CODE_MK_NO_RESOURCE_DLL = 3002,
	BTRIEVE_STATUS_CODE_MK_INCOMPAT_COMPONENT = 3003,
	BTRIEVE_STATUS_CODE_MK_TIMEOUT_ERROR = 3004,
	BTRIEVE_STATUS_CODE_MK_OS_ERROR = 3005,
	BTRIEVE_STATUS_CODE_MK_INVALID_SESSION = 3006,
	BTRIEVE_STATUS_CODE_MK_SERVER_NOT_FOUND = 3007,
	BTRIEVE_STATUS_CODE_MK_INVALID_CONFIG = 3008,
	BTRIEVE_STATUS_CODE_MK_NETAPI_NOT_LOADED = 3009,
	BTRIEVE_STATUS_CODE_MK_NWAPI_NOT_LOADED = 3010,
	BTRIEVE_STATUS_CODE_MK_THUNK_NOT_LOADED = 3011,
	BTRIEVE_STATUS_CODE_MK_LOCAL_NOT_LOADED = 3012,
	BTRIEVE_STATUS_CODE_MK_PNSL_NOT_LOADED = 3013,
	BTRIEVE_STATUS_CODE_MK_CANT_FIND_ENGINE = 3014,
	BTRIEVE_STATUS_CODE_MK_INIT_ERROR = 3015,
	BTRIEVE_STATUS_CODE_MK_INTERNAL_ERROR = 3016,
	BTRIEVE_STATUS_CODE_MK_LOCAL_MKDE_DATABUF_TOO_SMALL = 3017,
	BTRIEVE_STATUS_CODE_MK_CLOSED_ERROR = 3018,
	BTRIEVE_STATUS_CODE_MK_SEMAPHORE_ERROR = 3019,
	BTRIEVE_STATUS_CODE_MK_LOADING_ERROR = 3020,
	BTRIEVE_STATUS_CODE_MK_BAD_SRB_FORMAT = 3021,
	BTRIEVE_STATUS_CODE_MK_DATABUF_LEN_TOO_LARGE = 3022,
	BTRIEVE_STATUS_CODE_MK_TASK_TABLE_FULL = 3023,
	BTRIEVE_STATUS_CODE_MK_INVALID_OP_ON_REMOTE = 3024,
	BTRIEVE_STATUS_CODE_MK_PIDS_NOT_LOADED = 3025,
	BTRIEVE_STATUS_CODE_MK_BAD_PIDS = 3026,
	BTRIEVE_STATUS_CODE_MK_IDS_CONNECT_FAILURE = 3027,
	BTRIEVE_STATUS_CODE_MK_IDS_LOGIN_FAILURE = 3028,
	BTRIEVE_STATUS_CODE_NL_FAILURE = 3101,
	BTRIEVE_STATUS_CODE_NL_NOT_INITIALIZED = 3102,
	BTRIEVE_STATUS_CODE_NL_NAME_NOT_FOUND = 3103,
	BTRIEVE_STATUS_CODE_NL_PERMISSION_ERROR = 3104,
	BTRIEVE_STATUS_CODE_NL_NO_AVAILABLE_TRANSPORT = 3105,
	BTRIEVE_STATUS_CODE_NL_CONNECTION_FAILURE = 3106,
	BTRIEVE_STATUS_CODE_NL_OUT_OF_MEMORY = 3107,
	BTRIEVE_STATUS_CODE_NL_INVALID_SESSION = 3108,
	BTRIEVE_STATUS_CODE_NL_MORE_DATA = 3109,
	BTRIEVE_STATUS_CODE_NL_NOT_CONNECTED = 3110,
	BTRIEVE_STATUS_CODE_NL_SEND_FAILURE = 3111,
	BTRIEVE_STATUS_CODE_NL_RECEIVE_FAILURE = 3112,
	BTRIEVE_STATUS_CODE_NL_INVALID_SERVER_TYPE = 3113,
	BTRIEVE_STATUS_CODE_NL_SRT_FULL = 3114,
	BTRIEVE_STATUS_CODE_NL_TRANSPORT_FAILURE = 3115,
	BTRIEVE_STATUS_CODE_NL_RCV_DATA_OVERFLOW = 3116,
	BTRIEVE_STATUS_CODE_NL_CST_FULL = 3117,
	BTRIEVE_STATUS_CODE_NL_INVALID_ADDRESS_FAMILY = 3118,
	BTRIEVE_STATUS_CODE_NL_NO_AUTH_CONTEXT_AVAILABLE = 3119,
	BTRIEVE_STATUS_CODE_NL_INVALID_AUTH_TYPE = 3120,
	BTRIEVE_STATUS_CODE_NL_INVALID_AUTH_OBJECT = 3121,
	BTRIEVE_STATUS_CODE_NL_AUTH_LEN_TOO_SMALL = 3122,
	BTRIEVE_STATUS_CODE_NL_INVALID_SESSION_LEVEL_PARM = 3123,
	BTRIEVE_STATUS_CODE_NL_TASK_TABLE_FULL = 3124,
	BTRIEVE_STATUS_CODE_NL_NDS_NAME_RESOLUTION_ERROR = 3125,
	BTRIEVE_STATUS_CODE_NL_FILE_NAME_RESOLUTION_ERROR = 3126,
	BTRIEVE_STATUS_CODE_NL_IDS_SEND_FAILURE = 3127,
	BTRIEVE_STATUS_CODE_NL_IDS_RCV_FAILURE = 3128,
	BTRIEVE_STATUS_CODE_UNKNOWN = -7
} btrieve_status_code_t;

typedef enum VariableLengthRecordsMode {
   BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_NO,
   BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_YES,
   BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_YES_VARIABLE_ALLOCATION_TAILS,
   BTRIEVE_VARIABLE_LENGTH_RECORDS_MODE_UNKNOWN = -7
} btrieve_variable_length_records_mode_t;

typedef enum {
   BTRIEVE_ACS_MODE_NONE, BTRIEVE_ACS_MODE_NAMED, BTRIEVE_ACS_MODE_NUMBERED,
   BTRIEVE_ACS_MODE_CASE_INSENSITIVE, BTRIEVE_ACS_MODE_DEFAULT, BTRIEVE_ACS_MODE_UNKNOWN = -7
} btrieve_acs_mode_t;

typedef enum {
   BTRIEVE_RECORD_COMPRESSION_MODE_NONE, BTRIEVE_RECORD_COMPRESSION_MODE_BLANK_TRUNCATION,
   BTRIEVE_RECORD_COMPRESSION_MODE_RUN_LENGTH_ENCODING, BTRIEVE_RECORD_COMPRESSION_MODE_UNKNOWN = -7
} btrieve_record_compression_mode_t;

typedef enum {
   BTRIEVE_DUPLICATE_MODE_NOT_ALLOWED, BTRIEVE_DUPLICATE_MODE_ALLOWED_NONREPEATING, 
   BTRIEVE_DUPLICATE_MODE_ALLOWED_REPEATING, BTRIEVE_DUPLICATE_MODE_UNKNOWN = -7
} btrieve_duplicate_mode_t;

typedef enum {
   BTRIEVE_COMPARISON_NONE, BTRIEVE_COMPARISON_EQUAL, BTRIEVE_COMPARISON_GREATER_THAN,
   BTRIEVE_COMPARISON_LESS_THAN, BTRIEVE_COMPARISON_NOT_EQUAL,
   BTRIEVE_COMPARISON_GREATER_THAN_OR_EQUAL, BTRIEVE_COMPARISON_LESS_THAN_OR_EQUAL,
   BTRIEVE_COMPARISON_LIKE, BTRIEVE_COMPARISON_NOT_LIKE,
   BTRIEVE_COMPARISON_UNKNOWN = -7
} btrieve_comparison_t;

typedef enum {
   BTRIEVE_CONNECTOR_LAST, BTRIEVE_CONNECTOR_AND,
   BTRIEVE_CONNECTOR_OR, BTRIEVE_CONNECTOR_UNKNOWN = -7
} btrieve_connector_t;

typedef enum {
   BTRIEVE_DISK_DRIVE_A, BTRIEVE_DISK_DRIVE_B, BTRIEVE_DISK_DRIVE_C, 
   BTRIEVE_DISK_DRIVE_D, BTRIEVE_DISK_DRIVE_E, BTRIEVE_DISK_DRIVE_F, 
   BTRIEVE_DISK_DRIVE_G, BTRIEVE_DISK_DRIVE_H, BTRIEVE_DISK_DRIVE_I, 
   BTRIEVE_DISK_DRIVE_J, BTRIEVE_DISK_DRIVE_K, BTRIEVE_DISK_DRIVE_L, 
   BTRIEVE_DISK_DRIVE_M, BTRIEVE_DISK_DRIVE_N, BTRIEVE_DISK_DRIVE_O, 
   BTRIEVE_DISK_DRIVE_P, BTRIEVE_DISK_DRIVE_Q, BTRIEVE_DISK_DRIVE_R, 
   BTRIEVE_DISK_DRIVE_S, BTRIEVE_DISK_DRIVE_T, BTRIEVE_DISK_DRIVE_U, 
   BTRIEVE_DISK_DRIVE_V, BTRIEVE_DISK_DRIVE_W, BTRIEVE_DISK_DRIVE_X, 
   BTRIEVE_DISK_DRIVE_Y, BTRIEVE_DISK_DRIVE_Z, BTRIEVE_DISK_DRIVE_DEFAULT, 
   BTRIEVE_DISK_DRIVE_UNKNOWN = -7
} btrieve_disk_drive_t;

typedef enum {
   BTRIEVE_VERSION_TYPE_NONE, BTRIEVE_VERSION_TYPE_BTRIEVE_ENGINE, 
   BTRIEVE_VERSION_TYPE_WORKGROUP_ENGINE, BTRIEVE_VERSION_TYPE_DOS_WORKSTATION, 
   BTRIEVE_VERSION_TYPE_CLIENT_REQUESTOR, BTRIEVE_VERSION_TYPE_WINDOWS_SERVER_ENGINE, 
   BTRIEVE_VERSION_TYPE_UNIX, BTRIEVE_VERSION_TYPE_CLIENT_ENGINE,
   BTRIEVE_VERSION_TYPE_UNKNOWN = -7
} btrieve_version_type_t;

typedef enum { 
   BTRIEVE_CREATE_MODE_OVERWRITE, BTRIEVE_CREATE_MODE_NO_OVERWRITE, BTRIEVE_CREATE_MODE_UNKNOWN = -7
} btrieve_create_mode_t;

typedef enum {
   BTRIEVE_LOCATION_MODE_NO_PREFERENCE, BTRIEVE_LOCATION_MODE_FORCE_LOCAL, 
   BTRIEVE_LOCATION_MODE_FORCE_REMOTE, BTRIEVE_LOCATION_MODE_UNKNOWN = -7
} btrieve_location_mode_t;

typedef enum {
   BTRIEVE_LOCK_MODE_NONE, BTRIEVE_LOCK_MODE_SINGLE_WAIT, BTRIEVE_LOCK_MODE_SINGLE_NO_WAIT,
   BTRIEVE_LOCK_MODE_MULTIPLE_WAIT, BTRIEVE_LOCK_MODE_MULTIPLE_NO_WAIT, BTRIEVE_LOCK_MODE_UNKNOWN = -7
} btrieve_lock_mode_t;

typedef enum { 
   BTRIEVE_OPEN_MODE_NORMAL, BTRIEVE_OPEN_MODE_ACCELERATED, 
   BTRIEVE_OPEN_MODE_READ_ONLY, BTRIEVE_OPEN_MODE_EXCLUSIVE,
   BTRIEVE_OPEN_MODE_UNKNOWN = -7
} btrieve_open_mode_t;

typedef enum {
   BTRIEVE_OWNER_MODE_NONE, BTRIEVE_OWNER_MODE_NO_ENCRYPTION_NO_READ_ALLOWED, 
   BTRIEVE_OWNER_MODE_NO_ENCRYPTION_READ_ALLOWED, BTRIEVE_OWNER_MODE_ENCRYPTION_NO_READ_ALLOWED, 
   BTRIEVE_OWNER_MODE_ENCRYPTION_READ_ALLOWED, BTRIEVE_OWNER_MODE_UNKNOWN = -7
} btrieve_owner_mode_t;

typedef enum { 
   BTRIEVE_TRANSACTION_MODE_EXCLUSIVE, BTRIEVE_TRANSACTION_MODE_CONCURRENT_WRITE_WAIT, 
   BTRIEVE_TRANSACTION_MODE_CONCURRENT_NO_WRITE_WAIT, BTRIEVE_TRANSACTION_MODE_UNKNOWN = -7
} btrieve_transaction_mode_t;

typedef enum {
   BTRIEVE_UNLOCK_MODE_SINGLE, BTRIEVE_UNLOCK_MODE_MULTIPLE, BTRIEVE_UNLOCK_MODE_UNKNOWN = -7
} btrieve_unlock_mode_t;

typedef enum {
   BTRIEVE_INDEX_1 = 0, BTRIEVE_INDEX_2 = 1, BTRIEVE_INDEX_3 = 2,
   BTRIEVE_INDEX_4 = 3, BTRIEVE_INDEX_5 = 4, BTRIEVE_INDEX_6 = 5,
   BTRIEVE_INDEX_7 = 6, BTRIEVE_INDEX_8 = 7, BTRIEVE_INDEX_9 = 8,
   BTRIEVE_INDEX_10 = 9, BTRIEVE_INDEX_11 = 10, BTRIEVE_INDEX_12 = 11,
   BTRIEVE_INDEX_13 = 12, BTRIEVE_INDEX_14 = 13, BTRIEVE_INDEX_15 = 14,
   BTRIEVE_INDEX_16 = 15, BTRIEVE_INDEX_17 = 16, BTRIEVE_INDEX_18 = 17,
   BTRIEVE_INDEX_19 = 18, BTRIEVE_INDEX_20 = 19, BTRIEVE_INDEX_21 = 20,
   BTRIEVE_INDEX_22 = 21, BTRIEVE_INDEX_23 = 22, BTRIEVE_INDEX_24 = 23,
   BTRIEVE_INDEX_25 = 24, BTRIEVE_INDEX_26 = 25, BTRIEVE_INDEX_27 = 26,
   BTRIEVE_INDEX_28 = 27, BTRIEVE_INDEX_29 = 28, BTRIEVE_INDEX_30 = 29,
   BTRIEVE_INDEX_31 = 30, BTRIEVE_INDEX_32 = 31, BTRIEVE_INDEX_33 = 32,
   BTRIEVE_INDEX_34 = 33, BTRIEVE_INDEX_35 = 34, BTRIEVE_INDEX_36 = 35,
   BTRIEVE_INDEX_37 = 36, BTRIEVE_INDEX_38 = 37, BTRIEVE_INDEX_39 = 38,
   BTRIEVE_INDEX_40 = 39, BTRIEVE_INDEX_41 = 40, BTRIEVE_INDEX_42 = 41,
   BTRIEVE_INDEX_43 = 42, BTRIEVE_INDEX_44 = 43, BTRIEVE_INDEX_45 = 44,
   BTRIEVE_INDEX_46 = 45, BTRIEVE_INDEX_47 = 46, BTRIEVE_INDEX_48 = 47,
   BTRIEVE_INDEX_49 = 48, BTRIEVE_INDEX_50 = 49, BTRIEVE_INDEX_51 = 50,
   BTRIEVE_INDEX_52 = 51, BTRIEVE_INDEX_53 = 52, BTRIEVE_INDEX_54 = 53,
   BTRIEVE_INDEX_55 = 54, BTRIEVE_INDEX_56 = 55, BTRIEVE_INDEX_57 = 56,
   BTRIEVE_INDEX_58 = 57, BTRIEVE_INDEX_59 = 58, BTRIEVE_INDEX_60 = 59,
   BTRIEVE_INDEX_61 = 60, BTRIEVE_INDEX_62 = 61, BTRIEVE_INDEX_63 = 62,
   BTRIEVE_INDEX_64 = 63, BTRIEVE_INDEX_65 = 64, BTRIEVE_INDEX_66 = 65,
   BTRIEVE_INDEX_67 = 66, BTRIEVE_INDEX_68 = 67, BTRIEVE_INDEX_69 = 68,
   BTRIEVE_INDEX_70 = 69, BTRIEVE_INDEX_71 = 70, BTRIEVE_INDEX_72 = 71,
   BTRIEVE_INDEX_73 = 72, BTRIEVE_INDEX_74 = 73, BTRIEVE_INDEX_75 = 74,
   BTRIEVE_INDEX_76 = 75, BTRIEVE_INDEX_77 = 76, BTRIEVE_INDEX_78 = 77,
   BTRIEVE_INDEX_79 = 78, BTRIEVE_INDEX_80 = 79, BTRIEVE_INDEX_81 = 80,
   BTRIEVE_INDEX_82 = 81, BTRIEVE_INDEX_83 = 82, BTRIEVE_INDEX_84 = 83,
   BTRIEVE_INDEX_85 = 84, BTRIEVE_INDEX_86 = 85, BTRIEVE_INDEX_87 = 86,
   BTRIEVE_INDEX_88 = 87, BTRIEVE_INDEX_89 = 88, BTRIEVE_INDEX_90 = 89,
   BTRIEVE_INDEX_91 = 90, BTRIEVE_INDEX_92 = 91, BTRIEVE_INDEX_93 = 92,
   BTRIEVE_INDEX_94 = 93, BTRIEVE_INDEX_95 = 94, BTRIEVE_INDEX_96 = 95,
   BTRIEVE_INDEX_97 = 96, BTRIEVE_INDEX_98 = 97, BTRIEVE_INDEX_99 = 98,
   BTRIEVE_INDEX_100 = 99, BTRIEVE_INDEX_101 = 100, BTRIEVE_INDEX_102 = 101,
   BTRIEVE_INDEX_103 = 102, BTRIEVE_INDEX_104 = 103, BTRIEVE_INDEX_105 = 104,
   BTRIEVE_INDEX_106 = 105, BTRIEVE_INDEX_107 = 106, BTRIEVE_INDEX_108 = 107,
   BTRIEVE_INDEX_109 = 108, BTRIEVE_INDEX_110 = 109, BTRIEVE_INDEX_111 = 110,
   BTRIEVE_INDEX_112 = 111, BTRIEVE_INDEX_113 = 112, BTRIEVE_INDEX_114 = 113,
   BTRIEVE_INDEX_115 = 114, BTRIEVE_INDEX_116 = 115, BTRIEVE_INDEX_117 = 116,
   BTRIEVE_INDEX_118 = 117, BTRIEVE_INDEX_119 = 118, BTRIEVE_INDEX_SYSTEM = 125, 
   BTRIEVE_INDEX_NONE = -1, BTRIEVE_INDEX_UNKNOWN = -7
} btrieve_index_t;

typedef enum {
   BTRIEVE_DATA_TYPE_CHAR, BTRIEVE_DATA_TYPE_ZSTRING,
   BTRIEVE_DATA_TYPE_INTEGER, BTRIEVE_DATA_TYPE_UNSIGNED_BINARY,
   BTRIEVE_DATA_TYPE_FLOAT, BTRIEVE_DATA_TYPE_AUTOINCREMENT,
   BTRIEVE_DATA_TYPE_DATE, BTRIEVE_DATA_TYPE_NUMERICSTS,
   BTRIEVE_DATA_TYPE_TIME, BTRIEVE_DATA_TYPE_NUMERICSA,
   BTRIEVE_DATA_TYPE_DECIMAL, BTRIEVE_DATA_TYPE_CURRENCY,
   BTRIEVE_DATA_TYPE_MONEY, BTRIEVE_DATA_TYPE_TIMESTAMP,
   BTRIEVE_DATA_TYPE_LOGICAL, BTRIEVE_DATA_TYPE_WSTRING,
   BTRIEVE_DATA_TYPE_NUMERIC, BTRIEVE_DATA_TYPE_WZSTRING,
   BTRIEVE_DATA_TYPE_BFLOAT, BTRIEVE_DATA_TYPE_GUID,
   BTRIEVE_DATA_TYPE_LSTRING, BTRIEVE_DATA_TYPE_NULL_INDICATOR_SEGMENT,
   BTRIEVE_DATA_TYPE_LEGACY_STRING, BTRIEVE_DATA_TYPE_LEGACY_BINARY,
   BTRIEVE_DATA_TYPE_UNKNOWN = -7
} btrieve_data_type_t;

typedef enum {
   BTRIEVE_FILE_VERSION_6_0, BTRIEVE_FILE_VERSION_6_1,
   BTRIEVE_FILE_VERSION_7_0, BTRIEVE_FILE_VERSION_8_0,
   BTRIEVE_FILE_VERSION_9_0, BTRIEVE_FILE_VERSION_9_5,
   BTRIEVE_FILE_VERSION_DEFAULT, /* preserve enum value for DEFAULT */
   BTRIEVE_FILE_VERSION_13_0,
   BTRIEVE_FILE_VERSION_UNKNOWN = -7
} btrieve_file_version_t;

typedef enum {
   BTRIEVE_FREE_SPACE_THRESHOLD_10_PERCENT, BTRIEVE_FREE_SPACE_THRESHOLD_20_PERCENT, 
   BTRIEVE_FREE_SPACE_THRESHOLD_30_PERCENT, BTRIEVE_FREE_SPACE_THRESHOLD_DEFAULT, 
   BTRIEVE_FREE_SPACE_THRESHOLD_UNKNOWN = -7
} btrieve_free_space_threshold_t;

typedef enum {
   BTRIEVE_NULL_KEY_MODE_ALL_SEGMENTS, BTRIEVE_NULL_KEY_MODE_ANY_SEGMENTS, 
   BTRIEVE_NULL_KEY_MODE_NONE, BTRIEVE_NULL_KEY_MODE_UNKNOWN = -7
} btrieve_null_key_mode_t;

typedef enum {
   BTRIEVE_PAGE_LOCK_TYPE_NONE, BTRIEVE_PAGE_LOCK_TYPE_DATA_PAGE,
   BTRIEVE_PAGE_LOCK_TYPE_INDEX_PAGE, BTRIEVE_PAGE_LOCK_TYPE_VARIABLE_PAGE,
   BTRIEVE_PAGE_LOCK_TYPE_UNKNOWN = -7
} btrieve_page_lock_type_t;

typedef enum {
   BTRIEVE_PAGE_SIZE_512, BTRIEVE_PAGE_SIZE_1024, 
   BTRIEVE_PAGE_SIZE_1536, BTRIEVE_PAGE_SIZE_2048, 
   BTRIEVE_PAGE_SIZE_3072, BTRIEVE_PAGE_SIZE_3584,
   BTRIEVE_PAGE_SIZE_4096, BTRIEVE_PAGE_SIZE_8192, 
   BTRIEVE_PAGE_SIZE_16384, BTRIEVE_PAGE_SIZE_DEFAULT,
   BTRIEVE_PAGE_SIZE_UNKNOWN = -7
} btrieve_page_size_t;

typedef enum {
   BTRIEVE_SYSTEM_DATA_MODE_YES, BTRIEVE_SYSTEM_DATA_MODE_NO, 
   BTRIEVE_SYSTEM_DATA_MODE_DEFAULT, BTRIEVE_SYSTEM_DATA_MODE_UNKNOWN = -7
} btrieve_system_data_mode_t;

typedef struct btrieve_bulk_create_payload *btrieve_bulk_create_payload_t;
typedef struct btrieve_bulk_create_result *btrieve_bulk_create_result_t;

typedef struct btrieve_bulk_retrieve_attributes *btrieve_bulk_retrieve_attributes_t;

typedef struct btrieve_bulk_retrieve_result *btrieve_bulk_retrieve_result_t;

typedef struct btrieve_chunk_attributes *btrieve_chunk_attributes_t;
typedef struct btrieve_client *btrieve_client_t;
typedef struct btrieve_file *btrieve_file_t;
typedef struct btrieve_file_attributes *btrieve_file_attributes_t;
typedef struct btrieve_file_information *btrieve_file_information_t;
typedef struct btrieve_filter *btrieve_filter_t;
typedef struct btrieve_index_attributes *btrieve_index_attributes_t;
typedef struct btrieve_key_segment *btrieve_key_segment_t;
typedef struct btrieve_version *btrieve_version_t;

extern LINKAGE btrieve_acs_mode_t BtrieveKeySegmentGetACSMode(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_data_type_t BtrieveKeySegmentGetDataType(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_duplicate_mode_t BtrieveKeySegmentGetDuplicateMode(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_file_version_t BtrieveFileInformationGetFileVersion(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_free_space_threshold_t BtrieveFileInformationGetFreeSpaceThreshold(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_index_t BtrieveFileInformationGetDuplicateRecordConflictIndex(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_index_t BtrieveFileInformationGetLockOwnerIndex(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_index_t BtrieveFileInformationGetLogIndex(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_index_t BtrieveKeySegmentGetIndex(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_lock_mode_t BtrieveFileInformationGetLockOwnerExplicitLockMode(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_null_key_mode_t BtrieveKeySegmentGetNullKeyMode(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_owner_mode_t BtrieveFileInformationGetOwnerMode(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_page_lock_type_t BtrieveFileInformationGetLockOwnerPageLockType(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_page_size_t BtrieveFileInformationGetPageSize(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_record_compression_mode_t BtrieveFileInformationGetRecordCompressionMode(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_status_code_t BtrieveBulkCreatePayloadAddRecord(btrieve_bulk_create_payload_t bulkCreatePayload, const char *record, int recordLength);
extern LINKAGE btrieve_status_code_t BtrieveBulkCreatePayloadAllocate(btrieve_bulk_create_payload_t *btrieveBulkCreatePayloadPtr);
extern LINKAGE btrieve_status_code_t BtrieveBulkCreatePayloadFree(btrieve_bulk_create_payload_t bulkCreatePayload);
extern LINKAGE btrieve_status_code_t BtrieveBulkCreateResultAllocate(btrieve_bulk_create_result_t *btrieveBulkCreateResultPtr);
extern LINKAGE btrieve_status_code_t BtrieveBulkCreateResultFree(btrieve_bulk_create_result_t bulkCreateResult);
extern LINKAGE btrieve_status_code_t BtrieveBulkCreateResultGetLastStatusCode(btrieve_bulk_create_result_t bulkCreateResult);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesAddField(btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, int offset, int length);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesAddFilter(btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, btrieve_filter_t filter);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesAllocate(btrieve_bulk_retrieve_attributes_t *bulkRetrieveAttributesPtr);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesFree(btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesSetMaximumRecordCount(btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, int maximumRecordCount);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesSetMaximumRejectCount(btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, int maximumRejectCount);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveAttributesSetSkipCurrentRecord(btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, int skipCurrentRecord);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveResultAllocate(btrieve_bulk_retrieve_result_t *bulkRetrieveResultPtr);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveResultFree(btrieve_bulk_retrieve_result_t bulkRetrieveResult);
extern LINKAGE btrieve_status_code_t BtrieveBulkRetrieveResultGetLastStatusCode(btrieve_bulk_retrieve_result_t bulkRetrieveResult);
extern LINKAGE btrieve_status_code_t BtrieveClientAllocate(btrieve_client_t *btrieveClientPtr, int serviceAgentIdentifier, int clientIdentifier);
extern LINKAGE btrieve_status_code_t BtrieveClientContinuousOperationBegin(btrieve_client_t client, const char *pathNames);
extern LINKAGE btrieve_status_code_t BtrieveClientContinuousOperationBeginW(btrieve_client_t client, const wchar_t *pathNames);
extern LINKAGE btrieve_status_code_t BtrieveClientContinuousOperationEnd(btrieve_client_t client, const char *pathNames);
extern LINKAGE btrieve_status_code_t BtrieveClientContinuousOperationEndW(btrieve_client_t client, const wchar_t *pathNames);
extern LINKAGE btrieve_status_code_t BtrieveClientFileClose(btrieve_client_t client, btrieve_file_t file);
extern LINKAGE btrieve_status_code_t BtrieveClientFileCreate(btrieve_client_t client, const btrieve_file_attributes_t fileAttributes, const btrieve_index_attributes_t indexAttributes, const char *fileName, btrieve_create_mode_t createMode, btrieve_location_mode_t locationMode);
extern LINKAGE btrieve_status_code_t BtrieveClientFileCreateW(btrieve_client_t client, const btrieve_file_attributes_t fileAttributes, const btrieve_index_attributes_t indexAttributes, const wchar_t *fileName, btrieve_create_mode_t createMode, btrieve_location_mode_t locationMode);
extern LINKAGE btrieve_status_code_t BtrieveClientFileDelete(btrieve_client_t client, const char *fileName);
extern LINKAGE btrieve_status_code_t BtrieveClientFileDeleteW(btrieve_client_t client, const wchar_t *fileName);
extern LINKAGE btrieve_status_code_t BtrieveClientFileOpen(btrieve_client_t client, btrieve_file_t *btrieveFilePtr, const char *fileName, const char *ownerName, btrieve_open_mode_t openMode, btrieve_location_mode_t locationMode);
extern LINKAGE btrieve_status_code_t BtrieveClientFileOpenW(btrieve_client_t client, btrieve_file_t *btrieveFilePtr, const wchar_t *fileName, const char *ownerName, btrieve_open_mode_t openMode, btrieve_location_mode_t locationMode);
extern LINKAGE btrieve_status_code_t BtrieveClientFileRename(btrieve_client_t client, const char *existingFileName, const char *newFileName);
extern LINKAGE btrieve_status_code_t BtrieveClientFileRenameW(btrieve_client_t client, const wchar_t *existingFileName, const wchar_t *newFileName);
extern LINKAGE btrieve_status_code_t BtrieveClientFree(btrieve_client_t client);
extern LINKAGE btrieve_status_code_t BtrieveClientGetCurrentDirectory(btrieve_client_t client, btrieve_disk_drive_t diskDrive, char *currentDirectory, int currentDirectorySize);
extern LINKAGE btrieve_status_code_t BtrieveClientGetCurrentDirectoryW(btrieve_client_t client, btrieve_disk_drive_t diskDrive, wchar_t *currentDirectoryW, int currentDirectorySize);
extern LINKAGE btrieve_status_code_t BtrieveClientGetLastStatusCode(btrieve_client_t client);
extern LINKAGE btrieve_status_code_t BtrieveClientGetVersion(btrieve_client_t client, btrieve_version_t version, btrieve_file_t file);
extern LINKAGE btrieve_status_code_t BtrieveClientLogin(btrieve_client_t client, const char *databaseURI);
extern LINKAGE btrieve_status_code_t BtrieveClientLoginW(btrieve_client_t client, const wchar_t *databaseURI);
extern LINKAGE btrieve_status_code_t BtrieveClientLogout(btrieve_client_t client, const char *databaseURI);
extern LINKAGE btrieve_status_code_t BtrieveClientLogoutW(btrieve_client_t client, const wchar_t *databaseURI);
extern LINKAGE btrieve_status_code_t BtrieveClientReset(btrieve_client_t client);
extern LINKAGE btrieve_status_code_t BtrieveClientSetCurrentDirectory(btrieve_client_t client, const char *currentDirectory);
extern LINKAGE btrieve_status_code_t BtrieveClientSetCurrentDirectoryW(btrieve_client_t client, const wchar_t *currentDirectory);
extern LINKAGE btrieve_status_code_t BtrieveClientStop(btrieve_client_t client);
extern LINKAGE btrieve_status_code_t BtrieveClientTransactionAbort(btrieve_client_t client);
extern LINKAGE btrieve_status_code_t BtrieveClientTransactionBegin(btrieve_client_t client, btrieve_transaction_mode_t transactionMode, btrieve_lock_mode_t lockMode);
extern LINKAGE btrieve_status_code_t BtrieveClientTransactionEnd(btrieve_client_t client);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesAllocate(btrieve_file_attributes_t *btrieveFileAttributesPtr);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesFree(btrieve_file_attributes_t fileAttributes);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetBalancedIndexes(btrieve_file_attributes_t fileAttributes, int enableBalancedIndexes);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetFileVersion(btrieve_file_attributes_t fileAttributes, btrieve_file_version_t fileVersion);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetFixedRecordLength(btrieve_file_attributes_t fileAttributes, int fixedRecordLength);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetFreeSpaceThreshold(btrieve_file_attributes_t fileAttributes, btrieve_free_space_threshold_t freeSpaceThreshold);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetKeyOnly(btrieve_file_attributes_t fileAttributes, int enableKeyOnly);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetPageSize(btrieve_file_attributes_t fileAttributes, btrieve_page_size_t pageSize, int enablePageCompression);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetPreallocatedPageCount(btrieve_file_attributes_t fileAttributes, int preallocatedPageCount);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetRecordCompressionMode(btrieve_file_attributes_t fileAttributes, btrieve_record_compression_mode_t recordCompressionMode);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetReservedDuplicatePointerCount(btrieve_file_attributes_t fileAttributes, int reservedDuplicatePointerCount);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetSystemDataMode(btrieve_file_attributes_t fileAttributes, btrieve_system_data_mode_t systemDataMode);
extern LINKAGE btrieve_status_code_t BtrieveFileAttributesSetVariableLengthRecordsMode(btrieve_file_attributes_t fileAttributes, btrieve_variable_length_records_mode_t variableLengthRecordsMode);
extern LINKAGE btrieve_status_code_t BtrieveFileBulkCreate(btrieve_file_t file, const btrieve_bulk_create_payload_t bulkCreatePayload, btrieve_bulk_create_result_t bulkCreateResult);
extern LINKAGE btrieve_status_code_t BtrieveFileBulkRetrieveNext(btrieve_file_t file, const btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, btrieve_bulk_retrieve_result_t bulkRetrieveResult, btrieve_lock_mode_t lockMode);
extern LINKAGE btrieve_status_code_t BtrieveFileBulkRetrievePrevious(btrieve_file_t file, const btrieve_bulk_retrieve_attributes_t bulkRetrieveAttributes, btrieve_bulk_retrieve_result_t bulkRetrieveResult, btrieve_lock_mode_t lockMode);
extern LINKAGE btrieve_status_code_t BtrieveFileGetInformation(btrieve_file_t file, btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_status_code_t BtrieveFileGetLastStatusCode(btrieve_file_t file);
extern LINKAGE btrieve_status_code_t BtrieveFileIndexCreate(btrieve_file_t file, const btrieve_index_attributes_t indexAttributes);
extern LINKAGE btrieve_status_code_t BtrieveFileIndexDrop(btrieve_file_t file, btrieve_index_t index);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationAllocate(btrieve_file_information_t *btrieveFileInformationPtr);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationFree(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetGatewayName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetKeySegment(btrieve_file_information_t fileInformation, btrieve_key_segment_t keySegment, int keySegmentNumber);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetLastStatusCode(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetLockOwnerName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetReferentialIntegrityFileName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetSecurityCurrentDatabaseName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetSecurityCurrentUserName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetSecurityHandleDatabaseName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetSecurityHandleTableName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetSecurityHandleUserName(btrieve_file_information_t fileInformation, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileInformationGetSegmentFileName(btrieve_file_information_t fileInformation, int segmentFileNumber, char *name, int nameSize);
extern LINKAGE btrieve_status_code_t BtrieveFileKeyRetrieve(btrieve_file_t file, btrieve_comparison_t comparison, btrieve_index_t index, const char *key, int keyLength);
extern LINKAGE btrieve_status_code_t BtrieveFileKeyRetrieveFirst(btrieve_file_t file, btrieve_index_t index, char *key, int keySize);
extern LINKAGE btrieve_status_code_t BtrieveFileKeyRetrieveLast(btrieve_file_t file, btrieve_index_t index, char *key, int keySize);
extern LINKAGE btrieve_status_code_t BtrieveFileKeyRetrieveNext(btrieve_file_t file, char *key, int keySize);
extern LINKAGE btrieve_status_code_t BtrieveFileKeyRetrievePrevious(btrieve_file_t file, char *key, int keySize);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordAppendChunk(btrieve_file_t file, const char *chunk, int chunkLength);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordCreate(btrieve_file_t file, char *record, int recordLength);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordDelete(btrieve_file_t file);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordTruncate(btrieve_file_t file, int offset);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordUnlock(btrieve_file_t file, btrieve_unlock_mode_t unlockMode);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordUpdate(btrieve_file_t file, const char *record, int recordLength);
extern LINKAGE btrieve_status_code_t BtrieveFileRecordUpdateChunk(btrieve_file_t file, int offset, const char *chunk, int chunkLength);
extern LINKAGE btrieve_status_code_t BtrieveFileSetOwner(btrieve_file_t file, btrieve_owner_mode_t ownerMode, const char *ownerName, const char *ownerNameAgain, int useLongOwnerName);
extern LINKAGE btrieve_status_code_t BtrieveFileUnlockCursorPosition(btrieve_file_t file, long long cursorPosition);
extern LINKAGE btrieve_status_code_t BtrieveFilterAllocate(btrieve_filter_t *btrieveFilterPtr);
extern LINKAGE btrieve_status_code_t BtrieveFilterFree(btrieve_filter_t filter);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetACSMode(btrieve_filter_t filter, btrieve_acs_mode_t ACSMode);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetACSName(btrieve_filter_t filter, const char *name);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetACSUserDefined(btrieve_filter_t filter, const char *name);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetComparison(btrieve_filter_t filter, btrieve_comparison_t comparison);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetComparisonConstant(btrieve_filter_t filter, const char *constant, int constantLength);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetComparisonField(btrieve_filter_t filter, int offset);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetConnector(btrieve_filter_t filter, btrieve_connector_t connector);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetField(btrieve_filter_t filter, int offset, int length, btrieve_data_type_t dataType);
extern LINKAGE btrieve_status_code_t BtrieveFilterSetLikeCodePageName(btrieve_filter_t filter, const char *name);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesAddKeySegment(btrieve_index_attributes_t indexAttributes, btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesAllocate(btrieve_index_attributes_t *btrieveIndexAttributesPtr);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesFree(btrieve_index_attributes_t indexAttributes);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetACSMode(btrieve_index_attributes_t indexAttributes, btrieve_acs_mode_t ACSMode);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetACSName(btrieve_index_attributes_t indexAttributes, const char *ACSName);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetACSNumber(btrieve_index_attributes_t indexAttributes, int ACSNumber);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetACSUserDefined(btrieve_index_attributes_t indexAttributes, const char *ACSName, const char *ACSMap, int ACSMapLength);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetDuplicateMode(btrieve_index_attributes_t indexAttributes, btrieve_duplicate_mode_t duplicateMode);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetIndex(btrieve_index_attributes_t indexAttributes, btrieve_index_t index);
extern LINKAGE btrieve_status_code_t BtrieveIndexAttributesSetModifiable(btrieve_index_attributes_t indexAttributes, int enableModifiable);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentAllocate(btrieve_key_segment_t *btrieveKeySegmentPtr);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentFree(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentGetLastStatusCode(btrieve_key_segment_t keySegment);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentSetDescendingSortOrder(btrieve_key_segment_t keySegment, int setDescendingSortOrder);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentSetField(btrieve_key_segment_t keySegment, int offset, int length, btrieve_data_type_t dataType);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentSetNullKeyMode(btrieve_key_segment_t keySegment, btrieve_null_key_mode_t nullKeyMode);
extern LINKAGE btrieve_status_code_t BtrieveKeySegmentSetNullValue(btrieve_key_segment_t keySegment, int nullValue);
extern LINKAGE btrieve_status_code_t BtrieveVersionAllocate(btrieve_version_t *btrieveVersionPtr);
extern LINKAGE btrieve_status_code_t BtrieveVersionFree(btrieve_version_t version);
extern LINKAGE btrieve_status_code_t BtrieveVersionGetLastStatusCode(btrieve_version_t version);
extern LINKAGE btrieve_system_data_mode_t BtrieveFileInformationGetSystemDataMode(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_variable_length_records_mode_t BtrieveFileInformationGetVariableLengthRecordsMode(btrieve_file_information_t fileInformation);
extern LINKAGE btrieve_version_type_t BtrieveVersionGetClientVersionType(btrieve_version_t version);
extern LINKAGE btrieve_version_type_t BtrieveVersionGetLocalVersionType(btrieve_version_t version);
extern LINKAGE btrieve_version_type_t BtrieveVersionGetRemoteVersionType(btrieve_version_t version);
extern LINKAGE const char *BtrieveACSModeToString(btrieve_acs_mode_t ACSMode);
extern LINKAGE const char *BtrieveDataTypeToString(btrieve_data_type_t dataType);
extern LINKAGE const char *BtrieveDuplicateModeToString(btrieve_duplicate_mode_t duplicateMode);
extern LINKAGE const char *BtrieveFileVersionToString(btrieve_file_version_t fileVersion);
extern LINKAGE const char *BtrieveFreeSpaceThresholdToString(btrieve_free_space_threshold_t freeSpaceThreshold);
extern LINKAGE const char *BtrieveIndexToString(btrieve_index_t index);
extern LINKAGE const char *BtrieveLockModeToString(btrieve_lock_mode_t lockMode);
extern LINKAGE const char *BtrieveNullKeyModeToString(btrieve_null_key_mode_t nullKeyMode);
extern LINKAGE const char *BtrieveOwnerModeToString(btrieve_owner_mode_t ownerMode);
extern LINKAGE const char *BtrievePageLockTypeToString(btrieve_page_lock_type_t pageLockType);
extern LINKAGE const char *BtrievePageSizeToString(btrieve_page_size_t pageSize);
extern LINKAGE const char *BtrieveRecordCompressionModeToString(btrieve_record_compression_mode_t RecordCompressionMode);
extern LINKAGE const char *BtrieveStatusCodeToString(btrieve_status_code_t statusCode);
extern LINKAGE const char *BtrieveSystemDataModeToString(btrieve_system_data_mode_t systemDataMode);
extern LINKAGE const char *BtrieveVariableLengthRecordsModeToString(btrieve_variable_length_records_mode_t variableLengthRecordsMode);
extern LINKAGE const char *BtrieveVersionTypeToString(btrieve_version_type_t versionType);
extern LINKAGE int BtrieveBulkCreateResultGetRecordCount(btrieve_bulk_create_result_t bulkCreateResult);
extern LINKAGE long long BtrieveBulkCreateResultGetRecordCursorPosition(btrieve_bulk_create_result_t bulkCreateResult, int recordNumber);
extern LINKAGE int BtrieveBulkRetrieveResultGetRecord(btrieve_bulk_retrieve_result_t bulkRetrieveResult, int recordNumber, char *record, int recordSize);
extern LINKAGE int BtrieveBulkRetrieveResultGetRecordCount(btrieve_bulk_retrieve_result_t bulkRetrieveResult);
extern LINKAGE long long BtrieveBulkRetrieveResultGetRecordCursorPosition(btrieve_bulk_retrieve_result_t bulkRetrieveResult, int recordNumber);
extern LINKAGE int BtrieveBulkRetrieveResultGetRecordLength(btrieve_bulk_retrieve_result_t bulkRetrieveResult, int recordNumber);
extern LINKAGE int BtrieveClientGetClientIdentifier(btrieve_client_t client);
extern LINKAGE int BtrieveClientGetServiceAgentIdentifier(btrieve_client_t client);
extern LINKAGE long long BtrieveFileGetCursorPosition(btrieve_file_t file);
extern LINKAGE int BtrieveFileGetNumerator(btrieve_file_t file, btrieve_index_t index, const char *key, int keyLength, long long cursorPosition, int denominator);
extern LINKAGE int BtrieveFileGetPercentage(btrieve_file_t file, btrieve_index_t index, const char *key, int keyLength, long long cursorPosition);
extern LINKAGE int BtrieveFileInformationGetBalancedIndexes(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetClientTransactions(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetContinuousOperation(btrieve_file_information_t fileInformation);
extern LINKAGE long long BtrieveFileInformationGetDuplicateRecordConflictCursorPosition(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetExplicitLocks(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetFixedRecordLength(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetGatewayMajorVersion(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetGatewayMinorVersion(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetGatewayPatchLevel(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetGatewayPlatform(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetHandleCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetIdentifier(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetIndexCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetKeyOnly(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerClientIdentifier(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerFileLock(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerImplicitLock(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerRecordLock(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerSameProcess(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerServiceAgentIdentifier(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerTimeInTransaction(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerTransactionLevel(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerWriteHold(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLockOwnerWriteNoWait(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetLoggable(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetOpenTimestamp(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetPageCompression(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetPagePreallocation(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetReadOnly(btrieve_file_information_t fileInformation);
extern LINKAGE long long BtrieveFileInformationGetRecordCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetReferentialIntegrityConstraints(btrieve_file_information_t fileInformation);
extern LINKAGE long long BtrieveFileInformationGetReferentialIntegrityCursorPosition(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetReferentialIntegrityOperationCode(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseAuthenticationByDatabase(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseAuthorizationByDatabase(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseBtpasswd(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseExplicit(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseImplicit(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabasePAM(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseRTSSComplete(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseRTSSDisabled(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseRTSSPreauthorized(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseTrusted(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseWindowsNamedPipe(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityCurrentDatabaseWorkgroup(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleAuthenticationByDatabase(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleAuthorizationByDatabase(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleBtpasswd(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleExplicit(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleImplicit(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandlePAM(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleRTSSComplete(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleRTSSDisabled(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleRTSSPreauthorized(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleTrusted(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleWindowsNamedPipe(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityHandleWorkgroup(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionAlter(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionCreateFile(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionCreateRecord(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionCreateStoredProcedure(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionCreateView(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionDelete(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionExecute(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionNoRights(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionOpen(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionRead(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionRefer(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSecurityPermissionUpdate(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSegmentCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSegmented(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSystemIndexPresent(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSystemIndexSize(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSystemIndexUsed(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetSystemIndexVersion(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetUnusedDuplicatePointerCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetUnusedPageCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetUsageCount(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileInformationGetWrongOwner(btrieve_file_information_t fileInformation);
extern LINKAGE int BtrieveFileRecordRetrieve(btrieve_file_t file, btrieve_comparison_t comparison, btrieve_index_t index, const char *key, int keyLength, char *record, int recordSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveFileRecordRetrieveByCursorPosition(btrieve_file_t file, btrieve_index_t index, long long cursorPosition, char *record, int recordSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveFileRecordRetrieveByFraction(btrieve_file_t file, btrieve_index_t index, int numerator, int denominator, char *record, int recordSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveFileRecordRetrieveByPercentage(btrieve_file_t file, btrieve_index_t index, int percentage, char *record, int recordSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveFileRecordRetrieveChunk(btrieve_file_t file, int offset, int length, char *chunk, int chunkSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveFileRecordRetrieveFirst(btrieve_file_t file, btrieve_index_t index, char *record, int recordSize, btrieve_lock_mode_t lockMode); 
extern LINKAGE int BtrieveFileRecordRetrieveLast(btrieve_file_t file, btrieve_index_t index, char *record, int recordSize, btrieve_lock_mode_t lockMode); 
extern LINKAGE int BtrieveFileRecordRetrieveNext(btrieve_file_t file, char *record, int recordSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveFileRecordRetrievePrevious(btrieve_file_t file, char *record, int recordSize, btrieve_lock_mode_t lockMode);
extern LINKAGE int BtrieveKeySegmentGetACSNumber(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetDescendingSortOrder(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetKeyContinues(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetLength(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetModifiable(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetNullAllSegments(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetNullAnySegment(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetNullValue(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetOffset(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetSegmented(btrieve_key_segment_t keySegment);
extern LINKAGE long long BtrieveKeySegmentGetUniqueValueCount(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveKeySegmentGetUseNumberedACS(btrieve_key_segment_t keySegment);
extern LINKAGE int BtrieveVersionGetClientRevisionNumber(btrieve_version_t version);
extern LINKAGE int BtrieveVersionGetClientVersionNumber(btrieve_version_t version);
extern LINKAGE int BtrieveVersionGetLocalRevisionNumber(btrieve_version_t version);
extern LINKAGE int BtrieveVersionGetLocalVersionNumber(btrieve_version_t version);
extern LINKAGE int BtrieveVersionGetRemoteRevisionNumber(btrieve_version_t version);
extern LINKAGE int BtrieveVersionGetRemoteVersionNumber(btrieve_version_t version);
extern LINKAGE long long BtrieveUnixEpochMicrosecondsToTimestamp(long long microseconds);
extern LINKAGE long long BtrieveTimestampToUnixEpochMicroseconds(long long timestamp);

/// \example btest.c
/// This is an example of file creation, load, access, and deletion.
///

#ifdef __cplusplus
}
#endif

#endif
