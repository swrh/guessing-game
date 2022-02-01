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
	std::shared_ptr<Node> trait, animal = root_;

	do {
		trait = std::move(animal);
		answerYes = ui.askYesOrNot("Does the animal that you thought about " + trait->getName() + "?");
		if (answerYes) {
			animal = trait->getLeft();
		} else {
			animal = trait->getRight();
		}
	} while (animal->hasLeafs());

	if (ui.askYesOrNot("Is the animal that you thought about a " + animal->getName() + "?")) {
		ui.showMessage("I win again!");
		return;
	}

	std::string_view response;

	response = ui.askString("What was the animal that you thought about?");
	auto newAnimal = std::make_shared<Node>(std::string{response});

	response = ui.askString("A " + newAnimal->getName() + " _________ but a " + animal->getName() + " does not (Fill it with an animal trait, like '" + root_->getName() + "').");
	auto newTrait = std::make_shared<Node>(std::string{response});

	newTrait->setLeafs(std::move(newAnimal), std::move(animal));

	if (answerYes) {
		trait->setLeft(std::move(newTrait));
	} else {
		trait->setRight(std::move(newTrait));
	}
}

}
