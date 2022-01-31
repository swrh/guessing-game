#include <gg/stream_interface.hpp>

using gg::StreamInterface;

namespace gg {

StreamInterface::StreamInterface(std::istream &is, std::ostream &os)
	: is_{is}
	, os_{os}
{
}

}
