#include "gg/application.hpp"

#include <iostream>

#include "gg/game.hpp"
#include "gg/stream_interface.hpp"

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
	Game game;

	StreamInterface ui{std::cin, std::cout};

	for (;;) {
		game.run(ui);
	}
}

}
