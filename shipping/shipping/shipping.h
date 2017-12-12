#pragma once

#include <array>

namespace shipping {

struct parcel {
    parcel(double length, double width, double height, double weight);
    bool fits_into(parcel const & other) const;
    std::array<double, 3> const dimensions;
    double const weight;
};

double get_reindeer_price(parcel const & parcel);

}