#ifndef UCN_H
#define UCN_H

#include <string>

class ucn {
public:
    ucn() = default;

    explicit ucn(const char *str);

    int year() const noexcept;

    int month() const noexcept;

    int day() const noexcept;

    std::string region() const noexcept;

    static bool is_valid_ucn(const char *str) noexcept;

    const char *to_string() const noexcept;

    bool operator==(const ucn &other) const noexcept;

private:
    std::string ucn_;
    int year_, month_, day_;
    int region_code_;

    void decode() noexcept;

    static int checksum(const std::string &s) noexcept;
};

std::ostream &operator<<(std::ostream &os, const ucn &ucn);

std::istream &operator>>(std::istream &is, ucn &ucn);

#endif //UCN_H
