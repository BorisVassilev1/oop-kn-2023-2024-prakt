#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "math/fact.hpp"

TEST_CASE("Factorial2")
{
    SECTION("Test factorial function")
    {
        int m = fact(5);

        REQUIRE(m == 120);
    }
}