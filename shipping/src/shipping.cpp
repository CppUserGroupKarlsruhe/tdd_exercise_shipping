#include <shipping/shipping.h>

#include <stdexcept>

namespace shipping {

double get_reindeer_price(double length, double width, double height, double) {
    if (length <= 0) {
        throw std::runtime_error("The parcel must have positive length");
    }
    if (width <= 0) {
        throw std::runtime_error("The parcel must have positive width");
    }
    if (height <= 0) {
        throw std::runtime_error("The parcel must have positive height");
    }
}

}
