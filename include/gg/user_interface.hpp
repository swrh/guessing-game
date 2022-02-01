#pragma once

#include <string_view>

namespace gg {

class
UserInterface
{
public:
	virtual ~UserInterface();

	virtual void askOk(const std::string_view &question) = 0;
	virtual std::string_view askString(const std::string_view &question) = 0;
	virtual bool askYesOrNot(const std::string_view &question) = 0;

	virtual void showMessage(const std::string_view &message) = 0;
};

}
