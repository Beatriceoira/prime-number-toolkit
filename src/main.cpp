#include "prime_analysis.hpp"
#include "prime_checker.hpp"
#include "prime_generator.hpp"
#include "prime_factorization.hpp"
#include "prime_utils.hpp"

#include <chrono>
#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;

std::uint64_t readUnsigned(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string input;
        std::cin >> input;

        if (input.empty() || input.front() == '-') {
            std::cout << "Please enter a valid non-negative integer.\n";
            continue;
        }

        try {
            std::size_t consumed = 0;
            const auto value = std::stoull(input, &consumed);

            if (consumed == input.size()) {
                return value;
            }
        } catch (...) {
        }

        std::cout << "Please enter a valid non-negative integer.\n";
    }
}

void printPrimes(const std::vector<std::uint64_t>& primes) {
    if (primes.empty()) {
        std::cout << "No primes found.\n";
        return;
    }

    constexpr std::size_t perLine = 12;

    for (std::size_t i = 0; i < primes.size(); ++i) {
        std::cout << primes[i];

        if ((i + 1) % perLine == 0 || i + 1 == primes.size()) {
            std::cout << '\n';
        } else {
            std::cout << ' ';
        }
    }
}

void checkPrime() {
    const auto n = readUnsigned("Enter number: ");

    const bool trial = prime::isPrimeTrialDivision(n);
    const bool miller = prime::isPrimeMillerRabin(n);

    std::cout << "\nNumber: " << prime::formatNumber(n) << '\n';
    std::cout << "Trial division: "
              << (trial ? "prime" : "not prime") << '\n';
    std::cout << "Miller-Rabin:   "
              << (miller ? "prime" : "not prime") << '\n';
}

void generate() {
    const auto limit = readUnsigned("Generate primes up to: ");
    const auto primes = prime::generatePrimes(limit);

    std::cout << "\nFound " << primes.size() << " primes.\n";
    printPrimes(primes);
}

void count() {
    const auto limit = readUnsigned("Count primes up to: ");
    std::cout << "\nπ(" << prime::formatNumber(limit) << ") = "
              << prime::countPrimes(limit) << '\n';
}

void nth() {
    const auto n = readUnsigned("Find the nth prime, n = ");

    try {
        std::cout << "\nThe " << prime::formatNumber(n)
                  << "th prime is " << prime::nthPrime(n) << '\n';
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }
}

void factorize() {
    const auto n = readUnsigned("Factorize number: ");

    if (n < 2) {
        std::cout << "\nNumbers below 2 have no prime factorization.\n";
        return;
    }

    const auto factors = prime::primeFactorization(n);

    std::cout << "\n" << n << " = "
              << prime::formatFactorization(n) << '\n';

    std::cout << "Prime factors: ";
    printPrimes(factors);
}

void twinPrimes() {
    const auto limit = readUnsigned("Find twin primes up to: ");
    const auto twins = prime::findTwinPrimes(limit);

    std::cout << "\nFound " << twins.size() << " twin-prime pairs.\n";

    for (const auto& [a, b] : twins) {
        std::cout << "(" << a << ", " << b << ")\n";
    }
}

void primeGaps() {
    const auto limit = readUnsigned("Analyze primes up to: ");
    const auto [left, right] = prime::largestPrimeGap(limit);

    if (left == 0 && right == 0) {
        std::cout << "\nAt least two primes are required.\n";
        return;
    }

    std::cout << "\nLargest gap: " << (right - left) << '\n';
    std::cout << "Between: " << left << " and " << right << '\n';
}

void rangeQuery() {
    const auto left = readUnsigned("Start of range: ");
    const auto right = readUnsigned("End of range: ");

    try {
        const auto primes = prime::primesInRange(left, right);

        std::cout << "\nFound " << primes.size()
                  << " primes in the range.\n";
        printPrimes(primes);
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }
}

void benchmark() {
    const auto n = readUnsigned("Benchmark primality testing for: ");

    auto start = Clock::now();
    const bool trial = prime::isPrimeTrialDivision(n);
    const auto trialTime = std::chrono::duration<double, std::micro>(
        Clock::now() - start
    ).count();

    start = Clock::now();
    const bool miller = prime::isPrimeMillerRabin(n);
    const auto millerTime = std::chrono::duration<double, std::micro>(
        Clock::now() - start
    ).count();

    std::cout << "\nResult:\n";
    std::cout << "  Trial division: "
              << (trial ? "prime" : "not prime")
              << " | " << trialTime << " µs\n";
    std::cout << "  Miller-Rabin:   "
              << (miller ? "prime" : "not prime")
              << " | " << millerTime << " µs\n";
}

void printMenu() {
    std::cout << R"(
========================================
          PRIME NUMBER TOOLKIT
========================================
1. Check if a number is prime
2. Generate primes up to N
3. Count primes up to N
4. Find the nth prime
5. Prime factorization
6. Find twin primes
7. Analyze largest prime gap
8. Find primes in a range
9. Benchmark primality algorithms
0. Exit
========================================
)";
}

} // namespace

int main() {
    std::cout << "Prime Number Toolkit v1.0\n";

    while (true) {
        printMenu();

        const auto choice = readUnsigned("Select an option: ");
        std::cout << '\n';

        try {
            switch (choice) {
                case 1:
                    checkPrime();
                    break;
                case 2:
                    generate();
                    break;
                case 3:
                    count();
                    break;
                case 4:
                    nth();
                    break;
                case 5:
                    factorize();
                    break;
                case 6:
                    twinPrimes();
                    break;
                case 7:
                    primeGaps();
                    break;
                case 8:
                    rangeQuery();
                    break;
                case 9:
                    benchmark();
                    break;
                case 0:
                    std::cout << "Goodbye.\n";
                    return 0;
                default:
                    std::cout << "Invalid option.\n";
                    break;
            }
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << '\n';
        }

        std::cout << '\n';
    }
}
