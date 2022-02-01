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
	if (!!left != !!right) {
		throw std::runtime_error("one of the arguments is null and the other is not");
	}
	left_ = std::move(left);
	right_ = std::move(right);
}

void
Node::setLeft(std::shared_ptr<Node> left)
{
	if (!left) {
		throw std::runtime_error("null argument");
	}
	if (!right_) {
		// setLeafs() must be used in case the other side is null
		throw std::runtime_error("right is null");
	}
	left_ = std::move(left);
}

const std::shared_ptr<Node> &
Node::getLeft() const
{
	return left_;
}

void
Node::setRight(std::shared_ptr<Node> right)
{
	if (!right) {
		throw std::runtime_error("null argument");
	}
	if (!left_) {
		// setLeafs() must be used in case the other side is null
		throw std::runtime_error("left is null");
	}
	right_ = std::move(right);
}

const std::shared_ptr<Node> &
Node::getRight() const
{
	return right_;
}

}
