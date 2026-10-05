#include "prime_generator.hpp"

#include "prime_checker.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace prime {

std::vector<std::uint64_t> generatePrimes(std::uint64_t limit) {
    if (limit < 2) {
        return {};
    }

    if (limit > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max() - 1)) {
        throw std::overflow_error("Limit is too large for this system's memory model.");
    }

    std::vector<bool> isPrime(static_cast<std::size_t>(limit) + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    for (std::uint64_t p = 2; p <= limit / p; ++p) {
        if (!isPrime[static_cast<std::size_t>(p)]) {
            continue;
        }

        for (std::uint64_t multiple = p * p;
             multiple <= limit;
             multiple += p) {
            isPrime[static_cast<std::size_t>(multiple)] = false;
        }
    }

    std::vector<std::uint64_t> primes;
    for (std::uint64_t i = 2; i <= limit; ++i) {
        if (isPrime[static_cast<std::size_t>(i)]) {
            primes.push_back(i);
        }
    }

    return primes;
}

std::vector<std::uint64_t> primesInRange(std::uint64_t left,
                                         std::uint64_t right) {
    if (left > right || right < 2) {
        return {};
    }

    left = std::max<std::uint64_t>(left, 2);

    const std::uint64_t root =
        static_cast<std::uint64_t>(std::sqrt(static_cast<long double>(right))) + 1;

    const auto basePrimes = generatePrimes(root);

    if (right - left > 100'000'000ULL) {
        throw std::invalid_argument(
            "Range is too large for the CLI segmented sieve limit."
        );
    }

    std::vector<bool> composite(
        static_cast<std::size_t>(right - left) + 1, false
    );

    for (const auto p : basePrimes) {
        if (p > right / p) {
            break;
        }

        std::uint64_t start = std::max(p * p, ((left + p - 1) / p) * p);

        for (std::uint64_t multiple = start;
             multiple <= right;
             multiple += p) {
            composite[static_cast<std::size_t>(multiple - left)] = true;
        }
    }

    std::vector<std::uint64_t> result;

    for (std::uint64_t i = left; i <= right; ++i) {
        if (!composite[static_cast<std::size_t>(i - left)]) {
            result.push_back(i);
        }
    }

    return result;
}

} // namespace prime
