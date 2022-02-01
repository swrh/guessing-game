#pragma once

#include <memory>
#include <variant>

namespace gg {

class
Node
{
private:
	const std::string name_;
	std::shared_ptr<Node> left_, right_;

public:
	Node(std::string name);

	const std::string &getName() const;

	bool hasLeafs() const;
	void setLeafs(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

	const std::shared_ptr<Node> &getLeft();
	const std::shared_ptr<Node> &getRight();
};

}
