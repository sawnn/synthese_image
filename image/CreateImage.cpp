#include <vector>
#include <fstream>
#include <string>
#include <iostream>


void CreateImage(int longeur, int largeur, std::vector<std::vector<std::vector<int>>> imageVec, std::string filename) {
    std::ofstream file;

    file.open(filename);
    std::string image = "P3\n" + std::to_string(longeur) + " " + std::to_string(largeur) + "\n255\n";

    for (int y = 0; y < largeur; y++) {
        for (int x = 0; x < longeur; x++) {
            std::cout << "here" << std::endl;
            image = image + std::to_string(imageVec[y][x][0]) + " " + std::to_string(imageVec[y][x][1]) + " " + std::to_string(imageVec[y][x][2]) + "\t\t";
        }
        image = image + "\n";
    }
    
    file << image;
    file.close();
}



/*int main() {
    std::vector<std::vector<std::vector<int>>> image = {{{255, 0, 0}, {0, 255, 0}, {0, 0, 255}},
                                                         {{255, 255, 0}, {255, 255, 255}, {0, 0, 0}}};

    CreateImage(3, 2, image, "image.ppm");
}*/
