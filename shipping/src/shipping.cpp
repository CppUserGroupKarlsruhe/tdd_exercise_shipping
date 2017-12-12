#include <shipping/shipping.h>

#include <stdexcept>

namespace shipping {

double get_reindeer_price(parcel const & p)
{
    if (p.fits_into(parcel{30, 20, 20, 2})) {
        return 2.99;
    }
    if (p.fits_into(parcel{40, 30, 20, 5})) {
        return 4.99;
    }
    if (p.fits_into(parcel{60, 10, 60, 4})) {
        return 5.99;
    }
    if (p.fits_into(parcel{120, 60, 60, 30})) {
        return 14.99;
    }
    throw std::runtime_error("The parcel is too large");
}

}
