#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include <math.h>
#include <stdlib.h>

typedef struct {
    double Lon;
    double Lat;
}Coordinates;

Coordinates wgs84_to_gcj02(Coordinates gps);
Coordinates gcj02_to_bd09(Coordinates gg);

#endif
