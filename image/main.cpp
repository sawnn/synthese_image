
#include "Sphere.cpp"
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <fstream>

typedef std::tuple<float, Sphere> Tuple;

void CreateImage(int longeur, int largeur, std::vector<std::vector<std::vector<int>>> imageVec, std::string filename) {
    std::ofstream file;

    file.open(filename);
    std::string image = "P3\n" + std::to_string(longeur) + " " + std::to_string(largeur) + "\n255\n";

    for (int y = 0; y < largeur; y++) {
        for (int x = 0; x < longeur; x++) {
            image = image + std::to_string(imageVec[y][x][0]) + " " + std::to_string(imageVec[y][x][1]) + " " + std::to_string(imageVec[y][x][2]) + "\t\t";
        }
        image = image + "\n";
    }
    
    file << image;
    file.close();
}

float intersect(Rayon r, Sphere s) 
{
    float A = r.direction.dot(r.direction);
    float B = (r.origin - s.centre).dot(r.direction) * 2;
    float C = ((r.origin - s.centre).dot((r.origin - s.centre))) - (s.rayon * s.rayon);
    float delta = (B * B) - 4 * A * C;
    float positive = (-B + sqrt(delta)) / (2 * A);
    float negative = (-B - sqrt(delta)) / (2 * A);
    if (negative >= 0) return negative;
    if (positive >= 0) return positive;

    else return -1;
}

std::vector<int> getPixel(float intersection, Rayon rayon, Vector lampe, Vector intensity, Sphere sphere) {

            Vector pointIntersection = rayon.origin + rayon.direction.normalize() * intersection;
            Vector normal = (pointIntersection - sphere.centre).normalize();
            Vector directionLampe = (lampe - pointIntersection);
            float distance2 = directionLampe.dot(directionLampe);

            Vector light = ( intensity * normal.dot(directionLampe.normalize())) / (M_PI * distance2);
            int pixelXvalue = (int)(light.x * intersection);
            int pixelYvalue = (int)(light.y * intersection);
            int pixelZvalue = (int)(intersection * light.z);
            int i =  pixelXvalue > 255 ? 255 : pixelXvalue;
            int j = pixelYvalue > 255 ? 255 : pixelYvalue;
            int k = pixelZvalue > 255 ? 255 : pixelZvalue;
            return {i, j, k};
}

Tuple getMinimumIntersect(std::vector<Sphere> spheres, int x, int y, Rayon rayon) {
    Tuple minimumIntersect = { -1, Sphere(0, 0)};
    for (Sphere sphere: spheres) {
        float intersection = intersect(rayon, sphere);
        if (intersection >= 0 &&  (intersection < std::get<0>(minimumIntersect) ||std::get<0>(minimumIntersect) == -1)) {
            std::get<0>(minimumIntersect) = intersection;
            std::get<1>(minimumIntersect) = sphere;
        }
    }
    return minimumIntersect;
}

int main() {
    int longueur = 100;
    int largeur = 100;
    std::string filename = "image.ppm";
    std::vector<std::vector<std::vector<int>>> image(longueur, std::vector<std::vector<int>>(largeur));
    std::vector<Sphere> spheres = { Sphere(12, Vector(50, 50, 50)), Sphere(500, Vector(50, 590, 100)), 
                                 Sphere(500, Vector(590, 50, 100)), Sphere(500, Vector(50, -490, 100)), Sphere(500, Vector(-490, 50, 100))};
    Vector lampe = Vector(25,25, 50);
    Vector intensity = Vector(30000, 30000, 0);
    for (int y = 0; y < largeur; y++) {
        int profondeur = 1;
        for (int x = 0; x < longueur; x++) {
            Rayon rayon = Rayon(Vector(y, x, 0), Vector(0, 0, 1));
            Tuple intersection = getMinimumIntersect(spheres, x, y, rayon);
            if (std::get<0>(intersection) >= 0) {
                std::vector<int> pixel = getPixel(std::get<0>(intersection), rayon, lampe, intensity, std::get<1>(intersection));
                image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
            } else {
                std::vector<int> pixel = {255, 0, 0};
                image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
            }


        }
    }

    CreateImage(longueur, largeur, image, filename);



}





