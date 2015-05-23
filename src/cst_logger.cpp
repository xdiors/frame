#include <stdarg.h>
#include "cst_logger.h"


using namespace std;

char* CstLogger::mLevelStr[NUMLEVEL] = {"INFO ", "WARN ", "ERROR", "FATAL", "DEBUG"};

void CstLogger::SetLogFile(const char* fileName)
{
	mOut.open(fileName, std::ios_base::out | std::ios_base::app);
}

void CstLogger::SetDebug(bool bDebug)
{
	mDebug = bDebug;
}

void CstLogger::Write(LOGLEVEL level, const char* format, ...)
{
	if( (!mDebug) && (DEBUG == level) )
	{
		return;
	}

	mOut << __DATE__ << " " << __TIME__ << " " << mLevelStr[level] << " : " ;

	va_list argPtr;
	va_start(argPtr, format);

	for(const char* p = format; *p; ++p)
	{
		if(*p != '%')
		{
			mOut << *p;
			continue;
		}

		++p;
		switch(*p)
		{
			case 'd':
			mOut << va_arg(argPtr, int);
			break;
			case 'f':
			mOut << va_arg(argPtr, double);
			break;
			case 's':
			mOut << va_arg(argPtr, char*);
			break;
			default:
			mOut << *p;
			break;
		}
	}


	va_end(argPtr);

	mOut << endl;
}
