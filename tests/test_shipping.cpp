#include <shipping/shipping.h>

#include <gtest/gtest.h>

#include <stdexcept>

using shipping::get_reindeer_price;

TEST(GetReindeerPriceTest, FailOnNonPositiveLength) {
    EXPECT_THROW(get_reindeer_price(-1, 2, 3, 4), std::runtime_error);
    EXPECT_THROW(get_reindeer_price(0, 2, 3, 4), std::runtime_error);
}

TEST(GetReindeerPriceTest, FailOnNonNegativeWidth) {
    EXPECT_THROW(get_reindeer_price(1, -2, 3, 4), std::runtime_error);
    EXPECT_THROW(get_reindeer_price(1, 0, 3, 4), std::runtime_error);
}

TEST(GetReindeerPriceTest, FailOnNonNegativeHeight) {
    EXPECT_THROW(get_reindeer_price(1, 2, -3, 4), std::runtime_error);
    EXPECT_THROW(get_reindeer_price(1, 2, 0, 4), std::runtime_error);
}

TEST(GetReindeerPriceTest, FailOnNonNegativeWeight) {
    EXPECT_THROW(get_reindeer_price(1, 2, 3, -4), std::runtime_error);
    EXPECT_THROW(get_reindeer_price(1, 2, 4, 0), std::runtime_error);
}

TEST(GetReindeerPriceTest, FailOnParcelTooLarge) {
    EXPECT_THROW(get_reindeer_price(300, 300, 300, 300), std::runtime_error);
}

TEST(GetReindeerPriceTest, LowestPrice) {
    EXPECT_EQ(get_reindeer_price(1, 1, 1, 1), 2.99);
    EXPECT_EQ(get_reindeer_price(30, 20, 20, 2), 2.99);
}
