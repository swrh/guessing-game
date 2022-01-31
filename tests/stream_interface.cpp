#include "gg/stream_interface.hpp"

#include <sstream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(StreamInterface_initializes) {
	std::ostringstream os;
	std::istringstream is;

	gg::StreamInterface si{is, os};
}

BOOST_AUTO_TEST_CASE(StreamInterface_askString_writes_and_reads_stream_correctly) {
	const std::vector<std::string> questions{
		{"What did the fox do?"},
		{"What did the fox say?"},
	};
	const std::vector<std::string> answers{
		{"The quick brown fox jumped over the lazy dog."},
		{"!@%%#!$%!@#$!@$#!@#$%!@#$@qwejklrhq1"},
	};

	std::ostringstream os;
	std::istringstream is;

	for (const std::string &answer : answers) {
		os << answer << '\n';
	}
	is.str(os.str());

	gg::StreamInterface si{is, os};

	BOOST_CHECK_EQUAL(questions.size(), answers.size());

	for (std::size_t i = 0; i < questions.size(); ++i) {
		os.str("");
		BOOST_CHECK_EQUAL(si.askString(questions.at(i)), answers.at(i));
		BOOST_CHECK_EQUAL(os.str(), questions.at(i) + ' ');
	}

	is.str("\n");

	BOOST_CHECK_EQUAL(si.askString("What?"), "");

	BOOST_CHECK_EXCEPTION(si.askString("What?"), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "end of file";
		});
}

BOOST_AUTO_TEST_CASE(StreamInterface_askYesOrNot_writes_and_reads_stream_correctly) {
	const std::vector<std::string> questions{
		{"Yes or not? Answer me quickly."},
		{"Is this the animal you thought about?"},
		{"Does the animal you thought about lives in the sea?"},
		{"Does it bite?"},
		{"Press ENTER for yes."},
	};
	const std::vector<std::tuple<std::string, bool>> answers{
		{"Yes!", true},
		{"No, it wasn't.", false},
		{"yes", true},
		{"no", false},
		{"", true},
	};

	std::ostringstream os;
	std::istringstream is;

	for (const auto &string_bool : answers) {
		os << std::get<std::string>(string_bool) << '\n';
	}
	is.str(os.str());

	gg::StreamInterface si{is, os};

	BOOST_CHECK_EQUAL(questions.size(), answers.size());

	for (std::size_t i = 0; i < questions.size(); ++i) {
		os.str("");
		BOOST_CHECK_EQUAL(si.askYesOrNot(questions.at(i)), std::get<bool>(answers.at(i)));
		BOOST_CHECK_EQUAL(os.str(), questions.at(i) + ' ');
	}

	is.str("\n");

	BOOST_CHECK_EQUAL(si.askYesOrNot("Y/n?"), true);

	BOOST_CHECK_EXCEPTION(si.askYesOrNot("Y/n?"), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "end of file";
		});
}
