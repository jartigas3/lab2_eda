#include "image/region.hpp"
#include <vector>

namespace image {
    Region::Region(): id(0), size(0){
        
    }

    void Region::addPoint(const Point2D& point){
        points.addPoint(point);
        size++;
    }

    void Region::setId(int _id){
        id = _id;
    }

    int Region::getId() const {
        return id;  
    }

   void Region::showRegion() const {

        std::vector<Point2D> regionPoints = points.getPoints();
    
        if (regionPoints.empty()) {
            std::cout << "La región no tiene puntos." << std::endl;
            return;
        }
    
        int maxRow = 0;
        int maxCol = 0;

       for (const auto& point : regionPoints) {
            if (point.getY() > maxRow) maxRow = point.getY();
            if (point.getX() > maxCol) maxCol = point.getX();
        }

        
        std::vector<std::vector<char>> grid(maxRow + 1, std::vector<char>(maxCol + 1, ' '));

        // Llenar la cuadrícula con los puntos pertenecientes a la región
        for (const auto& point : regionPoints) {
            grid[point.getY()][point.getX()] = '*';
        }


       for (const auto& row : grid) {
            for (const auto& cell : row) {
                std::cout << cell;
            }
            std::cout << std::endl;
        }
    
    }

    int Region::getSize() const {
        return size;
    }

    Region::~Region(){
        
    }
}