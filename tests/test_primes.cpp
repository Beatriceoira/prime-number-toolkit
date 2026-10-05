#include "prime_analysis.hpp"
#include "prime_checker.hpp"
#include "prime_generator.hpp"
#include "prime_factorization.hpp"
#include "prime_utils.hpp"

#include <gtest/gtest.h>

TEST(PrimeChecker, HandlesSmallNumbers) {
    EXPECT_FALSE(prime::isPrimeTrialDivision(0));
    EXPECT_FALSE(prime::isPrimeTrialDivision(1));
    EXPECT_TRUE(prime::isPrimeTrialDivision(2));
    EXPECT_TRUE(prime::isPrimeTrialDivision(3));
    EXPECT_FALSE(prime::isPrimeTrialDivision(4));
    EXPECT_TRUE(prime::isPrimeTrialDivision(97));
}

TEST(PrimeChecker, MillerRabinMatchesKnownValues) {
    EXPECT_TRUE(prime::isPrimeMillerRabin(2));
    EXPECT_TRUE(prime::isPrimeMillerRabin(104729));
    EXPECT_FALSE(prime::isPrimeMillerRabin(104730));
}

TEST(PrimeGenerator, GeneratesCorrectPrimes) {
    const std::vector<std::uint64_t> expected{2, 3, 5, 7, 11, 13, 17, 19};
    EXPECT_EQ(prime::generatePrimes(20), expected);
}

TEST(PrimeGenerator, HandlesRange) {
    const std::vector<std::uint64_t> expected{11, 13, 17, 19};
    EXPECT_EQ(prime::primesInRange(10, 20), expected);
}

TEST(Factorization, FactorizesCompositeNumbers) {
    const std::vector<std::uint64_t> expected{2, 2, 2, 3, 3, 5};
    EXPECT_EQ(prime::primeFactorization(360), expected);
}

TEST(Factorization, HandlesPrime) {
    const std::vector<std::uint64_t> expected{97};
    EXPECT_EQ(prime::primeFactorization(97), expected);
}

TEST(Analysis, CountsPrimes) {
    EXPECT_EQ(prime::countPrimes(10), 4);
    EXPECT_EQ(prime::countPrimes(100), 25);
}

TEST(Analysis, FindsNthPrime) {
    EXPECT_EQ(prime::nthPrime(1), 2);
    EXPECT_EQ(prime::nthPrime(5), 11);
    EXPECT_EQ(prime::nthPrime(25), 97);
}

TEST(Analysis, FindsTwinPrimes) {
    const auto result = prime::findTwinPrimes(20);

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].first, 3);
    EXPECT_EQ(result[0].second, 5);
    EXPECT_EQ(result[1].first, 5);
    EXPECT_EQ(result[1].second, 7);
}

TEST(Analysis, FindsLargestPrimeGap) {
    const auto [left, right] = prime::largestPrimeGap(30);
    EXPECT_EQ(left, 23);
    EXPECT_EQ(right, 29);
}

TEST(Utils, FormatsFactorization) {
    EXPECT_EQ(prime::formatFactorization(360), "2^3 × 3^2 × 5");
}
