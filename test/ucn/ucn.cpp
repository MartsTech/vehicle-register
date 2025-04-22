#include "ucn/ucn.h"
#include "catch2/catch_all.hpp"

TEST_CASE("UcnTest") {
    SECTION("Valid Ucn") {
        REQUIRE_NOTHROW(ucn("8001010007"));

        SECTION("Invalid Ucn") {
            REQUIRE_THROWS_AS(ucn("0000000000"), std::invalid_argument);
        }

        SECTION("Decode Date") {
            ucn u("8001010007");
            REQUIRE(u.year() == 1980);
            REQUIRE(u.month() == 1);
            REQUIRE(u.day() == 1);
        }
    }
}
