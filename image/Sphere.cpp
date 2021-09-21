#include "Rayon.cpp"

class Sphere
{
    private:

    public:
        Sphere(float r, Vector c);
        float rayon;
        Vector centre;
};


Sphere::Sphere(float r, Vector c) 
{
    rayon = r;
    centre = c;
}