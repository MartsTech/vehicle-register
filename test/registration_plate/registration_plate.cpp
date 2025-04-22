#include "registration_plate/registration_plate.h"
#include "catch2/catch_all.hpp"

TEST_CASE("RegistrationPlateTest") {
    SECTION("Valid Plates") {
        REQUIRE_NOTHROW(registration_plate("AB1234CD"));
        REQUIRE_NOTHROW(registration_plate("A1234CD"));
    }

    SECTION("Invalid Plates") {
        REQUIRE_THROWS_AS(registration_plate("AB123CD"), std::invalid_argument);
        REQUIRE_THROWS_AS(registration_plate("ABC1234D"), std::invalid_argument);
    }

    SECTION("Comparison") {
        registration_plate a("A1234AA");
        registration_plate b("B0000ZZ");
        REQUIRE(a < b);
        REQUIRE_FALSE(b < a);
    }
}
