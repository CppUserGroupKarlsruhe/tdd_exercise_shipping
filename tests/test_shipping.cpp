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

TEST(ParcelTest, StoresPhysicalDataWithSortedDimensions) {
    parcel const p(2, 1, 3, 4);
    EXPECT_EQ(p.dimensions[0], 3);
    EXPECT_EQ(p.dimensions[1], 2);
    EXPECT_EQ(p.dimensions[2], 1);
    EXPECT_EQ(p.weight, 4);
}

TEST(GetReindeerPriceTest, FailOnParcelTooLarge) {
    EXPECT_THROW(get_reindeer_price({300, 300, 300, 300}), std::runtime_error);
}

TEST(GetReindeerPriceTest, LowestPrice) {
    EXPECT_EQ(get_reindeer_price({1, 1, 1, 1}), 2.99);
    EXPECT_EQ(get_reindeer_price({30, 20, 20, 2}), 2.99);
}

TEST(GetReindeerPriceTest, SecondLowestPriceLowerBound) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({30 + delta, 20, 20, 2}), 4.99);
    EXPECT_EQ(get_reindeer_price({30, 20 + delta, 20, 2}), 4.99);
    EXPECT_EQ(get_reindeer_price({30, 20, 20 + delta, 2}), 4.99);
    EXPECT_EQ(get_reindeer_price({30, 20, 20, 2 + delta}), 4.99);
}

TEST(GetReindeerPriceTest, SecondLowestPriceUpperBound) {
    EXPECT_EQ(get_reindeer_price({40, 30, 20, 4}), 4.99);
}

TEST(GetReindeerPriceTest, SecondLowestPriceWithSwappedDimensions) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({20, 30 + delta, 20, 2}), 4.99);
    EXPECT_EQ(get_reindeer_price({20, 20, 30 + delta, 2}), 4.99);
}

TEST(GetReindeerPriceTest, ThirdLowestPrice) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({60 + delta, 10, 60, 4}), 5.99);
    EXPECT_EQ(get_reindeer_price({60, 10 + delta, 60, 4}), 5.99);
    EXPECT_EQ(get_reindeer_price({60, 10, 60 + delta, 4}), 5.99);
    EXPECT_EQ(get_reindeer_price({60, 10, 60, 4 + delta}), 5.99);
}