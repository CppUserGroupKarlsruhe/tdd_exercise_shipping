set(TEST_FILES test_shipping.cpp test_parcel.cpp)

add_executable(test_shipping ${TEST_FILES})
add_dependencies(test_shipping shipping)

target_link_libraries(test_shipping
    shipping
    gtest_main
    gtest
    )

add_test(NAME test_shipping_test COMMAND test_shipping)
