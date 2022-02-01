#pragma once

#include <iostream>

#include "gg/user_interface.hpp"

namespace gg {

class
StreamInterface
: public UserInterface
{
private:
	std::istream &is_;
	std::ostream &os_;

	std::string buffer_;

public:
	StreamInterface(std::istream &is, std::ostream &os);

	void askOk(const std::string_view &question) override;
	std::string_view askString(const std::string_view &question) override;
	bool askYesOrNot(const std::string_view &question) override;

	void showMessage(const std::string_view &message) override;

private:
	void readString();
};

}
