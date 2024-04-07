#include <bit>
#include <string>
#include <bitset>
#include <cstdint>

namespace des {

// 此函数仅用于单元测试框架
int add(int a, int b);

template<int N>
class bitset {
    std::array<bool, N> data;
public:

};

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

std::bitset<56> place_select1(const std::bitset<64>& input);
std::bitset<48> place_select2(const std::bitset<56>& input);

std::bitset<64> encrypt(const std::bitset<64>& original, const std::bitset<64>& key);
std::bitset<64> decrypt(const std::bitset<64>& encrypted, const std::bitset<64>& key);

std::bitset<56> rotl(const std::bitset<56>& input, int cnt);
std::bitset<48> get_actual_key_rnd(const std::bitset<64>& key, int rnd);

template<size_t N>
std::bitset<N> revert(const std::bitset<N>& input) {
    std::bitset<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = input[N - i - 1];
    }
    return result;
}

}