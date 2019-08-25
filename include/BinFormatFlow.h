#ifndef _BINFORMATFLOW_H_
#define _BINFORMATFLOW_H_

#include "BinFormat.h"

class BinFormatFlow : public AbstractFormat {
private :
	char lastModule[MAX_PATH];
	char lastNextModule[MAX_PATH];

  // Variables below are used for buffering mode. 
	// The reason i need buffering is that communication to the tracer.simple process are done by pipes and we can't seek in a pipe.
	// What I do is to write all entries in the buffer at runtime, then when executon ends write data to pipe(stdout) [number of bytes used + buffer]
	bool bufferingEntries;										// True if buffering entries
	unsigned char* bufferEntries;								// If this is created with shouldBufferEntries = true => we'll buffer all entries and send them at once
	static const int MAX_ENTRIES_BUFFER_SIZE = 1024*1024*2;   	// Preallocated buffer used when buffering entries. If exceeded an exception occurs. TODO: recreate buffer when exceeded max size ?
	int bufferHeaderPos;

  // Writes data either to the internal buffer or to the log file depending on the type
	void WriteData(unsigned char* data, const unsigned int size, const bool ignoreInBufferedMode = false);
	bool WriteBBModule(const char *moduleName, unsigned short type);
	bool WriteAst(SymbolicAst ast);
public :
	BinFormat(AbstractLog *l, bool shouldBufferEntries=false);
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

	// Callbacks to know about execution status and update internal data structures	
	void OnExecutionEnd() override;
	void OnExecutionBegin(const char* testName) override; // testName optional when running in buffered / flow mode (you can set it as nullptr)
};

#endif

