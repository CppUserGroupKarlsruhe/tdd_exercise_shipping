#pragma once

#include <array>
#include <vector>

namespace shipping {

struct parcel {
    parcel(double length, double width, double height, double weight);
    bool fits_into(parcel const & other) const;
    std::array<double, 3> const dimensions;
    double const weight;
};

struct tariff {
    tariff(parcel upper_limit, double price);
    parcel upper_limit;
    double const price;
};

struct pricelist {
    pricelist(std::vector<tariff> tariffs);
    std::vector<tariff> const tariffs;
};

}