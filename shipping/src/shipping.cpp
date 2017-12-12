#include <shipping/shipping.h>

#include <stdexcept>

namespace shipping {

pricelist const reindeer_prices({{{30, 20, 20, 2}, 2.99},
                                 {{40, 30, 20, 5}, 4.99},
                                 {{60, 10, 60, 4}, 5.99},
                                 {{120, 60, 60, 30}, 14.99}});

double get_reindeer_price(parcel const & p)
{
    for (auto const & tariff : reindeer_prices.tariffs) {
        if (tariff.available_for(p)) {
            return tariff.get_price();
        }
    }
    throw std::runtime_error("The parcel is too large");
}

}
