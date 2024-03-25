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

}