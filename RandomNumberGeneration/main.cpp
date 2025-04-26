#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>

#include "LCG.h"

void test_generator(LCG& gen);
void show_distribution(LCG& gen);

int main() {
    uint32_t seed = static_cast<uint32_t>(time(nullptr));
    LCG lcg_gen(seed);

    test_generator(lcg_gen);

    std::cout << '\n';

    show_distribution(lcg_gen);
}

void test_generator(LCG& gen) {
    std::cout << "Random in [0, " << LCG::rand_max << "]:" << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << gen.rand_int() << '\n';
    }

    std::cout << '\n';

    std::cout << "Random in [0, 36]:" << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << gen.rand_int(36 + 1) << '\n';
    }

    std::cout << '\n';

    std::cout << "Random in [0, 1):" << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << gen.rand_double() << '\n';
    }
}

void show_distribution(LCG& gen) {
    constexpr int total_bins = 20;
    constexpr int sample_size = 1'000'000;

    std::vector<int> histogram(total_bins, 0);
    for (int i = 0; i < sample_size; ++i) {
        uint32_t rand_value = gen.rand_int();

        int bin_index = static_cast<uint64_t>(rand_value) * total_bins / LCG::rand_max;
        if (bin_index == total_bins)
            bin_index--;

        histogram[bin_index]++;
    }

    std::cout << "Distribution:\n";
    for (int& bin_value : histogram) {
        std::cout << std::string(bin_value / 1000, '|') << '\n';
    }
}
