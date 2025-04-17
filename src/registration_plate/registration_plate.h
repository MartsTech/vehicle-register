#ifndef REGISTRATION_PLATE_H
#define REGISTRATION_PLATE_H
#include <iosfwd>

namespace registration_plate {

class registration_plate {
public:
    explicit registration_plate(const char* str);
    ~registration_plate();
    bool operator<(const registration_plate& other) const noexcept;
    bool operator==(const registration_plate& other) const noexcept;
    const char* to_string() const noexcept;

private:
    const char* plate_;
};

std::ostream& operator<<(std::ostream& os, const registration_plate& rp);
std::ifstream& operator>>(std::ifstream& is, registration_plate& rp);

} // registration_plate

#endif //REGISTRATION_PLATE_H
