#include "solidColorPicker.h"

solidColorPicker::solidColorPicker()
{
/* your code here  :)  */
}

HSLAPixel solidColorPicker::operator()(point p)
{
/* your code here */
    HSLAPixel ret;
    ret.h = p.c.color.h; ret.s = p.c.color.s ; ret.l = p.c.color.l;
    return ret;
}
