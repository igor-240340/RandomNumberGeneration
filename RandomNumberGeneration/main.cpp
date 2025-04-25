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
    std::cout << "random in [0, " << LCG::rand_max << "]" << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << gen.rand_int() << '\n';
    }

    std::cout << '\n';

    std::cout << "random in [0, 36]" << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << gen.rand_int(36 + 1) << '\n';
    }

    std::cout << '\n';

    std::cout << "random in [0, 1)" << '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << gen.rand_double() << '\n';
    }
}

void show_distribution(LCG& gen) {
    const int buckets = 20;
    const int samples = 1'000'000;

    std::vector<int> histogram(buckets, 0);

    for (int i = 0; i < samples; ++i) {
        uint32_t value = gen.rand_int();

        int bin = static_cast<uint64_t>(value) * buckets / LCG::rand_max;
        if (bin == buckets)
            bin = buckets - 1;

        ++histogram[bin];
    }

    for (int i = 0; i < buckets; i++) {
        std::cout << std::setw(2) << i << ": "
            << std::string(histogram[i] / (samples / 1000), '*')
            << " (" << histogram[i] << ")\n";
    }
}
