#include "des.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("AddTest", "[add]") {
    REQUIRE(des::add(1, 2) == 3);
}