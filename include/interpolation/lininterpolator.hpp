#ifndef LININTERPOLATOR_H
#define LININTERPOLATOR_H
#pragma once

#include "utils.hpp"
#include "interpolation/interpolator.hpp"

namespace libfp{
namespace interpolation{
class LinearInterpolator : public Interpolator
{
public:
        LinearInterpolator();
         
        unsigned char get_pixel_value(Image, double, double);
};
}
}
#endif /* END OF INCLUDE GUARD */
