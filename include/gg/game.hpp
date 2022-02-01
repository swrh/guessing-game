#pragma once

#include <memory>

#include "gg/node.hpp"
#include "gg/user_interface.hpp"

namespace gg {

class
Game
{
private:
	std::shared_ptr<Node> root_;

public:
	Game();

	void run(UserInterface &ui);
};

}
