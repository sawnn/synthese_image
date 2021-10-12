#define _USE_MATH_DEFINES
#ifndef VECTOR_H

#include <math.h>
class Vector
{
private:

public:
    float x;
    float y;
    float z;
    Vector(float x = 0, float y = 0, float z = 0);
    Vector operator+(Vector);
    Vector operator-(Vector);
    Vector operator*(float);
    Vector operator/(float);
    Vector cross(Vector);
    float dot(Vector);
    float norm();
    Vector normalize();

};

#endif