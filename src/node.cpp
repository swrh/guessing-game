#include <gg/node.hpp>

using gg::Node;

namespace gg {

Node::Node(std::string name)
	: name_{std::move(name)}
{
}

const std::string &
Node::getName() const
{
	return name_;
}

bool
Node::hasLeafs() const
{
	return !!left_ && !!right_;
}

void
Node::setLeafs(std::shared_ptr<Node> left, std::shared_ptr<Node> right)
{
	if (!left || !right) {
		throw std::runtime_error("null argument");
	}

	left_ = std::move(left);
	right_ = std::move(right);
}

const std::shared_ptr<Node> &
Node::getLeft()
{
	return left_;
}

const std::shared_ptr<Node> &
Node::getRight()
{
	return right_;
}

}
