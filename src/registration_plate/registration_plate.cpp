#include "registration_plate.h"
#include <regex>

namespace registration_plate {
    registration_plate::registration_plate(const char *str) {
        static const std::regex pattern(R"(^[A-Za-z]{1,2}[0-9]{4}[A-Za-z]{2}$)");
        if (!std::regex_match(str, pattern)) {
            throw std::invalid_argument("Invalid registration plate format");
        }
        plate_ = str;
    }

    registration_plate::~registration_plate() {
        delete[] plate_;
    }

    bool registration_plate::operator<(const registration_plate &other) const noexcept {
        return plate_ < other.plate_;
    }

    bool registration_plate::operator==(const registration_plate &other) const noexcept {
        return plate_ == other.plate_;
    }

    const char * registration_plate::to_string() const noexcept {
        return plate_;
    }

    std::ostream & operator<<(std::ostream &os, const registration_plate &rp) {
        return os << rp.to_string();
    }

    std::ifstream & operator>>(std::ifstream &is, registration_plate &rp) {

    }
} // registration_plate
