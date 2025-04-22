#include "ucn.h"
#include <regex>

#include <array>

const std::array<std::pair<std::pair<int, int>, std::string>, 29> region_ranges = {
    {
        {{0, 43}, "Благоевград"}, {{44, 93}, "Бургас"}, {{94, 139}, "Варна"},
        {{140, 169}, "Велико Търново"}, {{170, 183}, "Видин"}, {{184, 217}, "Враца"},
        {{218, 233}, "Габрово"}, {{234, 281}, "Кърджали"}, {{282, 301}, "Кюстендил"},
        {{302, 319}, "Ловеч"}, {{320, 341}, "Монтана"}, {{342, 377}, "Пазарджик"},
        {{378, 395}, "Перник"}, {{396, 435}, "Плевен"}, {{436, 501}, "Пловдив"},
        {{502, 527}, "Разград"}, {{528, 555}, "Русе"}, {{556, 575}, "Силистра"},
        {{576, 601}, "Сливен"}, {{602, 623}, "Смолян"}, {{624, 721}, "София-град"},
        {{722, 751}, "София-окръг"}, {{752, 789}, "Стара Загора"}, {{790, 821}, "Добрич"},
        {{822, 843}, "Търговище"}, {{844, 871}, "Хасково"}, {{872, 903}, "Шумен"},
        {{904, 925}, "Ямбол"}, {{926, 999}, "Друг/Неизвестен"}
    }
};

ucn::ucn(const char *str) : ucn_(str) {
    if (!is_valid_ucn(str)) {
        throw std::invalid_argument("Invalid UCN");
    }
    decode();
}

bool ucn::is_valid_ucn(const char *str) noexcept {
    std::string ucn(str);
    if (ucn.size() != 10 || !std::all_of(ucn.begin(), ucn.end(), ::isdigit)) return false;
    const int sum = checksum(ucn);
    return sum == (ucn[9] - '0');
}

int ucn::checksum(const std::string &s) noexcept {
    static const int weights[9] = {2, 4, 8, 5, 10, 9, 7, 3, 6};
    int sum = 0;
    for (int i = 0; i < 9; ++i) sum += (s[i] - '0') * weights[i];
    const int rem = sum % 11;
    return rem == 10 ? 0 : rem;
}

void ucn::decode() noexcept {
    int year = std::stoi(ucn_.substr(0, 2));
    int month = std::stoi(ucn_.substr(2, 2));
    int day = std::stoi(ucn_.substr(4, 2));
    int region_code = std::stoi(ucn_.substr(6, 3));
    if (month > 40) {
        month -= 40;
        year += 2000;
    } else if (month > 20) {
        month -= 20;
        year += 1800;
    } else {
        year += 1900;
    }
    year_ = year;
    month_ = month;
    day_ = day;
    region_code_ = region_code;
}

bool ucn::operator==(const ucn &other) const noexcept {
    return ucn_ == other.ucn_;
}

int ucn::year() const noexcept { return year_; }
int ucn::month() const noexcept { return month_; }
int ucn::day() const noexcept { return day_; }

std::string ucn::region() const noexcept {
    for (const auto &range: region_ranges) {
        if (region_code_ >= range.first.first && region_code_ <= range.first.second) {
            return range.second;
        }
    }
    return "Друг/Неизвестен";
}

const char *ucn::to_string() const noexcept {
    return ucn_.c_str();
}

std::ostream &operator<<(std::ostream &os, const ucn &u) {
    return os << u.to_string();
}

std::istream &operator>>(std::istream &is, ucn &it) {
    std::string tmp;
    if (!(is >> tmp)) return is;
    try {
        it = ucn(tmp.c_str());
    } catch (const std::invalid_argument &) {
        is.setstate(std::ios::failbit);
    }
    return is;
}
