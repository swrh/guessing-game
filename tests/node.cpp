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

BOOST_AUTO_TEST_CASE(Node_setLeafs_setLeft_and_setRight_moves) {
	auto base = std::make_shared<gg::Node>("base");
	auto left = std::make_shared<gg::Node>("left");
	auto right = std::make_shared<gg::Node>("right");

	base->setLeafs(std::move(left), std::move(right));
	BOOST_REQUIRE(!left);
	BOOST_REQUIRE(!right);

	left = std::make_shared<gg::Node>("left1");
	base->setLeft(std::move(left));
	BOOST_REQUIRE(!left);

	right = std::make_shared<gg::Node>("right1");
	base->setLeft(std::move(right));
	BOOST_REQUIRE(!right);
}

BOOST_AUTO_TEST_CASE(Node_setLeafs_setLeft_and_setRight_throws_exceptions) {
	auto base = std::make_shared<gg::Node>("base");
	auto left = std::make_shared<gg::Node>("left");
	auto right = std::make_shared<gg::Node>("right");

	BOOST_CHECK_EXCEPTION(base->setLeft(nullptr), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "null argument";
		});

	BOOST_CHECK_EXCEPTION(base->setRight(nullptr), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "null argument";
		});

	BOOST_CHECK_EXCEPTION(base->setLeafs(left, nullptr), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "one of the arguments is null and the other is not";
		});

	BOOST_CHECK_EXCEPTION(base->setLeafs(nullptr, right), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "one of the arguments is null and the other is not";
		});

	BOOST_CHECK_EXCEPTION(base->setLeft(left), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "right is null";
		});

	BOOST_CHECK_EXCEPTION(base->setRight(right), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "left is null";
		});

	base->setLeafs(std::move(left), std::move(right));

	left = std::make_shared<gg::Node>("left");
	right = std::make_shared<gg::Node>("right");

	base->setLeft(left);
	BOOST_CHECK_EQUAL(left, base->getLeft());

	base->setRight(right);
	BOOST_CHECK_EQUAL(right, base->getRight());

	BOOST_CHECK_EXCEPTION(base->setLeft(nullptr), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "null argument";
		});

	BOOST_CHECK_EXCEPTION(base->setRight(nullptr), std::runtime_error, [](const std::runtime_error &e) {
			return std::string(e.what()) == "null argument";
		});
}
