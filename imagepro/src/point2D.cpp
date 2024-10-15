#include "image/point2D.hpp"

 namespace image{
    Point2D::Point2D(): x(0), y(0) {

    }

	Point2D::Point2D(int _x, int _y): x(_x), y(_y){

    }

    void Point2D::setX(int _x){
        x = _x;
    }
    void Point2D::setY(int _y){
        y = _y;
    }
    int Point2D::getX() const {
        return x;
    }
    int Point2D::getY() const {
        return y;
    }

    Point2D::~Point2D(){
        
    }
 }
 