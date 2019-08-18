#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>

class Logger
{
public:
	Logger();
	~Logger();

	void Log( const char * format, ... );
	void Log(const bool fromArgs, const va_list& arglist, const char* format);
	void EnableLog();
	void SetLoggingToFile(const char* filename);
	void SetLoggingToFile(FILE* _file);

private:	
	bool writeLogOnFile;
	bool isLogEnabled;
	FILE* logFile; 
};



#endif
