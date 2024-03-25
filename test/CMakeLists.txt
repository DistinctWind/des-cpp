add_executable(test_des_lib test.cpp)
target_link_libraries(test_des_lib PRIVATE des Catch2::Catch2WithMain)
catch_discover_tests(test_des_lib)