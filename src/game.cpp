#include "gg/game.hpp"

#include <string>

using gg::Game;

namespace gg {

void
Game::run(UserInterface &ui)
{
	ui.askOk("Think about an animal...");

	std::string animal;
	bool yes;

	yes = ui.askYesOrNot("Does the animal that you thought about lives in water?");

	if (yes) {
		animal = "shark";
	} else {
		animal = "monkey";
	}

	ui.askYesOrNot("Is the animal that you thought about a " + animal + "?");

	ui.showMessage("I win again!");
}

}
