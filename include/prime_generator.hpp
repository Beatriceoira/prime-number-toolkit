#pragma once

#include <cstdint>
#include <vector>

namespace prime {

std::vector<std::uint64_t> generatePrimes(std::uint64_t limit);
std::vector<std::uint64_t> primesInRange(std::uint64_t left, std::uint64_t right);

} // namespace prime
