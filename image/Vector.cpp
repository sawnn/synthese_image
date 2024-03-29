#include <cmath>
#include "Vector.h"
#include <iostream>


Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
   

Vector Vector::operator+(Vector vec) {
    return Vector(vec.x + x, vec.y + y, vec.z + z);
}

Vector Vector::operator-(Vector vec) {
    return Vector(x - vec.x, y - vec.y, z - vec.z);
}

Vector Vector::operator*(float multiple) {
    return Vector(x * multiple, y * multiple, z * multiple);
}

Vector Vector::operator/(float div) {
    return Vector(x / div, y / div, z / div);
}

Vector Vector::cross(Vector vec) {
    return Vector((y * vec.z - z * vec.y), (z * vec.x - x * vec.z), (x * vec.y - y * vec.x));
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

