#include "gg/node.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Node_getName_works) {
	gg::Node n{"foo"}, m{"bar"};

	BOOST_REQUIRE_EQUAL(n.getName(), "foo");
	BOOST_REQUIRE_EQUAL(m.getName(), "bar");
}

BOOST_AUTO_TEST_CASE(Node_hasLeafs_and_setLeafs_works) {
	std::shared_ptr<gg::Node> base = std::make_shared<gg::Node>("base");
	BOOST_REQUIRE(!base->hasLeafs());

	std::shared_ptr<gg::Node> left = std::make_shared<gg::Node>("left");
	BOOST_REQUIRE(!left->hasLeafs());

	std::shared_ptr<gg::Node> right = std::make_shared<gg::Node>("right");
	BOOST_REQUIRE(!right->hasLeafs());

	base->setLeafs(left, right);
	BOOST_REQUIRE(base->hasLeafs());
	BOOST_REQUIRE_EQUAL(base->getLeft()->getName(), "left");
	BOOST_REQUIRE_EQUAL(base->getLeft(), left);
	BOOST_REQUIRE(!base->getLeft()->hasLeafs());
	BOOST_REQUIRE_EQUAL(base->getRight()->getName(), "right");
	BOOST_REQUIRE_EQUAL(base->getRight(), right);
	BOOST_REQUIRE(!base->getRight()->hasLeafs());
}

BOOST_AUTO_TEST_CASE(Node_setLeafs_throws_exception_when_needed) {
	std::shared_ptr<gg::Node> base = std::make_shared<gg::Node>("base");
	std::shared_ptr<gg::Node> left = std::make_shared<gg::Node>("left");
	std::shared_ptr<gg::Node> right;

	BOOST_CHECK_EXCEPTION(base->setLeafs(std::move(left), std::move(right)), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "null argument";
		});
}
