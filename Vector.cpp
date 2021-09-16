#include <cmath>
#include "Vector.h"


Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

 Vector::Vector()
{
}
   

Vector Vector::operator+(Vector vec) {
    return Vector(vec.x + x, vec.y + y, vec.z + z);
}

Vector Vector::operator-(Vector vec) {
    return Vector(vec.x - x, vec.y - y, vec.z - z);
}

Vector Vector::operator*(float multiple) {
    return Vector(x * multiple, y * multiple, z * multiple);
}

Vector Vector::operator/(float div) {
    return Vector(x / div, y / div, z / div);
}

float Vector::dot(Vector vec) {
    return ((x * vec.x) + (y * vec.y) + (z * vec.z));
}

float Vector::norm() {
    return sqrt((x * x) + (y * y) + (z * z));
}

Vector Vector::normalize() {
    return Vector(x / norm(), y / norm(), z / norm());
}



Vector::~Vector()
{
}