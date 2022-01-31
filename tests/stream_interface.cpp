#include "gg/stream_interface.hpp"

#include <sstream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(stream_initializes) {
	std::ostringstream os;
	std::istringstream is;

	gg::StreamInterface si{is, os};
}
