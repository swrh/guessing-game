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

bool
StreamInterface::askYesOrNot(const std::string_view &question)
{
	os_ << question << ' ' << std::flush;

	do {
		readString();

		if (buffer_.size() == 0) {
			return true;
		}

		const char c = buffer_[0];
		if (c == 'n' || c == 'N') {
			return false;
		} else if (c == 'y' || c == 'Y') {
			return true;
		}
	} while (true);

	throw std::runtime_error("internal error");
}

void
StreamInterface::readString()
{
	if (is_.eof()) {
		throw std::runtime_error("end of file");
	}

	std::getline(is_, buffer_);

	if (buffer_.size() == 0 && is_.eof()) {
		throw std::runtime_error("end of file");
	}
}

}
