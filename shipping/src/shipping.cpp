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

pricelist const reindeer_prices({{{30, 20, 20, 2}, 2.99},
                                 {{40, 30, 20, 5}, 4.99},
                                 {{60, 10, 60, 4}, 5.99},
                                 {{120, 60, 60, 30}, 14.99}});

double get_reindeer_price(parcel const & p)
{
    return get_best_price(p, reindeer_prices);
}

}
