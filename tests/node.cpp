#include "gg/node.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Node_getName_works) {
	gg::Node n{"foo"}, m{"bar"};

	BOOST_REQUIRE_EQUAL(n.getName(), "foo");
	BOOST_REQUIRE_EQUAL(m.getName(), "bar");
}

BOOST_AUTO_TEST_CASE(Node_hasLeafs_and_setLeafs_works) {
	std::unique_ptr<gg::Node> base = std::make_unique<gg::Node>("base");
	BOOST_REQUIRE(!base->hasLeafs());

	std::unique_ptr<gg::Node> left = std::make_unique<gg::Node>("left");
	const gg::Node *pLeft = left.get();
	BOOST_REQUIRE(!left->hasLeafs());

	std::unique_ptr<gg::Node> right = std::make_unique<gg::Node>("right");
	const gg::Node *pRight = right.get();
	BOOST_REQUIRE(!right->hasLeafs());

	base->setLeafs(std::move(left), std::move(right));
	BOOST_REQUIRE(base->hasLeafs());
	BOOST_REQUIRE_EQUAL(base->getLeft().get(), pLeft);
	BOOST_REQUIRE_EQUAL(base->getLeft()->getName(), "left");
	BOOST_REQUIRE(!base->getLeft()->hasLeafs());
	BOOST_REQUIRE_EQUAL(base->getRight().get(), pRight);
	BOOST_REQUIRE_EQUAL(base->getRight()->getName(), "right");
	BOOST_REQUIRE(!base->getRight()->hasLeafs());
	BOOST_REQUIRE(!left);
	BOOST_REQUIRE(!right);
}

BOOST_AUTO_TEST_CASE(Node_setLeafs_throws_exception_when_needed) {
	std::unique_ptr<gg::Node> base = std::make_unique<gg::Node>("base");
	std::unique_ptr<gg::Node> left = std::make_unique<gg::Node>("left");
	std::unique_ptr<gg::Node> right;

	BOOST_CHECK_EXCEPTION(base->setLeafs(std::move(left), std::move(right)), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "null argument";
		});
}
