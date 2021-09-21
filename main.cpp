#include "Vector.h"
#include <iostream>

int main() {
    int time = 0;
    int dt = 1;
    float gravity = 9.8f;
    int mass = 100;
    float coef = 0.37f;
    Vector P = Vector(0, 0, 4000);
    Vector V = Vector(50, 0, 0);


    while (time < 60) {
        Vector A = (Vector(0, 0, 1) * -gravity) - (V * V.norm() * coef) / mass;

        V = V + A * dt;
        P = P + V * dt;

        std::cout << "Time " << time << std::endl;
        std::cout << "Vitesse " << V.x << " " << V.y << " " << V.z << std::endl;
        std::cout << "Acceleration " << A.x << " " << A.y << " " << A.z << std::endl;
        std::cout << "Position " << P.x << " " << P.y << " " << P.z << std::endl;
        time += dt;
    }
}