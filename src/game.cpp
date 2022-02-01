#include "gg/game.hpp"

using gg::Game;

namespace gg {

void
Game::run(StreamInterface &ui)
{
	ui.askOk("Think about an animal...");
	ui.askOk("Does the animal that you thought about lives in water? [Y/n]");
	ui.askOk("Is the animal that you thought about a shark? [Y/n]");
	ui.showMessage("I win again!");
}

}
