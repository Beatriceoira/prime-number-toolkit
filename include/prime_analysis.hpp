#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace prime {

std::uint64_t countPrimes(std::uint64_t limit);
std::uint64_t nthPrime(std::uint64_t n);

std::vector<std::pair<std::uint64_t, std::uint64_t>>
findTwinPrimes(std::uint64_t limit);

std::pair<std::uint64_t, std::uint64_t>
largestPrimeGap(std::uint64_t limit);

} // namespace prime
