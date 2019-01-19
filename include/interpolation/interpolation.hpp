#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include "interpolation/interpolator.hpp"
#include "interpolation/lininterpolator.hpp"
#include "interpolation/lancinterpolator.hpp"

namespace libfp{
namespace interpolation{
enum interpolationType { INTERPOLATION_BILINEAR,  INTERPOLATION_LANCZOS2, INTERPOLATION_LANCZOS3, INTERPOLATION_LANCZOS4 };
}
}
#endif
