#include "image/image.hpp"
#include "image/region.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <memory>

int main(int nargs, char** vargs) {
    std::unordered_map<std::string, image::Image*> images; // Para almacenar las imágenes por nombre
    std::string command;

    std::cout << ">> Bienvenido a ImagePRO" << std::endl;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            std::cout << "Saliendo del programa." << std::endl;
            break;
        } else if (command.find("read") == 0) {
            // Comando read <nombre_imagen> <ruta>
            std::string imgName, path;
            std::istringstream iss(command);
            std::string temp;
            iss >> temp >> imgName >> path;

            if (path.empty() || imgName.empty()) {
                std::cout << "Comando inválido. Uso: read <nombre_imagen> <ruta>" << std::endl;
                continue;
            }

            image::Image* img = image::Image::readImage(path);
            if (img) {
                images[imgName] = img;
                std::cout << "Imagen " << imgName << " leída exitosamente desde " << path << std::endl;
            } else {
                std::cout << "No se pudo leer la imagen desde " << path << std::endl;
            }

        } else if (command.find("show") == 0) {
            // Comando show <nombre_imagen>
            std::istringstream iss(command);
            std::string temp, imgName;
            iss >> temp >> imgName;

            if (images.find(imgName) != images.end()) {
                images[imgName]->show();
            } else {
                std::cout << "Imagen " << imgName << " no encontrada." << std::endl;
            }

        } else if (command.find("getRegions") == 0) {
            // Comando getRegions <nombre_imagen>
            std::istringstream iss(command);
            std::string temp, imgName;
            iss >> temp >> imgName;

            if (images.find(imgName) != images.end()) {
                std::list<std::shared_ptr<image::Region>> regions = images[imgName]->getRegions();
                std::cout << "La imagen " << imgName << " tiene " << regions.size() << " regiones." << std::endl;

                int regionId = 1;
                for (const auto& region : regions) {
                    std::cout << "Region " << regionId << " -> Tamaño: " << region->getSize() << std::endl;
                    ++regionId;
                }
            } else {
                std::cout << "Imagen " << imgName << " no encontrada." << std::endl;
            }

        } else if (command.find("showRegion") == 0) {
            // Comando showRegion <nombre_imagen> <id_region>
            std::istringstream iss(command);
            std::string temp, imgName;
            int regionId;
            iss >> temp >> imgName >> regionId;

            if (images.find(imgName) != images.end()) {
                std::list<std::shared_ptr<image::Region>> regions = images[imgName]->getRegions();

                if (regionId > 0 && regionId <= regions.size()) {
                    auto it = regions.begin();
                    std::advance(it, regionId - 1);
                    (*it)->showRegion();  // Corregido: desreferenciar puntero inteligente
                } else {
                    std::cout << "ID de región inválido para la imagen " << imgName << std::endl;
                }
            } else {
                std::cout << "Imagen " << imgName << " no encontrada." << std::endl;
            }

        } else {
            std::cout << "Comando no reconocido." << std::endl;
        }
    }

    // Liberar memoria de las imágenes cargadas
    for (auto& pair : images) {
        delete pair.second;
    }

    return 0;
}
