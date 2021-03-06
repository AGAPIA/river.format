#include "FileLog.h"
#include <string.h>

bool FileLog::_OpenLog() {
	if (strcmp(logName, "stdout") == 0)
		fLog = stdout;
	else
		fLog = fopen(logName, "wb");

	return fLog != nullptr;
}

bool FileLog::_CloseLog() {
	if (nullptr == fLog) {
		return false;
	}

	fclose(fLog);
	fLog = nullptr;
	return true;
}

bool FileLog::SetLogFileName(const char *name) {
	if (IsLogOpen()) {
		CloseLog();
	}

	strcpy(logName, (char *)name);
	return true;
}

bool FileLog::SetExternalFile(FILE* externalFile)
{
	fLog = externalFile;
	isExternalFileSet = true;

	return true;
}

bool FileLog::WriteBytes(unsigned char *buffer, unsigned int size) {
	if (!IsLogOpen()) {
		if (!OpenLog()) {
			return false;
		}
	}

	fwrite(buffer, size, 1, fLog);
	return true;
}

bool FileLog::Flush() {
	fflush(fLog);
	return true;
}
