#ifndef VEHICLE_REGISTER_H
#define VEHICLE_REGISTER_H

#include <map>
#include <vector>
#include "registration_plate/registration_plate.h"
#include "ucn/ucn.h"

class vehicle_register {
public:
    std::map<registration_plate, ucn> register_;

    vehicle_register() = default;

    void register_vehicle(const registration_plate &registration, const ucn &owner);

    void deregister(const registration_plate &reg) noexcept;

    std::vector<registration_plate> owned_vehicles(const ucn &person) const noexcept;
};

std::ostream &operator<<(std::ostream &os, const vehicle_register &vehicle_register);

std::istream &operator>>(std::istream &is, vehicle_register &vehicle_register);

#endif //VEHICLE_REGISTER_H
