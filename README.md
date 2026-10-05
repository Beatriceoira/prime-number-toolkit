# Prime Number Toolkit

A modular C++20 command-line application for prime-number computation, analysis, and benchmarking.

## Features

- Primality testing with optimized trial division
- Deterministic Miller-Rabin primality testing for 64-bit integers
- Prime generation using the Sieve of Eratosthenes
- Prime counting
- Nth-prime lookup
- Prime factorization
- Twin-prime detection
- Largest prime-gap analysis
- Range prime queries using a segmented sieve
- Algorithm benchmarking
- GoogleTest unit tests
- CMake build system
- C++20 implementation with warnings enabled

## Project Structure

```text
prime-number-toolkit/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   ├── prime_checker.hpp
│   ├── prime_generator.hpp
│   ├── prime_factorization.hpp
│   ├── prime_analysis.hpp
│   └── prime_utils.hpp
├── src/
│   ├── main.cpp
│   ├── prime_checker.cpp
│   ├── prime_generator.cpp
│   ├── prime_factorization.cpp
│   ├── prime_analysis.cpp
│   └── prime_utils.cpp
└── tests/
    └── test_primes.cpp
```

## Requirements

- C++20 compiler
- CMake 3.20 or newer
- Optional: GoogleTest for the test suite

Tested conceptually with GCC, Clang, and MSVC-compatible C++20 toolchains.

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run:

```bash
./build/prime-toolkit
```

On Windows, the executable may be located under a configuration directory such as:

```text
build/Debug/prime-toolkit.exe
```

## Testing

If GoogleTest is installed and discoverable by CMake:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The project still builds without GoogleTest; the test target is simply omitted.

## Algorithms

### Trial Division

The optimized trial-division implementation checks only odd divisors and stops when:

```text
d <= n / d
```

Using division instead of `d * d <= n` avoids integer multiplication overflow.

Complexity:

```text
Time:  O(sqrt(n))
Space: O(1)
```

### Sieve of Eratosthenes

Used for generating all primes up to a limit.

Complexity:

```text
Time:  O(n log log n)
Space: O(n)
```

### Segmented Sieve

Used for prime queries over an interval `[L, R]`. This avoids allocating a sieve for every number below `R`.

Complexity is approximately:

```text
Time:  O((R-L+1) log log R)
Space: O(R-L+1)
```

### Miller-Rabin

The implementation uses the known deterministic witness set for the full unsigned 64-bit range.

This provides substantially faster primality testing for large 64-bit values than trial division.

## Example

Prime factorization:

```text
Select an option: 5
Factorize number: 360

360 = 2^3 × 3^2 × 5
Prime factors: 2 2 2 3 3 5
```

Prime analysis:

```text
Select an option: 7
Analyze primes up to: 100

Largest gap: 8
Between: 89 and 97
```

## Design Goals

The project intentionally separates:

- primality algorithms
- prime generation
- factorization
- prime analysis
- formatting
- command-line interaction

This keeps the numerical algorithms independently testable and makes it easier to add additional algorithms later.

## Future Improvements

Potential extensions include:

- Pollard's Rho factorization for large integers
- Euler's totient function
- Möbius function
- Goldbach decomposition
- Prime-counting algorithms beyond a full sieve
- Parallel segmented sieve
- Persistent benchmark results
- JSON output mode
- Interactive performance comparison
- Additional property-based tests

## License

MIT License.
