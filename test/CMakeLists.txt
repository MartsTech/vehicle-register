# Add a target for the unit tests
add_executable(test_target
        registration_plate/registration_plate.cpp,
        ucn/ucn.cpp,
        vehicle_register/vehicle_register.cpp)

target_link_libraries(
        test_target
        PRIVATE
        Catch2::Catch2WithMain,
)

target_include_directories(
        test_target
        PRIVATE
        ${CMAKE_SOURCE_DIR}
)

# Automatically register all tests
catch_discover_tests(test_target)

# add_test(test_all test_target)
