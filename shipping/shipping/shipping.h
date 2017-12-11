#pragma once

namespace shipping {

struct parcel {
    parcel(double length, double width, double height, double weight);
};

double get_reindeer_price(parcel const & parcel);

}