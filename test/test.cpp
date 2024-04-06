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

TEST_CASE("SignificantBit", "[play]") {
    std::bitset<8> test{0x1f};
    REQUIRE(test[0] == 1);
    REQUIRE(test.to_string() == "00011111");
}

TEST_CASE("SplitBit", "[utils]") {
    std::bitset<64> t{0x1122334455667788};
    auto [l, r] = des::split(t);
    REQUIRE(l == 0x55667788);
    REQUIRE(r == 0x11223344);
}

TEST_CASE("MergeBit", "[utils]") {
    uint32_t l = 0x55667788;
    uint32_t r = 0x11223344;
    std::bitset<64> result = des::merge(l, r);
    REQUIRE(result == 0x1122334455667788);
}

TEST_CASE("SplitThenMerge", "[utils]") {
    std::bitset<64> t{0x1122334455667788};
    auto [l, r] = des::split(t);
    REQUIRE(t == des::merge(l, r));
}