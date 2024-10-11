#include "image/image.hpp"
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstring>
#include <memory>

namespace image{

    Image::Image(): width(0), height(0), th_value(120), data(nullptr){

    }

    Image::Image(int w, int h): width(w), height(h), th_value(120),  data(nullptr){

    }

    Image::Image(int w, int h, uchar* _data): width(w), height(h), th_value(120), data(_data){
       threshold();
    }

    void Image::threshold(){
        if (data != nullptr) {
            for(int i = 0; i < height*width; i++){            
                if (static_cast<int>(data[i]) < th_value){
                    data[i] = static_cast<char>(0);
                }
                else{
                    data[i] = static_cast<char>(1);                    
                }
            }
        }
    }
    int Image::getValue(int row, int col){
        int pos = row*width + col;
        return static_cast<int>(data[pos]);
    }

    void Image::show(){
        std::cout << "----------------------" << std::endl;
        std::cout << "size [ (w: " << width << ") x   ( h:" << height << ")]" <<  std::endl;        
        std::cout << "---------------------" << std::endl;
        for(int i = 0 ; i < height ; i++ ){
            for(int j = 0; j < width; j++ ){
                //std::cout<< getValue(i,j) << " "; 
                if (getValue(i,j) == 0) {
                    std::cout<<" ";
                }
                else{
                    std::cout<<"*";
                }
            }
            std::cout<<std::endl;
        }
    }
    std::list<std::shared_ptr<Region>> Image::getRegions() {
        std::list<std::shared_ptr<Region>> regions;
        bool* visited = new bool[width * height](); // Inicializamos un array de booleanos para marcar los píxeles visitados

        int currentRegionId = 1;

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                // Verificamos si el píxel pertenece a un objeto (valor 1) y si no ha sido visitado
                if (data[row * width + col] == 1 && !visited[row * width + col]) {
                    // Nueva región encontrada
                    std::shared_ptr<Region> region = std::make_shared<Region>();
                    region->setId(currentRegionId++);
                    exploreRegion(row, col, visited, *region);
                    regions.push_back(region);
                }
            }
        }

        delete[] visited; // Liberamos la memoria usada para el array de booleanos
        return regions;
    }

    // Método auxiliar para explorar una región
    void Image::exploreRegion(int row, int col, bool* visited, Region& region) {
        // Verificamos si la posición está fuera de los límites de la imagen
        if (row < 0 || col < 0 || row >= height || col >= width) return;

        // Si el píxel ya ha sido visitado o no pertenece a un objeto, retornamos
        if (data[row * width + col] == 0 || visited[row * width + col]) return;

        // Marcamos el píxel como visitado
        visited[row * width + col] = true;

        // Añadimos el punto a la región
        region.addPoint(Point2D(col, row));

        // Exploramos los píxeles vecinos (arriba, abajo, izquierda, derecha)
        exploreRegion(row - 1, col, visited, region);
        exploreRegion(row + 1, col, visited, region);
        exploreRegion(row, col - 1, visited, region);
        exploreRegion(row, col + 1, visited, region);
    }

    Image::~Image(){

    }

    Image* Image::readImage(std::string &path){

        Image* im = nullptr;
        std::ifstream fin(path, std::ios::binary);
        char info[54];
        // read the 54-byte header
        fin.read(info, 54);
        // extract image height and width from header
        int width = *(int*)&info[18];
        int height = *(int*)&info[22];
        short int planes = *(short int*)&info[26];
        short int bits = *(short int*)&info[28];
        int imagesize = *(int*)&info[34];
        int numcolors = *(int*)&info[46];
        assert(info[0]=='B' && info[1] =='M');
        assert(bits == 8);
        // std::cout<< "planes " << planes << std::endl;
        // std::cout<< "bits " << bits << std::endl;
        // std::cout<< "imagesize " << imagesize << std::endl;
        // std::cout<< "numcolors " << numcolors << std::endl;
        // std::cout<< info[0] << info[1] << std::endl;
        //reading colortable
        char  colors[numcolors*4];
        fin.read(colors, numcolors*4);        
        if (imagesize == height * width) {            
            char* data = new char[imagesize];
            //read the pixel values
            fin.read(data, imagesize); 
            fin.close();
            char* ordered_data = new char[imagesize];
            //copy data in in a proper order            
            std::cout<< "----------------" <<std::endl;
            for(int i = 0; i < height ; i++){
                std::memcpy(ordered_data + width*i, data + width*(height - 1 - i ), width);
            }                    
            delete[]  data;            
            im = new Image(width, height, reinterpret_cast<uchar*>(ordered_data));        
        }
        assert(im != nullptr);
        return im;
    }

}

