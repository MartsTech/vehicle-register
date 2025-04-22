add_executable(vehicle_register
        vehicle_register/vehicle_register.cpp
        vehicle_register/vehicle_register.h
        ucn/ucn.cpp
        ucn/ucn.h
        registration_plate/registration_plate.cpp
        registration_plate/registration_plate.h
        main.cpp
)

set_target_properties(vehicle_register PROPERTIES OUTPUT_NAME "vehicle_register")

target_sources(
        vehicle_register
        PRIVATE
        main.cpp
)