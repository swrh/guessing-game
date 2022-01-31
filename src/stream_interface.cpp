#include <gg/stream_interface.hpp>

using gg::StreamInterface;

namespace gg {

StreamInterface::StreamInterface(std::istream &is, std::ostream &os)
	: is_{is}
	, os_{os}
{
}

const std::string &
StreamInterface::askString(const std::string_view &question)
{
	os_ << question << ' ' << std::flush;
	readString();
	return buffer_;
}

void
StreamInterface::readString()
{
	std::getline(is_, buffer_);
}

}
