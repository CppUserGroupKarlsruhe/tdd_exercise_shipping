#include <shipping/shipping.h>

#include <gtest/gtest.h>

#include <stdexcept>

using shipping::get_reindeer_price;
using shipping::parcel;

TEST(ParcelTest, FailOnNonPositiveLength) {
    EXPECT_THROW(parcel(-1, 2, 3, 4), std::runtime_error);
    EXPECT_THROW(parcel(0, 2, 3, 4), std::runtime_error);
}

TEST(ParcelTest, FailOnNonNegativeWidth) {
    EXPECT_THROW(parcel(1, -2, 3, 4), std::runtime_error);
    EXPECT_THROW(parcel(1, 0, 3, 4), std::runtime_error);
}

TEST(ParcelTest, FailOnNonNegativeHeight) {
    EXPECT_THROW(parcel(1, 2, -3, 4), std::runtime_error);
    EXPECT_THROW(parcel(1, 2, 0, 4), std::runtime_error);
}

TEST(ParcelTest, FailOnNonNegativeWeight) {
    EXPECT_THROW(parcel(1, 2, 3, -4), std::runtime_error);
    EXPECT_THROW(parcel(1, 2, 4, 0), std::runtime_error);
}

TEST(ParcelTest, StoresPhysicalData) {
    parcel const p(1, 2, 3, 4);
    EXPECT_EQ(p.length, 1);
    EXPECT_EQ(p.width, 2);
    EXPECT_EQ(p.height, 3);
    EXPECT_EQ(p.weight, 4);
}

TEST(GetReindeerPriceTest, FailOnParcelTooLarge) {
    EXPECT_THROW(get_reindeer_price({300, 300, 300, 300}), std::runtime_error);
}

TEST(GetReindeerPriceTest, LowestPrice) {
    EXPECT_EQ(get_reindeer_price({1, 1, 1, 1}), 2.99);
    EXPECT_EQ(get_reindeer_price({30, 20, 20, 2}), 2.99);
}

TEST(GetReindeerPriceTest, SecondLowestPrice) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({30 + delta, 20, 20, 2}), 4.99);
    EXPECT_EQ(get_reindeer_price({30, 20 + delta, 20, 2}), 4.99);
}
