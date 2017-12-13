#pragma once

#include <shipping/data_structures.h>

namespace shipping {

extern pricelist const reindeer_prices;

double get_best_price(parcel const & parcel, pricelist const & tariffs);

}