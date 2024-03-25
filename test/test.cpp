#include "des.h"
#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <random>

TEST_CASE("AddTest", "[add]") {
    REQUIRE(des::add(1, 2) == 3);
}

TEST_CASE("IPTest", "[ip]") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distrib(0, std::numeric_limits<uint64_t>::max());
    
    uint64_t input = distrib(gen);
    REQUIRE(des::ip_r(des::ip(input)) == input);
    REQUIRE(des::ip(des::ip_r(input)) == input);
}