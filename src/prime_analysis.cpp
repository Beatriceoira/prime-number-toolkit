#include "prime_analysis.hpp"

#include "prime_checker.hpp"
#include "prime_generator.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace prime {

std::uint64_t countPrimes(std::uint64_t limit) {
    return static_cast<std::uint64_t>(generatePrimes(limit).size());
}

std::uint64_t nthPrime(std::uint64_t n) {
    if (n == 0) {
        throw std::invalid_argument("Prime indexing starts at 1.");
    }

    if (n <= 5) {
        constexpr std::uint64_t firstFive[] = {2, 3, 5, 7, 11};
        return firstFive[n - 1];
    }

    const long double nn = static_cast<long double>(n);
    std::uint64_t estimate =
        static_cast<std::uint64_t>(nn * (std::log(nn) + std::log(std::log(nn)))) + 10;

    while (true) {
        const auto primes = generatePrimes(estimate);
        if (primes.size() >= n) {
            return primes[static_cast<std::size_t>(n - 1)];
        }

        if (estimate > std::numeric_limits<std::uint64_t>::max() / 2) {
            throw std::overflow_error("Requested prime is too large.");
        }

        estimate *= 2;
    }
}

std::vector<std::pair<std::uint64_t, std::uint64_t>>
findTwinPrimes(std::uint64_t limit) {
    const auto primes = generatePrimes(limit);
    std::vector<std::pair<std::uint64_t, std::uint64_t>> result;

    for (std::size_t i = 1; i < primes.size(); ++i) {
        if (primes[i] - primes[i - 1] == 2) {
            result.emplace_back(primes[i - 1], primes[i]);
        }
    }

    return result;
}

std::pair<std::uint64_t, std::uint64_t>
largestPrimeGap(std::uint64_t limit) {
    const auto primes = generatePrimes(limit);

    if (primes.size() < 2) {
        return {0, 0};
    }

    std::uint64_t bestLeft = primes[0];
    std::uint64_t bestRight = primes[1];

    for (std::size_t i = 1; i < primes.size(); ++i) {
        const auto currentGap = primes[i] - primes[i - 1];
        const auto bestGap = bestRight - bestLeft;

        if (currentGap > bestGap) {
            bestLeft = primes[i - 1];
            bestRight = primes[i];
        }
    }

    return {bestLeft, bestRight};
}

} // namespace prime
