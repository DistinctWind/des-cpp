#include "des.h"
#include "des_constants.h"

int des::add(int a, int b) {
    return a + b;
}

std::bitset<64> des::ip(const std::bitset<64>& rhs) {
    std::bitset<64> result;
    for (int offset = 0; offset < 64; offset++) {
        int target_index = ip_t[offset] - 1;
        result[offset] = rhs[target_index];
    }
    return result;
}

std::bitset<64> des::ip_r(const std::bitset<64>& rhs) {
    std::bitset<64> result;
    for (int offset = 0; offset < 64; offset++) {
        int target_index = ip_rt[offset] - 1;
        result[offset] = rhs[target_index];
    }
    return result;
}

std::bitset<32> des::f(const std::bitset<32>& input, const std::bitset<48>& k) {
    std::bitset<48> extended = extend(input);
    extended ^= k;
    std::bitset<32> selected = select(extended);
    std::bitset<32> placed = place(selected);
    return placed;
}

std::bitset<64> des::round(const std::bitset<64>& input, const std::bitset<48>& k) {
    auto [l, r] = split(input);
    return merge(r, f(r, k).to_ulong() ^ l);
}

std::bitset<48> des::extend(const std::bitset<32>& input) {
    std::bitset<48> result;
    for (int offset = 0; offset < 48; offset++) {
        int target_index = e_t[offset] - 1;
        result[offset] = input[target_index];
    }
    return result;
}

std::bitset<32> des::place(const std::bitset<32>& input) {
    std::bitset<32> result;
    for (int offset = 0; offset < 32; offset++) {
        int target_index = p_t[offset] - 1;
        result[offset] = input[target_index];
    }
    return result;
}
