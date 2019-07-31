// BDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include <btrieveCpp.h>

static char* btrieveFileName = (char*)"squaresAndSquareRoots.btr";

#define MIN_X 0
#define MAX_X 255

#pragma pack(1)
typedef struct {
	uint8_t x;
	uint16_t xSquared;
	double xSquareRoot;
} record_t;
#pragma pack()

typedef uint8_t _key_t;

static Btrieve::StatusCode ReportExceptionAndReturn ( const char * pachrMessage, const Btrieve::StatusCode pintStatusCode )
{
	printf (
		pachrMessage,
		pintStatusCode,
		Btrieve::StatusCodeToString ( pintStatusCode ) );
	return pintStatusCode;
}	// static Btrieve::StatusCode ReportExceptionAndReturn


static int ShowUsageAndQuit ( const char* pszProgramName , const int pintStatusCode )
{
	printf ("Usage: %s uint8_value, where uint8_value is between %u and %u inclusive\n",
		pszProgramName ,												// Usage: %s uint8_value
		MIN_X,															// where uint8_value is between %u
		MAX_X);															// and %u inclusive
	return pintStatusCode;
}	// static int ShowUsageAndQuit


static Btrieve::StatusCode createFile ( BtrieveClient* btrieveClient )
{
	Btrieve::StatusCode status;
	BtrieveFileAttributes btrieveFileAttributes;

	printf (
		"createFile: SetFixedRecordLength = %i ...",							// Format control string
		( int ) sizeof ( record_t ) );											// SetFixedRecordLength = %i, where the size of record_t is size_t, which must be cast to int to suppress a compiler warning

	// If SetFixedRecordLength() fails.
	if ( ( status = btrieveFileAttributes.SetFixedRecordLength ( sizeof ( record_t ) ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveFileAttributes::SetFixedRecordLength():%d:%s.\n", 
			status);
	}

	printf (
		"done\n            FileCreate %s ...",
		btrieveFileName);

	// If FileCreate() fails.
	if ( ( status = btrieveClient->FileCreate ( &btrieveFileAttributes, btrieveFileName, Btrieve::CREATE_MODE_OVERWRITE ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveClient::FileCreate():%d:%s.\n",
			status );
	}

	printf ( "done\n\ncreateFile done\n\n" );
	return status;
}	// static Btrieve::StatusCode createFile


static Btrieve::StatusCode openFile ( BtrieveClient * btrieveClient, BtrieveFile * btrieveFile )
{
	Btrieve::StatusCode status;

	printf (
		"openFile: Opening file %s ...",
		btrieveFileName );

	// If FileOpen ( ) fails.
	if ( ( status = btrieveClient->FileOpen ( btrieveFile, btrieveFileName, NULL, Btrieve::OPEN_MODE_NORMAL ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveClient::FileOpen():%d:%s.\n",
			status);
	}

	printf ( "done\n\n" );
	return status;
}	// static Btrieve::StatusCode openFile


static Btrieve::StatusCode loadFile ( BtrieveFile* btrieveFile )
{
	int i;
	record_t record;
	int j						= 0;
	Btrieve::StatusCode status	= Btrieve::STATUS_CODE_NO_ERROR;

	printf ( "loadFile: Building lookup table of squares and square roots:\n\n" );

	for ( i = MIN_X;
		  i <= MAX_X;
		  i++, j++ )
	{
		record.x			= ( uint8_t ) i;
		record.xSquared		= ( uint16_t ) ( i * i );
		record.xSquareRoot	= sqrt ( ( double ) i );

		printf (
			"          Record %i: Index = %i, Square of Index = %i, Squre root of Index = %f\n",
			j,																	// Record %i
			record.x,															// Index = %i
			record.xSquared,													// Square of Index = %i
			record.xSquareRoot);												// Squre root of Index = %f

		// If RecordCreate() fails.
		if ( ( status = btrieveFile->RecordCreate ( ( char* ) &record , sizeof ( record ) ) ) != Btrieve::STATUS_CODE_NO_ERROR )
		{
			return ReportExceptionAndReturn (
				"Error: BtrieveFile::RecordCreate():%d:%s.\n",
				status );
		}	// if ( ( status = btrieveFile->RecordCreate ( ( char* ) &record , sizeof ( record ) ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	}	// for ( i = MIN_X; i <= MAX_X; i++, j++ )

	printf (
		"\nloadFile finished loading %i items into lookup table\n\n",
		j );
	return status;
}	// static Btrieve::StatusCode loadFile


static Btrieve::StatusCode closeFile ( BtrieveClient* btrieveClient, BtrieveFile* btrieveFile )
{
	Btrieve::StatusCode status;

	printf ( "closeFile: closing database ... " );

	// If FileClose ( ) fails.
	if ( ( status = btrieveClient->FileClose ( btrieveFile ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveClient::FileClose():%d:%s.\n",
			status );
	}

	printf ( "done\n\n" );
	return status;
}	// static Btrieve::StatusCode closeFile


static Btrieve::StatusCode deleteFile ( BtrieveClient* btrieveClient )
{
	Btrieve::StatusCode status;

	printf ( "deleteFile: deleting the database file ... ");

	// If FileDelete() fails.
	if ( ( status = btrieveClient->FileDelete ( btrieveFileName ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveClient::FileDelete():%d:%s.\n",
			status );
	}

	printf ( "done\n\n" );
	return status;
}	// static Btrieve::StatusCode deleteFile

static Btrieve::StatusCode createIndex ( BtrieveFile* btrieveFile )
{
	Btrieve::StatusCode status;
	BtrieveIndexAttributes btrieveIndexAttributes;
	BtrieveKeySegment btrieveKeySegment;

	printf ( "createIndex: Setting index field ... " );

	// If SetField ( ) fails.
	if ( ( status = btrieveKeySegment.SetField ( 0, 1, Btrieve::DATA_TYPE_UNSIGNED_BINARY ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveKeySegment::SetField():%d:%s.\n",
			status );
	}

	printf ( "done\n             Adding key segment ..." );

	// If AddKeySegment ( ) fails.
	if ( ( status = btrieveIndexAttributes.AddKeySegment ( &btrieveKeySegment ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveIndexAttributes::AddKeySegment():%d:%s.\n",
			status );
	}

	printf ( "done\n             Populating index ..." );

	// If IndexCreate() fails.
	if ( ( status = btrieveFile->IndexCreate ( &btrieveIndexAttributes ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveFile::IndexCreate():%d:%s.\n",
			status );
	}

	printf ( "done\n\ncreateIndex completed its task\n\n" );
	return status;
}	// static Btrieve::StatusCode createIndex


static Btrieve::StatusCode retrieveRecord ( BtrieveFile* btrieveFile, _key_t* key )
{
	Btrieve::StatusCode status = Btrieve::STATUS_CODE_NO_ERROR;
	record_t record;

	// If RecordRetrieve() fails.
	if ( btrieveFile->RecordRetrieve ( Btrieve::COMPARISON_EQUAL, Btrieve::INDEX_1, ( char* ) key, sizeof ( *key ), ( char* ) &record, sizeof ( record ) ) != sizeof ( record ) )
	{
		return ReportExceptionAndReturn (
			"Error: BtrieveFile::RecordRetrieve():%d:%s.\n",
			btrieveFile->GetLastStatusCode ( ) );
	}

	printf (
		"record: Index = %u        Square of Index = %u        Square root of Index = %f\n\n",
		record.x,
		record.xSquared,
		record.xSquareRoot );

	return status;
}	// static Btrieve::StatusCode retrieveRecord


int main ( int argc, char* argv [ ] )
{
	BtrieveFile btrieveFile;
	_key_t key;
	uint64_t integerValue;

	BtrieveClient btrieveClient ( 0x4232, 0) ;
	Btrieve::StatusCode status = Btrieve::STATUS_CODE_UNKNOWN;

	// If the incorrect number of arguments were given.
	if ( argc != 2 )
	{
		return ShowUsageAndQuit (
			argv [ 0 ] ,
			1 );
	}

	integerValue = atoi ( argv [ 1 ] );

	// If integerValue is out of range.
	if ( ( integerValue < MIN_X ) || ( integerValue > MAX_X ) )
	{
		return ShowUsageAndQuit (
			argv [ 0 ] ,
			2 );
	}

	key = ( _key_t ) integerValue;

	// If createFile ( ) fails.
	if ( ( status = createFile ( &btrieveClient ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If openFile ( ) fails.
	if ( ( status = openFile ( &btrieveClient, &btrieveFile ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If loadFile ( ) fails.
	if ( ( status = loadFile ( &btrieveFile ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If createIndex ( ) fails.
	if ( ( status = createIndex ( &btrieveFile ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If retrieveRecord ( ) fails.
	if ( ( status = retrieveRecord ( &btrieveFile, &key ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If closeFile ( ) fails.
	if ( ( status = closeFile ( &btrieveClient, &btrieveFile ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If deleteFile ( ) fails.
	if ( ( status = deleteFile ( &btrieveClient ) ) != Btrieve::STATUS_CODE_NO_ERROR )
	{
		return 3;
	}

	// If there wasn't a failure.
	if ( status == Btrieve::STATUS_CODE_NO_ERROR )
		return 0;
	else
		return 4;
}	// int main