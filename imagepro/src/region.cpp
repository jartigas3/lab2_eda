#include "image/region.hpp"

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

    void Region::showRegion() const{
        std::cout << "Region ID:" << id << ", size: " << size << std::endl;
        points.showPoints();
    }

    int Region::getSize() const {
        return size;
    }

    Region::~Region(){
        
    }
}