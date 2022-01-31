#pragma once

#include <iostream>

namespace gg {

class
StreamInterface
{
private:
	std::istream &is_;
	std::ostream &os_;

public:
	StreamInterface(std::istream &is, std::ostream &os);
};

}
