
#include "Sphere.cpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>



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

int main() {
    int longueur = 100;
    int largeur = 100;
    std::string filename = "image.ppm";
    std::vector<std::vector<std::vector<int>>> image(longueur, std::vector<std::vector<int>>(largeur));
    Sphere sphere =  Sphere(25, Vector(50, 50, 50));

    for (int y = 0; y < largeur; y++) {
        int profondeur = 1;
        for (int x = 0; x < longueur; x++) {
                float intersection = intersect(Rayon(Vector(y, x, 0), Vector(0, 0, 1)), sphere);
                if (intersection >= 0) {
                    std::cout<< profondeur<< std::endl;
                    std::vector<int> pixel = {(int)(4 * intersection), (int)(4 * intersection), (int)(4 * intersection)};
                    image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
                        profondeur += 1;
                } else {
                    std::vector<int> pixel = {255, 0, 0};
                    image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
                }
        }
 
    }

    CreateImage(longueur, largeur, image, filename);
    
}



