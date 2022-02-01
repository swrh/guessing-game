#include "gg/game.hpp"

#include <variant>

#include <boost/algorithm/string/join.hpp>
#include <boost/test/unit_test.hpp>

#include "gg/stream_interface.hpp"

typedef std::variant<const char *, bool, nullptr_t> Answer;

struct
MockInterface
: gg::UserInterface
{
	const std::vector<Answer> &answers_;
	std::vector<Answer>::const_iterator answersIt_;
	std::vector<std::string> messages_;

	MockInterface(const std::vector<Answer> &answers)
		: answers_{answers}
		, answersIt_{answers_.begin()}
	{
	}

	void
	askOk(const std::string_view &s) override
	{
		messages_.push_back(std::string{s});
		getAnswer<nullptr_t>();
	}

	std::string_view
	askString(const std::string_view &s) override
	{
		messages_.push_back(std::string{s});
		return getAnswer<const char *>();
	}

	bool
	askYesOrNot(const std::string_view &s) override
	{
		messages_.push_back(std::string{s});
		return getAnswer<bool>();
	}

	void
	showMessage(const std::string_view &s) override
	{
		messages_.push_back(std::string{s});
	}

private:
	template <typename T>
	const T &
	getAnswer()
	{
		if (answersIt_ == answers_.end()) {
			throw std::runtime_error("end of answers");
		}
		const T *ptr = std::get_if<T>(&*answersIt_);
		if (!ptr) {
			throw std::runtime_error("answer has different type");
		}
		++answersIt_;
		return *ptr;
	}
};

void
run(gg::Game &game, const std::vector<std::string> &questions, const std::vector<Answer> &answers)
{
	MockInterface ui{answers};

	game.run(ui);

	BOOST_REQUIRE_EQUAL_COLLECTIONS(ui.messages_.begin(), ui.messages_.end(),
			questions.begin(), questions.end());

	BOOST_REQUIRE_MESSAGE(ui.answersIt_ == answers.end(), "game.run() did not process all answers");
}

void
pushBack(std::vector<std::string> &questions, std::vector<Answer> &answers, std::string question, const Answer &answer)
{
	questions.push_back(std::move(question));
	answers.push_back(answer);
}

BOOST_AUTO_TEST_CASE(Game_run_throws_exception_on_input_end_of_file) {
	gg::Game game;

	std::ostringstream os;
	std::istringstream is;

	gg::StreamInterface ui{is, os};

	BOOST_CHECK_EXCEPTION(game.run(ui), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "end of file";
		});
}

BOOST_AUTO_TEST_CASE(Game_run_has_default_shark) {
	gg::Game game;

	std::vector<std::string> questions;
	std::vector<Answer> answers;

	questions = {
		{"Think about an animal..."},
		{"Does the animal that you thought about lives in water?"},
		{"Is the animal that you thought about a shark?"},
		{"I win again!"},
	};
	answers = {
		{nullptr},
		{true},
		{true},
	};

	run(game, questions, answers);
}

BOOST_AUTO_TEST_CASE(Game_run_has_default_monkey) {
	gg::Game game;

	std::vector<std::string> questions;
	std::vector<Answer> answers;

	questions = {
		{"Think about an animal..."},
		{"Does the animal that you thought about lives in water?"},
		{"Is the animal that you thought about a monkey?"},
		{"I win again!"},
	};
	answers = {
		{nullptr},
		{false},
		{true},
	};

	run(game, questions, answers);
}

BOOST_AUTO_TEST_CASE(Game_run_learns_new_animals) {
	gg::Game game;

	std::vector<std::string> questions;
	std::vector<Answer> answers;

	// Create parrot
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", false);
	pushBack(questions, answers, "Is the animal that you thought about a monkey?", false);
	pushBack(questions, answers, "What was the animal that you thought about?", "parrot");
	pushBack(questions, answers, "A parrot _________ but a monkey does not (Fill it with an animal trait, like 'lives in water').", "flies");
	run(game, questions, answers);

	// Test parrot
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", false);
	pushBack(questions, answers, "Does the animal that you thought about flies?", true);
	pushBack(questions, answers, "Is the animal that you thought about a parrot?", true);
	questions.push_back("I win again!");
	run(game, questions, answers);

	// Create whale
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", true);
	pushBack(questions, answers, "Is the animal that you thought about a shark?", false);
	pushBack(questions, answers, "What was the animal that you thought about?", "whale");
	pushBack(questions, answers, "A whale _________ but a shark does not (Fill it with an animal trait, like 'lives in water').", "blows");
	run(game, questions, answers);

	// Test whale
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", true);
	pushBack(questions, answers, "Does the animal that you thought about blows?", true);
	pushBack(questions, answers, "Is the animal that you thought about a whale?", true);
	questions.push_back("I win again!");
	run(game, questions, answers);

	// Test shark
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", true);
	pushBack(questions, answers, "Does the animal that you thought about blows?", false);
	pushBack(questions, answers, "Is the animal that you thought about a shark?", true);
	questions.push_back("I win again!");
	run(game, questions, answers);

	// Test monkey
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", false);
	pushBack(questions, answers, "Does the animal that you thought about flies?", false);
	pushBack(questions, answers, "Is the animal that you thought about a monkey?", true);
	questions.push_back("I win again!");
	run(game, questions, answers);

	// Test parrot
	questions.clear();
	answers.clear();
	pushBack(questions, answers, "Think about an animal...", nullptr);
	pushBack(questions, answers, "Does the animal that you thought about lives in water?", false);
	pushBack(questions, answers, "Does the animal that you thought about flies?", true);
	pushBack(questions, answers, "Is the animal that you thought about a parrot?", true);
	questions.push_back("I win again!");
	run(game, questions, answers);
}
