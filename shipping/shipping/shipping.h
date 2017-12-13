#pragma once

#include <shipping/data_structures.h>

namespace shipping {

double get_best_price(parcel const & parcel, pricelist const & tariffs);

double get_reindeer_price(parcel const & parcel);

}