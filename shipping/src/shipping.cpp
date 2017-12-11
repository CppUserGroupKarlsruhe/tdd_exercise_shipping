#include <shipping/shipping.h>

#include <stdexcept>

namespace shipping {

double get_reindeer_price(double length, double width, double, double) {
    if (length <= 0) {
        throw std::runtime_error("The parcel must have positive length");
    }
    if (width < 0) {
        throw std::runtime_error("The parcel must not have negative width");
    }
}

}
