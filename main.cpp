#include <iostream>
#include <string>
#include "des.h"

using namespace std::string_literals;

int countDiff(const std::bitset<64>& a, const std::bitset<64>& b) {
    int cnt = 0;
    for (int i = 0; i < 64; i++) {
        if (a[i] != b[i])
            cnt++;
    }
    return cnt;
}

void test_a() {
    std::cout << "===Test A===" << std::endl;
    std::bitset<64> key_a {"0000001010010110010010001100010000111000001100000011100001100100"};
    std::bitset<64> content_a1 {"0000000000000000000000000000000000000000000000000000000000000000"};
    std::bitset<64> content_a2 {"1000000000000000000000000000000000000000000000000000000000000000"};
    std::bitset<64> result_a1 = des::encrypt(content_a1, key_a);
    std::bitset<64> result_a2 = des::encrypt(content_a2, key_a);
    std::cout << result_a1 << '\n' << result_a2 << '\n';
    std::cout << "diff = " << countDiff(result_a1, result_a2) << std::endl;
}

void test_b() {
    std::cout << "===Test B===" << std::endl;
    std::bitset<64> key1 {"1110001011110110110111100011000000111010000010000110001011011100"};
    std::bitset<64> content1 {"0110001011110110110111100011000000111010000010000110001011011100"};
    std::bitset<64> content2 {"0110100010000101001011110111101000010011011101101110101110100100"};
    std::bitset<64> result_a1 = des::encrypt(content1, key1);
    std::bitset<64> result_a2 = des::encrypt(content2, key1);
    std::cout << result_a1 << '\n' << result_a2 << '\n';
    std::cout << "diff = " << countDiff(result_a1, result_a2);
}

int main() {
//    std::cout << "Hello, World!" << std::endl;
    test_a();
    test_b();
    return 0;
}
