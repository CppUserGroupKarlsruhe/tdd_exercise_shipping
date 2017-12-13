#include <shipping/shipping.h>
#include <shipping/data_structures.h>

#include <gtest/gtest.h>

#include <stdexcept>

using shipping::reindeer_prices;
using shipping::fair_and_square_prices;
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
