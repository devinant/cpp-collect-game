#include <hgeWrapper.h>
#include "Loop.h"
#include <ctime>

#undef main

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);

	srand((size_t)time(0));
	if (HgeWrapper::initiate("TinGame", 1024, 768))
		HgeWrapper::startHge(new Loop());

	// Enables you to see logging.
	std::cin.get();
	return 0;
}