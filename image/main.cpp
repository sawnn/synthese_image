
#include "Triangle.cpp"
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <fstream>

typedef std::tuple<float, Sphere> Tuple;
typedef std::tuple<float, Triangle> TupleTriangle;

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




std::vector<Triangle> getTriangles() {
     std::string line;
     std::ifstream myfile ("cube.off");
     std::vector<Triangle> triangles;
     std::vector<Vector> vertices;
     int nbVertices;
     int nbFacettes;
     getline(myfile,line);
     if (line == "OFF")
        getline(myfile,line);
    size_t pos = 0;
    std::string token;
     int j =0;
    while ((pos = line.find(" ")) != std::string::npos) {
        token = line.substr(0, pos);
        switch (j)
        {
        case 0:
            nbVertices = std::atoi(token.c_str());
            break;
        default:
            break;
        }
        line.erase(0, pos + 1);
        j++;
    }
    
    int i = 0;

   while ( getline(myfile,line) )
    {
        if (line == "OFF")
            continue;
        size_t pos = 0;
        std::string token;
        Triangle triangle = Triangle();
        Vector vec = Vector();
        

        if (i < nbVertices) {
            j =0;
            while ((pos = line.find(" ")) != std::string::npos) {
                token = line.substr(0, pos);
                switch (j)
                {
                case 0:
                    vec.x = std::atoi(token.c_str());
                    break;
                case 1:
                    vec.y = std::atoi(token.c_str());
                    break;
                default:
                    break;
                }
                line.erase(0, pos + 1);
                j++;
            }
            vec.z = std::atoi(line.c_str());
            vertices.push_back(vec);
        } else {
            j = 0;
             while ((pos = line.find(" ")) != std::string::npos) {
                token = line.substr(0, pos);

                switch (j)
                {
                case 1:
                    triangle.v1 = vertices[std::atoi(token.c_str())];
                    break;
                case 2:
                    triangle.v2 = vertices[std::atoi(token.c_str())];
                    break;
                default:
                    break;
                }
                line.erase(0, pos + 1);
                j++;
            }
            triangle.v3 = vertices[std::atoi(line.c_str())];
            triangles.push_back(triangle);
        }
    
        i++;
    }
    myfile.close();
    return triangles;
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

float RayIntersectsTriangle(Rayon rayon,
                           Triangle inTriangle)
{
    const float EPSILON = 0.01;
    Vector vertex0 = inTriangle.v1;
    Vector vertex1 = inTriangle.v2;  
    Vector vertex2 = inTriangle.v3;
    Vector edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = rayon.direction.cross(edge2);
    a = edge1.dot(h);
    if (a > -EPSILON && a < EPSILON)
        return -1;
    f = 1.0/a;
    s = rayon.origin - vertex0;
    u = f * (s.dot(h));
    if (u < 0.0 || u > 1.0)
        return -1;
    q = s.cross(edge1);
    v = f * rayon.direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return -1;
    float t = f * edge2.dot(q);
   // std::cout << "t:" << t << std::endl;
    if (t > 0.01)
        return t;
    else
        return -1;
}

Vector normalTriangle(Triangle triangle) {
    Vector u = triangle.v2 - triangle.v1;
    Vector v = triangle.v3 - triangle.v1;
    return u.cross(v);
}

std::vector<int> getPixelTriangle(float intersection, Rayon rayon, Vector lampe, Vector intensity, Triangle triangle) {

            Vector pointIntersection = rayon.origin + rayon.direction.normalize() * intersection;
            Vector normal = normalTriangle(triangle);
            Vector directionLampe = (lampe - pointIntersection);
            float distance2 = directionLampe.dot(directionLampe);
          //  std::cout << intersection << std::endl;
            Vector light = ( intensity * normal.dot(directionLampe.normalize())) / (M_PI * distance2);
            int pixelXvalue = (int)(light.x * intersection);
            int pixelYvalue = (int)(light.y * intersection);
            int pixelZvalue = (int)(intersection * light.z);
            int i =  pixelXvalue > 255 ? 255 : pixelXvalue;
            int j = pixelYvalue > 255 ? 255 : pixelYvalue;
            int k = pixelZvalue > 255 ? 255 : pixelZvalue;
            return {i, j, k};
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
    for (Sphere& sphere: spheres) {
        float intersection = intersect(rayon, sphere);
        if (intersection >= 0 &&  (intersection < std::get<0>(minimumIntersect) ||std::get<0>(minimumIntersect) == -1)) {
            std::get<0>(minimumIntersect) = intersection;
            std::get<1>(minimumIntersect) = sphere;
        }
    }
    return minimumIntersect;
}

TupleTriangle getMinimumIntersectTriangle(  std::vector<Triangle> triangles, Rayon rayon) {
    TupleTriangle minimumIntersect = { -1 , Triangle(Vector(), Vector(), Vector())};

    for (Triangle& triangle: triangles) {
        float intersection = RayIntersectsTriangle(rayon, triangle);
        if (intersection >= 0 &&  (intersection < std::get<0>(minimumIntersect) ||std::get<0>(minimumIntersect) == -1)) {
            std::get<0>(minimumIntersect) = intersection;
            std::get<1>(minimumIntersect) = triangle;
        }
    }
    return minimumIntersect;
}



int main() {
    int longueur = 200;
    int largeur = 200;
    std::string filename = "image.ppm";
    std::vector<std::vector<std::vector<int>>> image(longueur, std::vector<std::vector<int>>(largeur));
    std::vector<Sphere> spheres = {/*  Sphere(12, Vector(50, 50, 50)), Sphere(500, Vector(50, 590, 100)), 
                                 Sphere(500, Vector(590, 50, 100)), Sphere(500, Vector(50, -490, 100)), Sphere(500, Vector(-490, 50, 100))*/};
    std::vector<Triangle> triangles = getTriangles();
    Vector lampe = Vector(25,25, -5000);
    Vector intensity = Vector(30000, 30000, 0);
   // std::cout << triangles.size();

    /*for (Triangle triangle: triangles) {
        std::cout <<triangle.v1.x << triangle.v1.y << triangle.v1.z << std::endl;
        std::cout <<triangle.v2.x << triangle.v2.y << triangle.v2.z << std::endl;
        std::cout <<triangle.v3.x << triangle.v3.y << triangle.v3.z << std::endl;
        std::cout << "\n";
    }*/


    for (int y = 0; y < largeur; y++) {
        int profondeur = 1;
        for (int x = 0; x < longueur; x++) {
            Rayon rayon = Rayon(Vector(y, x, -50), Vector(0, 0, 1));
            Tuple intersection = getMinimumIntersect(spheres, x, y, rayon);
            TupleTriangle intersectionTriangle = getMinimumIntersectTriangle(triangles, rayon);
            if (std::get<0>(intersection) >= 0 && (std::get<0>(intersection) <= std::get<0>(intersectionTriangle) || std::get<0>(intersectionTriangle) < 0)) {
                std::vector<int> pixel = getPixel(std::get<0>(intersection), rayon, lampe, intensity, std::get<1>(intersection));
                image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
            } else if (std::get<0>(intersectionTriangle) >= 0) {
                std::vector<int> pixel = getPixelTriangle(std::get<0>(intersectionTriangle), rayon, lampe, intensity, std::get<1>(intersectionTriangle));
                image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
            }
            else {
                std::vector<int> pixel = {255, 0, 0};
                image[y][x].insert(image[y][x].begin(), pixel.begin(), pixel.end());
            }


        }
    }
    CreateImage(longueur, largeur, image, filename);
}







