#include "BinFormatConcolic.h"
#include <string.h>
#include <assert.h>
#include <cstdlib>

#include "CommonCrossPlatform/Common.h" //MAX_PATH

// The format of the output file for a single execution is the following format:

// [OUTPUT_SIZE : unsigned int |  BinLogEntryHeader with ENTRY_TYPE_CONCOLIC_TEST_BEGIN  | .... test data .... | BinLogEntryHeader with ENTRY_TYPE_CONCOLIC_TEST_END]
// Where test data is composed of multiple serialized SingleTestDetails, one for each branch (test) encountered during execution

bool ConcolicExecutionResult::deserializeFromStream(const char* bufferIn_original, const size_t bufferSize)
{
	const char* bufferIn = bufferIn_original;
	m_tests.clear();

    // Decode first item from bufferIn which must be a BEGIN header with length = number of expected test (NT)
	BinLogEntryHeader* entry = (BinLogEntryHeader*) bufferIn;
	bufferIn += sizeof(BinLogEntryHeader);
	if (entry->entryType != ENTRY_TYPE_CONCOLIC_TEST_BEGIN)
	{
		assert(false);
		return false;
	}
	const int NT = entry->entryLength;
	m_tests.resize(NT);

    // Decode tests one by one (x NT)
	for (int i = 0; i < NT; i++)
	{		
		// Read the header from buffer and advance buffer
		SingleTestDetails& testData = m_tests[i];

#if 0
		// HACK
		if (i == 0)
		{
			BinLogEntry *blEntry = (BinLogEntry *)bufferIn;
			if (blEntry->header.entryType != Z3_SYMBOLIC_TYPE_JCC)
			{
				assert(false && "Only jcc is currently supported for concolic testing..." );
			}

			const int dataSize = blEntry->header.entryLength;
			bufferIn += sizeof(blEntry->header);
			bufferIn += dataSize;
		}
		else 
#endif
		{
			const int size = BinFormat::ReadZ3SymbolicJumpCC(bufferIn, testData);
			bufferIn += size;
		}
	}

    // Decode last item from bufferIn which must be an END header - as a sanity check
	entry = (BinLogEntryHeader*) bufferIn;
	bufferIn += sizeof(BinLogEntryHeader);
	if (entry->entryType != ENTRY_TYPE_CONCOLIC_TEST_END)
	{
		assert(false);
		return false;
	}

	// Final Check - dimension
	const size_t readSize = (size_t)(bufferIn - bufferIn_original);
	if (readSize != bufferSize)
	{
		assert(false);
		return false;
	}

	return true;
}

void BinFormatConcolic::WriteStartHeader(const bool flush)
{
	BinLogEntryHeader entry;
	entry.entryType = ENTRY_TYPE_CONCOLIC_TEST_BEGIN;
	entry.entryLength = 0;

	WriteData((unsigned char*)&entry, sizeof(entry));
	if (flush)
	{
		if (!noOutputWrite)
			log->Flush();
	}
}

void BinFormatConcolic::WriteEndHeader(const bool flush)
{
	BinLogEntryHeader entry;
	entry.entryType = ENTRY_TYPE_CONCOLIC_TEST_END;
	entry.entryLength = 0;

	WriteData((unsigned char*)&entry, sizeof(entry));
	if (flush)
	{
		if (!noOutputWrite)
			log->Flush();
	}
}

void BinFormatConcolic::OnExecutionBegin(const char* testName)
{
	m_testCounter = 0;
	BinFormat::OnExecutionBegin(testName);
	WriteStartHeader(true);
}

void BinFormatConcolic::OnExecutionEnd()
{
	// Write the test counter firs
	if (bufferHeaderPos < sizeof(BinLogEntryHeader))
	{
		assert(false && "Failed the sanity check. We didn't even wrote the buffer");
	}

	BinLogEntryHeader* beginHeader = (BinLogEntryHeader*) &bufferEntries[CONTENT_OFFSET];
	assert(beginHeader->entryType == ENTRY_TYPE_CONCOLIC_TEST_BEGIN && "Incorrect first entry type");
	beginHeader->entryLength = m_testCounter;

	WriteEndHeader(true);
	BinFormat::OnExecutionEnd();


	// This is just a debug test to see if I write the binary output log in trace.simple.out, can I read it correctly ?
#if 0
	FILE *f = fopen("trace.simple.out", "rb");
	fseek(f, 0, SEEK_END);
	const size_t fSize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* fileContent = new char[fSize];
	fread(fileContent, 1, fSize, f);
	fclose(f);

	ConcolicExecutionResult execResults;
	const bool res = execResults.deserializeFromStream(fileContent + sizeof(fSize), fSize-sizeof(fSize));
	assert(res && "couldn't read correctly from stream");

	delete []fileContent;

#endif
}

bool BinFormatConcolic::WriteZ3SymbolicJumpCC(const SingleTestDetails& testDetails)
{
	m_testCounter++;
	return BinFormat::WriteZ3SymbolicJumpCC(testDetails);
}

