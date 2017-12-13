#pragma once

#include <shipping/data_structures.h>

namespace shipping {

extern pricelist const reindeer_prices;
extern pricelist const fair_and_square_prices;

double get_best_price(parcel const & parcel, pricelist const & tariffs);
double get_best_price(parcel const & parcel, std::vector<pricelist> const & carriers);

}