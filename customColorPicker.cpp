#include "CustomColorPicker.h"

CustomColorPicker::CustomColorPicker()
{
/* your code here  :)  */
}

HSLAPixel CustomColorPicker::operator()(point p)
{
/* your code here */
    HSLAPixel ret;
    int dist = sqrt( (p.x - p.c.x) * (p.x - p.c.x) + (p.y - p.c.y) * (p.y - p.c.y));
    ret.h = dist * p.c.color.h; 
    ret.s = dist * p.c.color.s;
    ret.l = dist * p.c.color.l;
    return ret;
}