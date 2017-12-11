#include <shipping/shipping.h>

#include <stdexcept>

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

}

namespace shipping {

parcel::parcel(double length, double width, double height, double weight) :
    length(length),
    width(width),
    height(height),
    weight(weight)
{
    check_physical_attributes(length, width, height, weight);
}


double get_reindeer_price(parcel const & parcel) {
//    if (width > 30) {
//        throw std::runtime_error("The parcel is too large");
//    }
    return 2.99;
}

}
