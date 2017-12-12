#pragma once

#include <array>
#include <vector>

namespace shipping {

class parcel {
public:
    parcel(double length, double width, double height, double weight);
    bool fits_into(parcel const & other) const;
private:
    std::array<double, 3> dimensions;
    double weight;
};

struct tariff {
public:
    tariff(parcel upper_limit, double price);
    bool available_for(parcel const & other) const;
    double get_price() const;
private:
    parcel upper_limit;
    double price;
};

struct pricelist {
    pricelist(std::vector<tariff> tariffs);
    std::vector<tariff> const tariffs;
};

}