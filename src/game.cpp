#include "gg/game.hpp"

#include <string>

using gg::Game;

namespace gg {

Game::Game()
{
	root_ = std::make_shared<Node>("lives in water");
	root_->setLeafs(std::make_shared<Node>("shark"), std::make_shared<Node>("monkey"));
}

void
Game::run(UserInterface &ui)
{
	ui.askOk("Think about an animal...");

	bool answerYes;
	std::shared_ptr<Node> parent, child = root_;

	do {
		parent = child;
		answerYes = ui.askYesOrNot("Does the animal that you thought about " + parent->getName() + "?");
		if (answerYes) {
			child = parent->getLeft();
		} else {
			child = parent->getRight();
		}
	} while (child->hasLeafs());

	if (ui.askYesOrNot("Is the animal that you thought about a " + child->getName() + "?")) {
		ui.showMessage("I win again!");
		return;
	}
}

}
