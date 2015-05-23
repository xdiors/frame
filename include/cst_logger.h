#ifndef CST_LOGGER_H
#define CST_LOGGER_H

#include <fstream>
#include "cst_singleton.h"

enum LOGLEVEL {INFO, WARN, ERROR, FATAL, DEBUG, NUMLEVEL};

class CstLogger
{
public:
	void SetLogFile(const char* fileName);
	void SetDebug(bool bDebug);
	void Write(LOGLEVEL level, const char* format, ...);
	
private:
	bool mDebug;
	std::ofstream mOut;	
	static char* mLevelStr[NUMLEVEL];

SET_SINGLETON(CstLogger);
};


#endif