#include "prime_utils.hpp"

#include "prime_factorization.hpp"

#include <sstream>
#include <unordered_map>
#include <vector>

namespace prime {

std::string formatNumber(std::uint64_t value) {
    std::string digits = std::to_string(value);

    for (std::ptrdiff_t pos = static_cast<std::ptrdiff_t>(digits.size()) - 3;
         pos > 0;
         pos -= 3) {
        digits.insert(static_cast<std::size_t>(pos), ",");
    }

    return digits;
}

std::string formatFactorization(std::uint64_t n) {
    if (n < 2) {
        return std::to_string(n);
    }

    const auto factors = primeFactorization(n);

    std::ostringstream out;

    for (std::size_t i = 0; i < factors.size();) {
        const auto factor = factors[i];
        std::size_t count = 0;

        while (i < factors.size() && factors[i] == factor) {
            ++count;
            ++i;
        }

        if (out.tellp() > 0) {
            out << " × ";
        }

        out << factor;

        if (count > 1) {
            out << "^" << count;
        }
    }

    return out.str();
}

} // namespace prime
