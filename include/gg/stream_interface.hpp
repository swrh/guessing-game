#pragma once

#include <iostream>
#include <string>

namespace gg {

class
StreamInterface
{
private:
	std::istream &is_;
	std::ostream &os_;

	std::string buffer_;

public:
	StreamInterface(std::istream &is, std::ostream &os);

	const std::string &askString(const std::string_view &question);
	bool askYesOrNot(const std::string_view &question);

private:
	void readString();
};

}
