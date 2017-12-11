#pragma once

namespace shipping {

struct parcel {
    parcel(double length, double width, double height, double weight);
    double const length;
    double const width;
    double const height;
    double const weight;
};

double get_reindeer_price(parcel const & parcel);

}