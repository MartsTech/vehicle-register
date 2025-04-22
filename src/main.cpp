#include <iostream>
#include <sstream>
#include <string>
#include <limits> // За std::numeric_limits

#ifdef _WIN32
#include <windows.h>
#endif

#include "vehicle_register/vehicle_register.h"
#include "registration_plate/registration_plate.h"
#include "ucn/ucn.h"

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    vehicle_register vehicle_registe;
    std::cout << "Въведете регистрации от вида '<ЕГН> <Регистрационен номер>' (по една на ред)." << std::endl;
    std::cout << "За край въведете 'exit' или натиснете Ctrl+D (Ctrl+Z, Enter в Windows)." << std::endl;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "exit") {
            break;
        }

        std::stringstream ss(line);
        ucn owner;
        registration_plate reg;
        ss >> owner >> reg;

        if (ss.fail()) {
            std::cerr << "Грешка при четене на ред: '" << line << "' - Невалиден формат." << std::endl;
            ss.clear();
            ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            try {
                vehicle_registe.register_vehicle(reg, owner);
                std::cout << "Регистрация добавена: " << owner << " - " << reg << std::endl;
            } catch (const std::invalid_argument &e) {
                std::cerr << "Грешка при регистрация на " << reg << " за " << owner << ": " << e.what() << std::endl;
            } catch (const std::runtime_error &e) {
                std::cerr << "Грешка при регистрация на " << reg << " за " << owner << ": " << e.what() << std::endl;
            }
        }
    }

    std::cout << "\nВсички въведени регистрации:" << std::endl;
    std::cout << vehicle_registe;

    return 0;
}
