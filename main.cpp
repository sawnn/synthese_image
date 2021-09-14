#include <fstream>
#include <iterator>
#include <Magick++.h> 
#include <vector>
#include <iostream>


int main() {
       std::ifstream file ("C:\\Users\\ddoughan\\Documents\\Prog\\random-grid.jpg", std::ios::binary);

    std::istream_iterator<unsigned char> begin(file), end; 

    std::vector<unsigned int> buffer(begin,end); 

    for(int i=0;i<buffer.size();i++){
          std::cout<<buffer[i];
    }
     
     

       Image image; 
   image.read(2,3,"RGB",CharPixel,pix);
      image.write("result.png"); 

}