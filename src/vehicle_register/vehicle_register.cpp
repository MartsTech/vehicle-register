#include "vehicle_register.h"

#include <stdexcept>

void vehicle_register::register_vehicle(const registration_plate &registration, const ucn &owner) {
    auto it = register_.find(registration);
    if (it != register_.end() && !(it->second == owner)) {
        throw std::runtime_error("Автомобилът вече е регистриран на друг собственик");
    }
    register_[registration] = owner;
}

void vehicle_register::deregister(const registration_plate &reg) noexcept {
    register_.erase(reg);
}

std::vector<registration_plate> vehicle_register::owned_vehicles(const ucn &person) const noexcept {
    std::vector<registration_plate> res;
    for (const auto &[reg, owner]: register_) {
        if (owner == person) res.push_back(reg);
    }
    return res;
}

std::ostream &operator<<(std::ostream &os, const vehicle_register &vehicle_register) {
    for (const auto &[reg, owner]: vehicle_register.register_) {
        os << owner << " " << reg << '\n';
    }
    return os;
}

std::istream &operator>>(std::istream &is, vehicle_register &vehicle_register) {
    ucn owner;
    registration_plate reg("");
    while (is >> owner >> reg) {
        vehicle_register.register_vehicle(reg, owner);
    }
    return is;
}
