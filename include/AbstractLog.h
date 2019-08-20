#ifndef _ABSTRACT_LOG_H_
#define _ABSTRACT_LOG_H_

#include "revtracer/revtracer.h"		//ExecutionRegs
#include "CommonCrossPlatform/Common.h" //MAX_PATH

class AbstractLog {
private :
	bool isLogOpen;

protected :
	virtual bool _OpenLog() = 0;
	virtual bool _CloseLog() = 0;

	bool OpenLog();
	bool CloseLog();
	bool IsLogOpen();

public :
	AbstractLog();
	virtual bool WriteBytes(unsigned char *buffer, unsigned int size) = 0;
	virtual bool Flush() = 0;
	virtual ~AbstractLog() {}
};

#define MAX_VARCOUNT	1024
#define FLAG_LEN	7
#define INPUT_ADDR	0x01
#define OUTPUT_ADDR		0x02
#define DISP8	0x01
#define DISP	0x04

#define MAX_LINE_SIZE 8096

struct BasicBlockPointer {
	unsigned int offset;
	char modName[MAX_PATH];
};

struct BasicBlockMeta {
	struct BasicBlockPointer bbp;
	unsigned int cost;
	unsigned int jumpType;
	unsigned int jumpInstruction;
	unsigned int esp;
	unsigned int nInstructions;
	unsigned int bbpNextSize;
	struct BasicBlockPointer *bbpNext;
};

struct SymbolicAddress {
	unsigned int symbolicBase;
	unsigned int scale;
	unsigned int symbolicIndex;
	unsigned int composedSymbolicAddress;
	unsigned char dispType;
	unsigned displacement;
	unsigned char inputOutput;
	struct BasicBlockPointer bbp;
};

struct SymbolicFlag {
	unsigned int testFlags;
	unsigned int symbolicCond;
	unsigned int symbolicFlags[FLAG_LEN];
};

struct SymbolicAst {
	const char *address;
	unsigned int size;
};

#include <unordered_set>

// Details about a test in the source code.
// It is partially filled before a jump is executed, and fully filled after.
struct SingleTestDetails
{
	//static const int MAX_Z3STR_SIZE = 8096;
	SymbolicAst ast;//[MAX_Z3STR_SIZE];  Pointer to the Z3 AST defining the condition
	SymbolicFlag flags;	// These are the flags involved in the jump test. E.g. JA will test CF and ZF 


	DWORD parentBlock = 0;	//Block address where  the jump command happens 
	char parentModuleName[MAX_PATH] = {'\0'};
	DWORD blockOptionTaken = 0;	//BLock address where it should go if jump is taken
	char takenOptionModuleName[MAX_PATH] = {'\0'};
	DWORD blockOptionNotTaken = 0; // BLock address where it should go if jump is no taken
	char notTakenOptionModuleName[MAX_PATH] = {'\0'};
	std::unordered_set<unsigned int> indicesOfInputBytesUsed; // Indices of input bytes used by this test 
	bool pending = false; // True if a Jump instruction found and we wait to know if it was taken or not
	bool taken = false;
	bool isPending() const { return pending;}
	void setPending(const bool _pending) { pending = _pending;}

	void Reset()
	{
		ast.address = nullptr;
		ast.size = 0;
		parentBlock = blockOptionTaken = blockOptionNotTaken = 0;
		parentModuleName[0] = takenOptionModuleName[0] = notTakenOptionModuleName[0] = '\0';
		pending = false;
		taken = false;
		indicesOfInputBytesUsed.clear();
	}


	// Serialize and deserializa this data structure to a give buffer. Both read/written sizes
	int serialize(char* outputBuffer, const size_t maxOutputSize) const;
	int deserialize(const char* inputBuffer, const size_t inputBufferSize);
};

class AbstractFormat {
protected :
	AbstractLog *log;

public :
	AbstractFormat(AbstractLog *l) {
		log = l;
	}
	virtual ~AbstractFormat() {}

	virtual bool WriteTestName(
		const char *testName
	) = 0;

	virtual bool WriteRegisters(rev::ExecutionRegs &regs) = 0;

	virtual bool WriteBasicBlock(struct BasicBlockMeta bbm) = 0;

	// Maybe these need a better name ?
	virtual void OnExecutionEnd() {}
	virtual void OnExecutionBegin(const char* testName) { WriteTestName(testName); }

	virtual bool WriteInputUsage(unsigned int offset) = 0;
	virtual bool WriteTaintedIndexPayload(unsigned int dest,
			unsigned int source, unsigned int size) = 0;
	virtual bool WriteTaintedIndexExtract(unsigned int dest,
			unsigned int source, unsigned int lsb, unsigned int size) = 0;
	virtual bool WriteTaintedIndexConcat(unsigned int dest,
			unsigned int operands[2]) = 0;
	virtual bool WriteTaintedIndexExecute(unsigned int dest, BasicBlockPointer bbp,
			unsigned int flags, unsigned int depsSize,
			unsigned int *deps) = 0;
	virtual bool WriteTaintedIndexConst(unsigned int dest,
			unsigned int value, unsigned int size) = 0;
	virtual bool WriteZ3SymbolicAddress(unsigned int dest,
			SymbolicAddress symbolicAddress, SymbolicAst ast) = 0;
	virtual bool WriteZ3SymbolicJumpCC(const SingleTestDetails& testDetails) = 0;

};

/*class AbstractLog {
private :
	bool isLogOpen;
protected :
	char logName[PATH_LEN];
	virtual bool _OpenLog() = 0;
	virtual bool _CloseLog() = 0;

	bool OpenLog();
	bool CloseLog();
	
	virtual bool _WriteTestName(
		const char *testName
	) = 0;

	virtual bool _WriteBasicBlock(
		const char *module,
		unsigned int offset,
		unsigned int cost,
		unsigned int jumpType
	) = 0;
public :
	virtual bool SetLogFile(
		const char *log
	);

	virtual void FlushLog() = 0;

	bool WriteTestName(
		const char *testName
	);

	bool WriteBasicBlock(
		const char *module,
		unsigned int offset,
		unsigned int cost,
		unsigned int jumpType
	);

	virtual bool WriteInputUsage(
		unsigned int offset
	) = 0;

	virtual bool WriteTestResult(
	) = 0;
};*/

#endif
