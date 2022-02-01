#pragma once

#include <memory>
#include <variant>

namespace gg {

class
Node
{
private:
	const std::string name_;
	std::unique_ptr<Node> left_, right_;

public:
	Node(std::string name);

	const std::string &getName() const;

	bool hasLeafs() const;
	void setLeafs(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right);

	std::unique_ptr<Node> &getLeft();
	std::unique_ptr<Node> &getRight();
};

}
