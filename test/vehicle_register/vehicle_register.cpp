#include "vehicle_register/vehicle_register.h"
#include "catch2/catch_all.hpp"

TEST_CASE("VehicleRegisterTest") {
    SECTION("Register and Query Owned Vehicles") {
        vehicle_register vr;
        registration_plate r("A1234BC");
        ucn u("8001010007");
        vr.register_vehicle(r, u);
        auto v = vr.owned_vehicles(u);
        REQUIRE(v.size() == 1);
        REQUIRE(v[0] == r);
    }

    SECTION("Deregister Vehicle") {
        vehicle_register vr;
        registration_plate r("A1234BC");
        ucn u("8001010007");
        vr.register_vehicle(r, u);
        vr.deregister(r);
        auto v = vr.owned_vehicles(u);
        REQUIRE(v.empty());
    }

    SECTION("Register Existing Vehicle Throws") {
        vehicle_register vr;
        registration_plate r("A1234BC");
        ucn u1("8001010007");
        ucn u2("9001011234");
        vr.register_vehicle(r, u1);
        REQUIRE_THROWS_AS(vr.register_vehicle(r, u2), std::runtime_error);
    }

    SECTION("Deregister Non-Existing Vehicle Does Not Throw") {
        vehicle_register vr;
        registration_plate r("A1234BC");
        REQUIRE_NOTHROW(vr.deregister(r));
    }

    SECTION("Owned Vehicles Returns Empty Vector For Non-Existing Owner") {
        vehicle_register vr;
        ucn u("8001010007");
        auto v = vr.owned_vehicles(u);
        REQUIRE(v.empty());
    }
}
