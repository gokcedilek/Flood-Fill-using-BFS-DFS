#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"
#include "point.h"
#include "center.h"

class CustomColorPicker : public colorPicker
{
  public:
    CustomColorPicker();
    virtual HSLAPixel operator()(point p);

};

#endif