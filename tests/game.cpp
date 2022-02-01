#include "gg/game.hpp"

#include <boost/algorithm/string/join.hpp>
#include <boost/test/unit_test.hpp>

void
run(gg::Game &game, const std::vector<std::string> &questions, const std::vector<std::string> &answers)
{
	std::ostringstream os;
	std::istringstream is;

	for (const std::string &answer : answers) {
		os << answer << '\n';
	}
	is.str(os.str());
	os.str("");

	gg::StreamInterface ui{is, os};

	game.run(ui);

	std::string data = boost::algorithm::join(questions, "");
	BOOST_REQUIRE_EQUAL(os.str(), data);

	BOOST_CHECK_MESSAGE(!is.eof(), "stdin reached end of file prematurely");
	is.get();
	BOOST_CHECK_MESSAGE(is.eof(), "game did not process all the input data");
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

	std::vector<std::string> questions, answers;

	questions = {
		{"Think about an animal... "},
		{"Does the animal that you thought about lives in water? [Y/n] "},
		{"Is the animal that you thought about a shark? [Y/n] "},
		{"I win again!\n"},
	};
	answers = {
		{""},
		{""},
		{""},
	};

	run(game, questions, answers);
}

BOOST_AUTO_TEST_CASE(Game_run_has_default_monkey) {
	gg::Game game;

	std::vector<std::string> questions, answers;

	questions = {
		{"Think about an animal... "},
		{"Does the animal that you thought about lives in water? [Y/n] "},
		{"Is the animal that you thought about a monkey? [Y/n] "},
		{"I win again!\n"},
	};
	answers = {
		{""},
		{"n"},
		{""},
	};

	run(game, questions, answers);
}

BOOST_AUTO_TEST_CASE(Game_run_learns_new_animals) {
	gg::Game game;

	std::vector<std::string> questions, answers;

	questions = {
		{"Think about an animal... "},
		{"Does the animal that you thought about lives in water? [Y/n] "},
		{"Is the animal that you thought about a monkey? [Y/n] "},
		{"What was the animal that you thought about? "},
		{"A parrot _________ but a monkey does not (Fill it with an animal trait, like 'lives in water'). "},
	};
	answers = {
		{""},
		{"n"},
		{"n"},
		{"parrot"},
		{"flies"},
	};

	run(game, questions, answers);

	questions = {
		{"Think about an animal... "},
		{"Does the animal that you thought about lives in water? [Y/n] "},
		{"Does the animal that you thought about flies? [Y/n] "},
		{"Is the animal that you thought about a parrot? [Y/n] "},
		{"I win again!\n"},
	};
	answers = {
		{""},
		{"n"},
		{"y"},
		{"y"},
	};

	run(game, questions, answers);
}
