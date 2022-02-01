#pragma once

#include <iostream>

#include "gg/stream_interface.hpp"

namespace gg {

class
Game
{
public:
	void run(StreamInterface &ui);
};

}
