#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    HSLAPixel ret;
    ret.h = p.c.color.h; ret.s = p.c.color.s;
    int dist = sqrt( (p.x - p.c.x) * (p.x - p.c.x) + (p.y - p.c.y) * (p.y - p.c.y));
    ret.l = p.c.color.l * pow(fadeFactor, dist);
    return ret;
}
