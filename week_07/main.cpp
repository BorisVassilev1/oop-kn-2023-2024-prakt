#include "catch2.hpp"
#include "math/fact.hpp"

TEST_CASE("Factorial")
{
    SECTION("Test factorial function4")
    {
        int n = fact(5);

        REQUIRE(n == 120);
    }
}
