#ifndef REGISTRATION_PLATE_H
#define REGISTRATION_PLATE_H

#include <regex>
#include <string>

class registration_plate {
public:
    registration_plate() = default;

    explicit registration_plate(const char *plate);

    bool operator<(const registration_plate &other) const noexcept;

    bool operator==(const registration_plate &other) const noexcept;

    const char *to_string() const noexcept;

private:
    std::string plate_;
};

std::ostream &operator<<(std::ostream &os, const registration_plate &plate);

std::istream &operator>>(std::istream &is, registration_plate &plate);

#endif //REGISTRATION_PLATE_H
