#include <shipping/shipping.h>
#include <shipping/data_structures.h>

#include <gtest/gtest.h>

#include <stdexcept>

using shipping::get_reindeer_price;
using shipping::get_best_price;
using shipping::parcel;

TEST(GetBestPrice, FailOnNoSuitableTariff) {
    parcel const p(1, 2, 3, 4);
    shipping::tariff const unsuitable_tariff({1, 1, 1, 1}, 1);

    EXPECT_THROW(get_best_price(p, shipping::pricelist({})), std::runtime_error);
    EXPECT_THROW(get_best_price(p, shipping::pricelist({unsuitable_tariff})), std::runtime_error);
}

TEST(GetBestPrice, PickCheapestMatchingTariff) {
    parcel const p(1, 2, 3, 4);
    shipping::tariff const cheapest({10, 10, 10, 10}, 1);
    shipping::tariff const more_expensive({10, 10, 10, 10}, 2);

    EXPECT_EQ(get_best_price(p, shipping::pricelist({more_expensive, cheapest})), cheapest.get_price());
}

TEST(GetReindeerPriceTest, FailOnParcelTooLarge) {
    double const delta = 0.01;
    EXPECT_THROW(get_reindeer_price({120 + delta, 60, 60, 30}), std::runtime_error);
    EXPECT_THROW(get_reindeer_price({120, 60 + delta, 60, 30}), std::runtime_error);
    EXPECT_THROW(get_reindeer_price({120, 60, 60, 30 + delta}), std::runtime_error);
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
    EXPECT_EQ(get_reindeer_price({40, 30, 20, 5}), 4.99);
}

TEST(GetReindeerPriceTest, SecondLowestPriceWithSwappedDimensions) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({20, 30 + delta, 20, 2}), 4.99);
    EXPECT_EQ(get_reindeer_price({20, 20, 30 + delta, 2}), 4.99);
}

TEST(GetReindeerPriceTest, ThirdLowestPriceLowerBound) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({40 + delta, 10, 20, 4}), 5.99);
    EXPECT_EQ(get_reindeer_price({40, 30 + delta, 10, 4}), 5.99);
}

TEST(GetReindeerPriceTest, ThirdLowestPriceUpperBound) {
    EXPECT_EQ(get_reindeer_price({60, 10, 60, 4}), 5.99);
}

TEST(GetReindeerPriceTest, LargestPriceLowerBound) {
    double const delta = 0.01;
    EXPECT_EQ(get_reindeer_price({60 + delta, 10, 60, 4}), 14.99);
    EXPECT_EQ(get_reindeer_price({60, 10 + delta, 60, 4}), 14.99);
    EXPECT_EQ(get_reindeer_price({60, 10, 60 , 4 + delta}), 14.99);
    EXPECT_EQ(get_reindeer_price({40 + delta, 30, 20, 5}), 14.99);
    EXPECT_EQ(get_reindeer_price({40, 30 + delta, 20, 5}), 14.99);
    EXPECT_EQ(get_reindeer_price({40, 30, 20 + delta, 5}), 14.99);
    EXPECT_EQ(get_reindeer_price({40, 30, 20, 5 + delta}), 14.99);
}

TEST(GetReindeerPriceTest, LargestPriceUpperBound) {
    EXPECT_EQ(get_reindeer_price({120, 60, 60, 30}), 14.99);
}