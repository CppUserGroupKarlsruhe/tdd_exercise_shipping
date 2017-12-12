#include <shipping/data_structures.h>

#include <stdexcept>
#include <algorithm>
#include <functional>

namespace {

void check_physical_attributes(double length, double width, double height, double weight)
{
    if (length <= 0) {
        throw std::runtime_error("The parcel must have positive length");
    }
    if (width <= 0) {
        throw std::runtime_error("The parcel must have positive width");
    }
    if (height <= 0) {
        throw std::runtime_error("The parcel must have positive height");
    }
    if (weight <= 0) {
        throw std::runtime_error("The parcel must have positive weight");
    }
}

std::array<double, 3> sorted(double x, double y, double z)
{
    std::array<double, 3> dimensions = {{x, y, z}};
    std::sort(dimensions.begin(), dimensions.end(), std::greater<double>());
    return dimensions;
};

}

namespace shipping {

parcel::parcel(double length, double width, double height, double weight) :
    dimensions(sorted(length, width, height)),
    weight(weight)
{
    check_physical_attributes(length, width, height, weight);
}

bool parcel::fits_into(parcel const &other) const
{
    return (dimensions[0] <= other.dimensions[0])
           and (dimensions[1] <= other.dimensions[1])
           and (dimensions[2] <= other.dimensions[2])
           and (weight <= other.weight);
}

tariff::tariff(parcel upper_limit, double price) :
    upper_limit(upper_limit),
    price(price)
{
    if (price <= 0) {
        throw std::runtime_error("Price must be a positive number");
    }
}


}