#include <stdexcept>
#include "cst_logger.h"


int main(int argc, char* argv[])
{
	SINGLETON(CstLogger)->SetLogFile("20150517.log", true);

	SINGLETON(CstLogger)->printf(INFO, "Program start");

	
	return 0;
}
