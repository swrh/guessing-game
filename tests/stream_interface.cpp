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
