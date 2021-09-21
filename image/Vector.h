
#ifndef VECTOR_H
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
    float dot(Vector);
    float norm();
    Vector normalize();

};

#endif