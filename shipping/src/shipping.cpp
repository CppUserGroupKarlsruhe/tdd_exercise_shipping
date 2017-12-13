#include <shipping/shipping.h>

#include <stdexcept>

namespace shipping {

double get_best_price(parcel const & parcel, pricelist const & tariffs)
{
    for (auto const & tariff : tariffs.tariffs) {
        if (tariff.available_for(parcel)) {
            return tariff.get_price();
        }
    }
    throw std::runtime_error("No suitable tariff found for parcel");
}

double get_best_price(parcel const & parcel, std::vector<pricelist> const & carriers)
{
    for (auto const & carrier : carriers) {
        try {
            return get_best_price(parcel, carrier);
        } catch (std::runtime_error const &) {}
    }

    throw std::runtime_error("No suitable carrier found for parcel");
}

pricelist const reindeer_prices({{{30, 20, 20, 2}, 2.99},
                                 {{40, 30, 20, 5}, 4.99},
                                 {{60, 10, 60, 4}, 5.99},
                                 {{120, 60, 60, 30}, 14.99}});

pricelist const fair_and_square_prices({{{15, 15, 15, 1.5}, 2.25},
                                        {{25, 25, 25, 2.5}, 3.24},
                                        {{35, 35, 35, 5}, 4.00},
                                        {{100, 100, 100, 75}, 56.25}});

}

