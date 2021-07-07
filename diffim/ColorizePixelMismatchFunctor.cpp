#include "pch.h"
#include "ColorizePixelMismatchFunctor.h"


void ColorizePixelMismatchFunctor::operator()(Pixel& pixel,
                                              const int* position) const
{
    // x, y, z are the color channels
    const bool identical = pixel.x + pixel.y + pixel.z == 0;
    const bool below_threshold = (pixel.x <= threshold) && (pixel.y <= threshold)
                                 && (pixel.z <= threshold);

    if (identical)
        return;

    if (below_threshold) {
        pixel = Pixel(255, 0, 0);  // blue
    }
    else {
        pixel = Pixel(0, 0, 255);  // red
    }
}