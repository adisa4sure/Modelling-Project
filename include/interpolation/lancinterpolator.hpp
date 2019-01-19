#ifndef LANCINTERPOLATOR_H
#define LANCTERPOLATOR_H
#pragma once

#include "utils.hpp"
#include "interpolation/interpolator.hpp"

namespace libfp{
namespace interpolation{
class LanczosInterpolator : public Interpolator
{
public:
        LanczosInterpolator(int a);
         
        unsigned char get_pixel_value(Image, double, double);
private:
        int a; // Kernel size
};
}
}
#endif /* END OF INCLUDE GUARD */
