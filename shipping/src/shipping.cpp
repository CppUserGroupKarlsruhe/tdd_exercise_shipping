#include <shipping/shipping.h>

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

bool parcel::fits_into(parcel const & other) const
{
    return (dimensions[0] <= other.dimensions[0]) and (dimensions[1] <= other.dimensions[1]) and (dimensions[2] <= other.dimensions[2]);
}


double get_reindeer_price(parcel const & parcel)
{
    if (parcel.dimensions[0] > 41) {
        throw std::runtime_error("The parcel is too large");
    }
    if ((parcel.dimensions[0] > 40) or (parcel.dimensions[1] > 30) or (parcel.dimensions[2] > 20) or (parcel.weight > 4)) {
        return 5.99;
    }
    if ((parcel.dimensions[0] > 30) or (parcel.dimensions[1] > 20) or (parcel.dimensions[2] > 20) or (parcel.weight > 2)) {
        return 4.99;
    }

    return 2.99;
}

}
