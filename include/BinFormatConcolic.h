#ifndef _BINFORMATFLOW_H_
#define _BINFORMATFLOW_H_

#include "BinFormat.h"
#include <vector>

// This holds the test (branches) resulted from an execution
class ConcolicExecutionResult
{
    public:
    std::vector<SingleTestDetails> m_tests;

    // This takes a buffer and size and deserializes all test inside m_tests
    bool deserializeFromStream(const char* bufferIn, const size_t bufferSize);
};


class BinFormatConcolic : public BinFormat {

public:
	BinFormatConcolic(AbstractLog *l, bool shouldBufferEntries=false)
		: BinFormat(l, shouldBufferEntries){}
	~BinFormatConcolic(){}

	// Callbacks to know about execution status and update internal data structures	
	void OnExecutionEnd() override;
	void OnExecutionBegin(const char* testName) override; // testName optional when running in buffered / flow mode (you can set it as nullptr)

	bool WriteZ3SymbolicJumpCC(const SingleTestDetails& testDetails) override;

protected:
	void WriteStartHeader(const bool flush);
	void WriteEndHeader(const bool flush);

	int m_testCounter = 0; // Counts how many tests (branches) are encountered during execution
};

#endif

