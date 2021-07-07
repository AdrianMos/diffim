#pragma once
#include "pch.h"

// Marks the pixel red if any r,g,b channel > threshold
// Marks the pixel blue if all r,g,b channels are <= threshold but not (0,0,0)
// If the pixel is (0,0,0), the pixel is not changed.
class ColorizePixelMismatchFunctor {
  private:
	int threshold;

  public:
	ColorizePixelMismatchFunctor(int threshold) : threshold(threshold){};
	void operator()(Pixel& pixel, const int* position) const;
};
