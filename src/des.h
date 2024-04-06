#include <bit>
#include <string>
#include <bitset>
#include <cstdint>

namespace des {

// 此函数仅用于单元测试框架
int add(int a, int b);

// 初始置换和逆初始置换
std::bitset<64> ip(const std::bitset<64>& rhs);
std::bitset<64> ip_r(const std::bitset<64>& rhs);

std::bitset<64> round(const std::bitset<64>& input, const std::bitset<48>& k);
std::bitset<48> extend(const std::bitset<32>& input);
std::bitset<32> select(const std::bitset<48>& input);
std::bitset<32> place(const std::bitset<32>& input);
std::bitset<32> f(const std::bitset<32>& input, const std::bitset<48>& k);

std::pair<uint32_t, uint32_t> split(const std::bitset<64>& input);
std::bitset<64> merge(uint32_t l, uint32_t r);

}