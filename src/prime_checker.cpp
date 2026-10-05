#include "prime_checker.hpp"

#include <array>

namespace prime {

bool isPrimeTrialDivision(std::uint64_t n) {
    if (n < 2) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if ((n & 1ULL) == 0) {
        return false;
    }

    for (std::uint64_t d = 3; d <= n / d; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }

    return true;
}

namespace {

std::uint64_t modularMultiply(std::uint64_t a,
                              std::uint64_t b,
                              std::uint64_t mod) {
#if defined(__SIZEOF_INT128__)
    return static_cast<std::uint64_t>(
        (static_cast<unsigned __int128>(a) * b) % mod
    );
#else
    std::uint64_t result = 0;
    a %= mod;

    while (b > 0) {
        if (b & 1ULL) {
            result = (result >= mod - a) ? result - (mod - a) : result + a;
        }
        a = (a >= mod - a) ? a - (mod - a) : a + a;
        b >>= 1U;
    }

    return result;
#endif
}

std::uint64_t modularPower(std::uint64_t base,
                           std::uint64_t exponent,
                           std::uint64_t mod) {
    std::uint64_t result = 1 % mod;
    base %= mod;

    while (exponent > 0) {
        if (exponent & 1ULL) {
            result = modularMultiply(result, base, mod);
        }
        base = modularMultiply(base, base, mod);
        exponent >>= 1U;
    }

    return result;
}

bool witnessPasses(std::uint64_t a,
                   std::uint64_t d,
                   unsigned int s,
                   std::uint64_t n) {
    if (a % n == 0) {
        return true;
    }

    std::uint64_t x = modularPower(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    for (unsigned int r = 1; r < s; ++r) {
        x = modularMultiply(x, x, n);
        if (x == n - 1) {
            return true;
        }
    }

    return false;
}

} // namespace

bool isPrimeMillerRabin(std::uint64_t n) {
    if (n < 2) {
        return false;
    }

    constexpr std::array<std::uint64_t, 12> smallPrimes{
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
    };

    for (const auto p : smallPrimes) {
        if (n == p) {
            return true;
        }
        if (n % p == 0) {
            return false;
        }
    }

    std::uint64_t d = n - 1;
    unsigned int s = 0;

    while ((d & 1ULL) == 0) {
        d >>= 1U;
        ++s;
    }

    // Deterministic for all uint64_t inputs.
    constexpr std::array<std::uint64_t, 7> witnesses{
        2ULL, 325ULL, 9375ULL, 28178ULL,
        450775ULL, 9780504ULL, 1795265022ULL
    };

    for (const auto a : witnesses) {
        if (!witnessPasses(a, d, s, n)) {
            return false;
        }
    }

    return true;
}

} // namespace prime
