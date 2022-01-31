#pragma once

namespace gg {

class
Application
{
public:
	Application();

	bool parseArguments(int argc, const char *argv[]);

	bool run();
};

}
