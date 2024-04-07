#include "des.h"
#include "des_constants.h"
#include <bit>

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

std::bitset<4> sbox_for(int box, const std::bitset<6>& box_input) {
    uint8_t row = box_input[0] << 1 | box_input[5];
    uint8_t col = (box_input.to_ullong() >> 1) & 0xf;
    
    int s = des::s_t[box][row][col];
    return s;
}

void writeResultOfBox(int box, const std::bitset<4>& box_output, std::bitset<32>& result) {
    int start_index = box * 4;
    for (int i = 0; i < 4; i++) {
        int target_index = start_index + i;
        result[target_index] = box_output[i];
    }
}

std::bitset<32> des::select(const std::bitset<48>& input) {
    std::bitset<32> result;
    for (int box = 0; box < 8; box++) {
        std::bitset<6> box_input = (input.to_ullong() >> (6 * box)) & 0x3f;
        std::bitset<4> box_output = sbox_for(box, box_input);
        writeResultOfBox(box, box_output, result);
    }
    return result;
}

std::pair<uint32_t, uint32_t> des::split(const std::bitset<64>& input) {
    return {
        input.to_ullong() >> 32,
        input.to_ullong() & 0xffffffff,
    };
}

std::bitset<64> des::merge(uint32_t l, uint32_t r) {
    return {(uint64_t) l << 32 | r};
}

std::bitset<56> des::place_select1(const std::bitset<64>& input) {
    std::bitset<56> result;
    for (int offset = 0; offset < 56; offset++) {
        int target_index = ps1_t[offset] - 1;
        result[offset] = input[target_index];
    }
    return result;
}

std::bitset<48> des::place_select2(const std::bitset<56>& input) {
    std::bitset<48> result;
    for (int offset = 0; offset < 48; offset++) {
        int target_index = ps2_t[offset] - 1;
        result[offset] = input[target_index];
    }
    return result;
}

std::bitset<56> des::rotl(const std::bitset<56>& input, int cnt) {
    uint64_t c = input.to_ullong() >> 28;
    uint64_t d = input.to_ullong() & 0xfffffff;
    c = std::rotl(c, cnt);
    d = std::rotl(d, cnt);
    return {(c << 28) | d};
}

std::bitset<48> des::get_actual_key_rnd(const std::bitset<64>& key, int rnd) {
    std::bitset<56> step_key = place_select1(key);
    for (int i = 0; i < rnd; i++) {
        step_key = rotl(step_key, rotl_t[i]);
    }
    std::bitset<48> actual_key = place_select2(step_key);
    return actual_key;
}

std::bitset<64> des::encrypt(const std::bitset<64>& original, const std::bitset<64>& key) {
    std::bitset<64> content = ip(original);
    std::bitset<56> step_key = place_select1(key);
    for (int rnd = 0; rnd < 16; rnd++) {
        step_key = rotl(step_key, rotl_t[rnd]);
        std::bitset<48> actual_key = place_select2(step_key);
        content = round(content, actual_key);
    }
    content = ip_r(content);
    auto [l, r] = split(content);
    return merge(r, l);
}

std::bitset<64> des::decrypt(const std::bitset<64>& encrypted, const std::bitset<64>& key) {
    std::bitset<64> content = ip(encrypted);
    for (int rnd = 15; rnd >= 0; rnd--) {
        std::bitset<48> actual_key = get_actual_key_rnd(key, rnd);
        content = round(content, actual_key);
    }
    content = ip_r(content);
    auto [l, r] = split(content);
    return merge(r, l);
}

