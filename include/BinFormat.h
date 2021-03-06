#ifndef _BINFORMAT_H_
#define _BINFORMAT_H_

#include <stdio.h>

#include "AbstractLog.h"
#include "CommonCrossPlatform/Common.h" //MAX_PATH

#define ENTRY_TYPE_TEST_NAME		0x0010
#define ENTRY_TYPE_EXECUTION_REGS	0x0020
#define ENTRY_TYPE_BB_MODULE		0x00B0
#define ENTRY_TYPE_BB_NEXT_MODULE	0x00C0
#define ENTRY_TYPE_BB_OFFSET		0x00BB
#define ENTRY_TYPE_INPUT_USAGE		0x00AA
#define ENTRY_TYPE_BB_NEXT_OFFSET	0x00A0
#define ENTRY_TYPE_TAINTED_INDEX	0x00D0
#define ENTRY_TYPE_Z3_SYMBOLIC  	0x00E0
#define ENTRY_TYPE_Z3_AST			0x00F0
#define ENTRY_TYPE_Z3_MODULE		0x00FF
#define ENTRY_TYPE_CONCOLIC_TEST_BEGIN 	0x00D1
#define ENTRY_TYPE_CONCOLIC_TEST_END	0x00D2

#define TAINTED_INDEX_TYPE_CONCAT	0x0001
#define TAINTED_INDEX_TYPE_EXTRACT	0x0020
#define TAINTED_INDEX_TYPE_PAYLOAD	0x0100
#define TAINTED_INDEX_TYPE_EXECUTE	0x1000
#define TAINTED_INDEX_TYPE_CONST	0x0030
#define TAINTED_INDEX_TYPE_MODULE	0x00AA

#define Z3_SYMBOLIC_TYPE_ADDRESS	0x0001
#define Z3_SYMBOLIC_TYPE_JCC		0x0002

#define MAX_DEPS	20

struct BinLogEntryHeader {
	unsigned short entryType;
	unsigned int entryLength;
};

struct TaintedIndexHeader {
	unsigned short entryType;
	unsigned short entryLength;
	unsigned int destIndex;
};

struct Z3SymbolicHeader {
	unsigned short entryType;
	unsigned short entryLength;
};

struct BinLogEntry {
	BinLogEntryHeader header;

	union Data {
		struct AsBBOffset {
			// encodes the module name length (including trailing \0)
			// a value of 0 means the current basic block resides in the same module as the previous
			unsigned int offset;
			unsigned short cost;
			unsigned short jumpType;
			unsigned short jumpInstruction;
			unsigned short nInstructions;
			unsigned int esp;
		} asBBOffset;

		struct AsExecutionRegisters {
			unsigned int edi;
			unsigned int esi;
			unsigned int ebp;
			unsigned int esp;

			unsigned int ebx;
			unsigned int edx;
			unsigned int ecx;
			unsigned int eax;
			unsigned int eflags;
		} asExecutionRegisters;

		struct AsBBNextOffset {
			unsigned int offset;
		} asBBNextOffset;

		struct AsInputUsage {
			unsigned int offset;
		} asInputUsage;

		struct AsTaintedIndex {
			TaintedIndexHeader header;
			union Source {
				// source is original input index
				struct TaintedIndexPayload {
					unsigned int payloadIndex;
					unsigned int size;
				} taintedIndexPayload;

				// operation implies bits extraction
				struct TaintedIndexExtract {
					unsigned int index;
					unsigned int lsb;
					unsigned int size;
				} taintedIndexExtract;

				// operation implies data concatenation
				struct TaintedIndexConcat {
					unsigned int operands[2];
				} taintedIndexConcat;

				// index changes after instruction execution
				// flag indices are first stored in deps
				// each flag bit is set in flags if it is tainted
				// after flags, deps contains data indices
				struct TaintedIndexExecute {
					unsigned int offset;
					unsigned int flags;
					unsigned int depsSize;
					unsigned int deps[MAX_DEPS];
				} taintedIndexExecute;

				// generation of a constant
				// size specified in bits
				struct TaintedIndexConst {
					unsigned int value;
					unsigned int size;
				} taintedIndexConst;
			} source;
		} asTaintedIndex;

		struct AsZ3Symbolic {
			Z3SymbolicHeader header;
			union Source {
				struct Z3SymbolicAddress {
					unsigned int offset;
					unsigned int symbolicBase;
					unsigned int scale;
					unsigned int symbolicIndex;
					// can be stored as BYTE or as DWORD
					unsigned int displacement;
					unsigned int composedAddress;
					bool input;
					bool output;
				} z3SymbolicAddress;

				struct Z3SymbolicJumpCC {
					unsigned int testFlags;
					unsigned int symbolicCond;
					unsigned int symbolicFlags[FLAG_LEN];
				} z3SymbolicJumpCC;
			} source;
		} asZ3Symbolic;

	} data;
};

/*class BinFormat : public AbstractFormat {
private:
	FILE *fLog;
	char lastModule[MAX_PATH];
protected :
	bool _OpenLog();
	bool _CloseLog();
	bool _WriteTestName(const char *testName);
	bool _WriteBasicBlock(const char *module, unsigned int offset, unsigned int cost, unsigned int jumpType);
public :
	virtual void FlushLog();
};*/

class BinFormat : public AbstractFormat {
protected :
	char lastModule[MAX_PATH];
	char lastNextModule[MAX_PATH];

  // Variables below are used for buffering mode. 
	// The reason i need buffering is that communication to the tracer.simple process are done by pipes and we can't seek in a pipe.
	// What I do is to write all entries in the buffer at runtime, then when executon ends write data to pipe(stdout) [number of bytes used + buffer]
	bool bufferingEntries;										// True if buffering entries
	unsigned char* bufferEntries;								// If this is created with shouldBufferEntries = true => we'll buffer all entries and send them at once
	static const int MAX_ENTRIES_BUFFER_SIZE = 1024*1024*2;   	// Preallocated buffer used when buffering entries. If exceeded an exception occurs. TODO: recreate buffer when exceeded max size ?
	int bufferHeaderPos;
	bool noOutputWrite;											// Use this with true if you want to manage yourself the buffered output (e.g. send it over a socket)

	static const int CONTENT_OFFSET = sizeof(int);

  // Writes data either to the internal buffer or to the log file depending on the type
	void WriteData(unsigned char* data, const unsigned int size, const bool ignoreInBufferedMode = false);
	bool WriteBBModule(const char *moduleName, unsigned short type);
	bool WriteAst(SymbolicAst ast);
public :
	BinFormat(AbstractLog *l, bool shouldBufferEntries=false, bool noOutputWrite=false);
	~BinFormat();

	virtual bool WriteTestName(
		const char *testName
	);

	virtual bool WriteRegisters(rev::ExecutionRegs &regs);

	virtual bool WriteBasicBlock(struct BasicBlockMeta bbm);

	virtual bool WriteInputUsage(unsigned int offset);

	virtual bool WriteTaintedIndexPayload(unsigned int dest,
			unsigned int source, unsigned int size);
	virtual bool WriteTaintedIndexExtract(unsigned int dest,
			unsigned int source, unsigned int lsb, unsigned int size);
	virtual bool WriteTaintedIndexConcat(unsigned int dest,
			unsigned int operands[2]);
	virtual bool WriteTaintedIndexExecute(unsigned int dest,
			BasicBlockPointer bbp, unsigned int flags, unsigned int depsSize,
			unsigned int *deps);
	virtual bool WriteTaintedIndexConst(unsigned int dest,
			unsigned int value, unsigned int size);
	virtual bool WriteZ3SymbolicAddress(unsigned int dest,
			SymbolicAddress symbolicAddress, SymbolicAst ast);
	virtual bool WriteZ3SymbolicJumpCC(const SingleTestDetails& testDetails);

	// Reads from buffer, puts the read data in outTestDetails and returns the size of data read to help client advance read buffer
	static int ReadZ3SymbolicJumpCC(const char* bufferToReadFrom, SingleTestDetails& outTestDetails);

	// Callbacks to know about execution status and update internal data structures	
	void OnExecutionEnd() override;
	void OnExecutionBegin(const char* testName) override; // testName optional when running in buffered / flow mode (you can set it as nullptr)

	virtual int GetBufferedSize() override;
	virtual char* GetBufferedContent() override;
	virtual int FinalizeBufferedContent() override;
	virtual void sendBufferedContentThroughSocket() override;
};

#endif

