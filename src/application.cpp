#include "gg/application.hpp"

#include <iostream>

extern const char *__progname;

using gg::Application;

namespace gg {

Application::Application()
{
}

bool
Application::parseArguments(int argc, const char *argv[])
{
	if (argc != 1) {
		std::cerr << __progname << ": Invalid number of arguments\n";
		return false;
	}

	return true;
}

bool
Application::run()
{
	std::cout << "Hello, world!\n";
	return true;
}

}
