#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H
#pragma once

#include "utils.hpp"

namespace libfp{
namespace interpolation{
enum interpolationType { INTERPOLATION_BILINEAR };

class Interpolator
{
public:
        virtual unsigned char get_pixel_value(Image, double, double) = 0;
};
}
}
#endif 
