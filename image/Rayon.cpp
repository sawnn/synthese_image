#include "Vector.h"

class Rayon
{
    private:

    public:
    Rayon(Vector o = Vector(), Vector d = Vector());
    Vector origin;
    Vector direction;
};

Rayon::Rayon(Vector o, Vector d)
{
    this->origin = o;
    this->direction = d;
}