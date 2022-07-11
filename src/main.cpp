#include <iostream>
#include "Controller.h"


int main() try
{
	auto controller = Controller();
	
	controller.run();
	return EXIT_SUCCESS;
}
catch(std::exception &c)
{
	return EXIT_FAILURE;
}
