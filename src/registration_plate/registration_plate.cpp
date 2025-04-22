#include "registration_plate.h"
#include <regex>

const std::regex plate_pattern(R"(^[A-Za-z]{1,2}[0-9]{4}[A-Za-z]{2}$)");

registration_plate::registration_plate(const char *plate) : plate_(plate) {
    if (!std::regex_match(plate, plate_pattern)) {
        throw std::invalid_argument("Невалиден формат на регистрационния номер");
    }
}

bool registration_plate::operator<(const registration_plate &other) const noexcept {
    return plate_ < other.plate_;
}

bool registration_plate::operator==(const registration_plate &other) const noexcept {
    return plate_ == other.plate_;
}

const char *registration_plate::to_string() const noexcept {
    return plate_.c_str();
}

std::ostream &operator<<(std::ostream &os, const registration_plate &plate) {
    return os << plate.to_string();
}

std::istream &operator>>(std::istream &is, registration_plate &plate) {
    std::string tmp;
    if (!(is >> tmp)) return is;
    try {
        plate = registration_plate(tmp.c_str());
    } catch (const std::invalid_argument &) {
        is.setstate(std::ios::failbit);
    }
    return is;
}
