#include "Logger.h"
#include <stdarg.h>

Logger::Logger() 
    : isLogEnabled(false) 
    , logFile(stdout){}

Logger::~Logger() 
{ 
	if (writeLogOnFile) 
		fclose(logFile);
}

void Logger::Log( const char * format, ... )
{
	if (!isLogEnabled)
		return;
		
	static const int buffSz = 2048;
	static char buffer[buffSz];
	va_list args;
	va_start (args, format);
	vsnprintf (buffer,buffSz,format, args);
	va_end (args);

	fprintf(logFile, "%s", buffer);
	fflush(logFile);
}

void Logger::Log(const bool fromArgs, const va_list& arglist, const char* format)
{
	if (!isLogEnabled)
		return ;

    vfprintf(logFile, format, arglist);
}

void Logger::EnableLog() 
{ 
    isLogEnabled = true; 
}

void Logger::SetLoggingToFile(const char* filename)
{
	logFile = fopen(filename, "w");
	writeLogOnFile = true;
}

void Logger::SetLoggingToFile(FILE* _file)
{
	if (_file != logFile) // By default we have stdout
	{
		logFile = _file;
		writeLogOnFile = true;
	}
}
