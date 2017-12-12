#include <shipping/data_structures.h>

#include <gtest/gtest.h>

#include <stdexcept>

using shipping::parcel;
using shipping::tariff;

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

TEST(ParcelTest, FitsInto) {
    parcel const p(1, 2, 3, 4);
    double const delta = 0.01;

    EXPECT_TRUE(p.fits_into(p));
    EXPECT_TRUE(p.fits_into(parcel{1 + delta, 2, 3, 4}));
    EXPECT_TRUE(p.fits_into(parcel{1, 2 + delta, 3, 4}));
    EXPECT_TRUE(p.fits_into(parcel{1, 2, 3 + delta, 4}));
    EXPECT_TRUE(p.fits_into(parcel{1, 2, 3, 4 + delta}));

    EXPECT_FALSE(p.fits_into(parcel{1 - delta, 2, 3, 4}));
    EXPECT_FALSE(p.fits_into(parcel{1, 2 - delta, 3, 4}));
    EXPECT_FALSE(p.fits_into(parcel{1, 2, 3 - delta, 4}));
    EXPECT_FALSE(p.fits_into(parcel{1, 2, 3, 4 - delta}));
}


TEST(TariffTest, FailOnNonPositivePrice) {
    EXPECT_THROW(tariff(parcel(1, 2, 3, 4), -1.2), std::runtime_error);
    EXPECT_THROW(tariff(parcel(1, 2, 3, 4), 0), std::runtime_error);
}

TEST(TariffTest, ConstructorProperties) {
    parcel const upper_limit(1, 2, 3, 4);
    double const expected_price = 5;

    tariff t(upper_limit, expected_price);
    EXPECT_EQ(t.upper_limit.weight, upper_limit.weight);
    EXPECT_EQ(t.price, expected_price);
}