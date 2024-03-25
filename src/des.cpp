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