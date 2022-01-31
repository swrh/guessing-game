#include <stdlib.h>

#include "gg/application.hpp"

int
main(int argc, const char *argv[])
{
	gg::Application app;

	if (!app.parseArguments(argc, argv)) {
		return EXIT_FAILURE;
	}

	if (!app.run()) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
