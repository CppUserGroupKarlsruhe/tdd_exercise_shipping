#include <shipping/shipping.h>
#include <shipping/data_structures.h>

#include <gtest/gtest.h>

#include <stdexcept>

using shipping::reindeer_prices;
using shipping::fair_and_square_prices;
using shipping::get_best_price;
using shipping::parcel;
using shipping::tariff;
using shipping::pricelist;

TEST(GetBestPrice, FailOnNoSuitableTariff) {
    parcel const p(1, 2, 3, 4);
    tariff const unsuitable_tariff({1, 1, 1, 1}, 1);

    EXPECT_THROW(get_best_price(p, pricelist({})), std::runtime_error);
    EXPECT_THROW(get_best_price(p, pricelist({unsuitable_tariff})), std::runtime_error);
}

TEST(GetBestPrice, PickCheapestMatchingTariff) {
    parcel const p(1, 2, 3, 4);
    tariff const cheapest({10, 10, 10, 10}, 1);
    tariff const more_expensive({10, 10, 10, 10}, 2);

    EXPECT_EQ(get_best_price(p, pricelist({more_expensive, cheapest})), cheapest.get_price());
}

TEST(GetBestPriceAmongMultipleCarriers, NoCarrier)
{
    parcel const p(1, 2, 3, 4);
    EXPECT_THROW(get_best_price(p, {}), std::runtime_error);
}

TEST(GetBestPriceAmongMultipleCarriers, NoMatchingCarrier)
{
    parcel const p(1, 2, 3, 4);
    pricelist const unsuitable_carrier({{{1, 1, 1, 1}, 1}});
    EXPECT_THROW(get_best_price(p, {unsuitable_carrier, unsuitable_carrier}), std::runtime_error);
}

TEST(GetBestPriceAmongMultipleCarriers, SoleMatchingCarrier)
{
    parcel const p(1, 2, 3, 4);
    double const expected_price = 123;
    pricelist const unsuitable_carrier({{{1, 1, 1, 1}, 1}});
    pricelist const carrier({{{10, 10, 10, 10}, expected_price}});
    EXPECT_EQ(get_best_price(p, {unsuitable_carrier, carrier, unsuitable_carrier}), expected_price);
}

TEST(GetBestPriceAmongMultipleCarriers, MultipleMatchingCarriers)
{
    parcel const p(1, 2, 3, 4);
    double const best_price = 1;
    pricelist const best_carrier({{p, best_price}});
    pricelist const other_carrier({{p, best_price * 2}});
    EXPECT_EQ(get_best_price(p, {other_carrier, best_carrier, other_carrier}), best_price);
}

TEST(ReindeerPricesTest, UnsupportedParcels) {
    double const delta = 0.01;
    EXPECT_THROW(get_best_price({120 + delta, 60, 60, 30}, reindeer_prices), std::runtime_error);
    EXPECT_THROW(get_best_price({120, 60 + delta, 60, 30}, reindeer_prices), std::runtime_error);
    EXPECT_THROW(get_best_price({120, 60, 60, 30 + delta}, reindeer_prices), std::runtime_error);
}

TEST(ReindeerPricesTest, SupportedParcels) {
    double const delta = 0.01;
    std::vector<std::pair<parcel, double>> expectations = {
        {{1, 1, 1, 1}, 2.99},
        {{30, 20, 20, 2}, 2.99},

        {{30 + delta, 20, 20, 2}, 4.99},
        {{30, 20 + delta, 20, 2}, 4.99},
        {{30, 20, 20 + delta, 2}, 4.99},
        {{30, 20, 20, 2 + delta}, 4.99},
        {{40, 30, 20, 5}, 4.99},

        {{40 + delta, 10, 20, 4}, 5.99},
        {{40, 30 + delta, 10, 4}, 5.99},
        {{60, 10, 60, 4}, 5.99},

        {{60 + delta, 10, 60, 4}, 14.99},
        {{60, 10 + delta, 60, 4}, 14.99},
        {{60, 10, 60, 4 + delta}, 14.99},
        {{40 + delta, 30, 20, 5}, 14.99},
        {{40, 30 + delta, 20, 5}, 14.99},
        {{40, 30, 20 + delta, 5}, 14.99},
        {{40, 30, 20, 5 + delta}, 14.99},
        {{120, 60, 60, 30}, 14.99}
    };

    for (auto const & expectation : expectations) {
        auto const & parcel = expectation.first;
        auto const expected_price = expectation.second;
        EXPECT_EQ(get_best_price(parcel, reindeer_prices), expected_price);
    }
}

TEST(FairAndSquarePricesTest, UnsupportedParcels) {
    double const delta = 0.01;
    EXPECT_THROW(get_best_price({100 + delta, 100, 100, 75}, fair_and_square_prices), std::runtime_error);
    EXPECT_THROW(get_best_price({100, 100, 100, 75 + delta}, fair_and_square_prices), std::runtime_error);
}

TEST(FairAndSquarePricesTest, SupportedParcels) {
    double const delta = 0.01;
    std::vector<std::pair<parcel, double>> expectations = {
        {{1, 1, 1, 1}, 2.25},
        {{15, 15, 15, 1.5}, 2.25},

        {{15 + delta, 15, 15, 1.5}, 3.24},
        {{15, 15, 15, 1.5 + delta}, 3.24},
        {{25, 25, 25, 2.5}, 3.24},

        {{25 + delta, 25, 25, 2.5}, 4},
        {{25, 25, 25, 2.5 + delta}, 4},
        {{35, 35, 35, 5}, 4},

        {{35 + delta, 35, 35, 5}, 56.25},
        {{35, 35, 35, 5 + delta}, 56.25},
        {{100, 100, 100, 75}, 56.25}
    };

    for (auto const & expectation : expectations) {
        auto const & parcel = expectation.first;
        auto const expected_price = expectation.second;
        EXPECT_EQ(get_best_price(parcel, fair_and_square_prices), expected_price);
    }
}
