
#include "Sphere.cpp"
#include <iostream>

class Triangle
{
    private:

    public:
        Triangle(Vector p1 = Vector(), Vector p2 = Vector(), Vector p3 = Vector());
        Vector v1;
        Vector v2;
        Vector v3;



};

Triangle::Triangle(Vector p1, Vector p2, Vector p3) 
{
v1 = p1;
v2 = p2;
v3 = p3; 
}