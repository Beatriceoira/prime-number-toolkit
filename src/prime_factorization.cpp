#include "prime_factorization.hpp"

#include "prime_checker.hpp"

namespace prime {

std::vector<std::uint64_t> primeFactorization(std::uint64_t n) {
    std::vector<std::uint64_t> factors;

    if (n < 2) {
        return factors;
    }

    while ((n & 1ULL) == 0) {
        factors.push_back(2);
        n /= 2;
    }

    for (std::uint64_t factor = 3; factor <= n / factor; factor += 2) {
        while (n % factor == 0) {
            factors.push_back(factor);
            n /= factor;
        }
    }

    if (n > 1) {
        factors.push_back(n);
    }

    return factors;
}

} // namespace prime
