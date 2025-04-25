#pragma once

#include <cstdint>

class LCG {
public:
    LCG(uint32_t seed) : state(seed) {}

    // [0, m).
    // NOTE: m = 2^k, so we don't care about an overflow in a * state (which leads to truncation of high-order bytes)
    // as the calculation of (% m) is equivalent to truncation by mask anyway.
    uint32_t rand_int() { 
        state = (a * state + c) & 0x7fffffff; // (a * state + c) % m.
        return state;
    }

    // [0, max).
    uint32_t rand_int(uint32_t max) {
        return rand_int() % max;
    }

    // [0, 1).
    // NOTE: Use double instead of float, otherwise after packing of max random integer (2^31 - 1) into float
    // we'll get 2^31 because of rounding and thus will get exactly 1.0f.
    double rand_double() {
        return static_cast<double>(rand_int()) / m;
    }

private:
    uint32_t state;

    // Values should satisfy Hull–Dobell Theorem so sequence has full period m for all seed values.
    // [Random Number Generators. Hull, Dobell], p. 233.
    static constexpr uint32_t a = 1103515245; // a % 4 = 1.
    static constexpr uint32_t c = 12345; // Odd.
    static constexpr uint32_t m = 1u << 31; // 2^31.

public:
    static constexpr uint32_t rand_max = m - 1;
};
