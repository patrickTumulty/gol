

#include "gol_utils.hpp"
#include <cstdio>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

int add(int a, int b)
{
    return a + b;
}


TEST_CASE("Testing Sequence Detection")
{
    // Existing tests
    std::vector<std::size_t> seq1{1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
    CHECK(detect_period(seq1));

    std::vector<std::size_t> seq2{1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3};
    CHECK(detect_period(seq2));

    std::vector<std::size_t> seq3{1, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1};
    CHECK(detect_period(seq3));

    std::vector<std::size_t> seq4{1, 2, 3, 4, 3, 6, 1, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1};
    CHECK(not detect_period(seq4));

    // Period 1
    std::vector<std::size_t> seq5{7, 7, 7, 7, 7, 7};
    CHECK(detect_period(seq5));

    // Single element
    std::vector<std::size_t> seq6{42};
    CHECK(not detect_period(seq6));

    // Empty sequence
    std::vector<std::size_t> seq7{};
    CHECK(not detect_period(seq7));

    // Two repeats of a length-3 cycle
    std::vector<std::size_t> seq8{1, 2, 3, 1, 2, 3};
    CHECK(detect_period(seq8, 15, 2));

    // Only one occurrence of a pattern
    std::vector<std::size_t> seq9{1, 2, 3, 4};
    CHECK(not detect_period(seq9));

    // Almost periodic, last element wrong
    std::vector<std::size_t> seq10{1, 2, 3, 1, 2, 3, 1, 2, 4};
    CHECK(not detect_period(seq10));

    // Longer cycle
    std::vector<std::size_t> seq11{
        1, 2, 3, 4, 5,
        1, 2, 3, 4, 5,
        1, 2, 3, 4, 5
    };
    CHECK(detect_period(seq11));

    // Prefix noise then periodic
    std::vector<std::size_t> seq12{
        99, 88,
        1, 2, 3,
        1, 2, 3,
        1, 2, 3
    };
    // Depends on whether detect_period() requires the
    // whole sequence to be periodic or just a suffix.
    // CHECK(detect_period(seq12));

    // Repeated values but not periodic
    std::vector<std::size_t> seq13{
        1, 2, 1, 3,
        1, 2, 1, 4
    };
    CHECK(not detect_period(seq13));

    // Palindrome but not periodic
    std::vector<std::size_t> seq14{
        1, 2, 3, 4, 3, 2, 1
    };
    CHECK(not detect_period(seq14));

    // Alternation interrupted once
    std::vector<std::size_t> seq15{
        1, 2, 1, 2, 1, 5, 1, 2, 1, 2
    };
    CHECK(not detect_period(seq15));
}
