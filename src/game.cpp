#include "gg/game.hpp"

using gg::Game;

namespace gg {

void
Game::run(UserInterface &ui)
{
	ui.askOk("Think about an animal...");
	ui.askYesOrNot("Does the animal that you thought about lives in water?");
	ui.askYesOrNot("Is the animal that you thought about a shark?");
	ui.showMessage("I win again!");
}

}
