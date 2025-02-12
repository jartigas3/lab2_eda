#include "image/listofpoint2d.hpp"
#include "image/point2D.hpp"
#include <vector>

namespace image {
    ListOfPoint2D::ListOfPoint2D() : head(nullptr){
    
    }

    void ListOfPoint2D::addPoint(const Point2D& point){
        Node* newNode = new Node(point);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
       
    }

    void ListOfPoint2D::showPoints() const {
        Node* temp = head;
        while (temp) {
            std::cout << "(" << temp->point.getX() << ", " << temp->point.getY() << ") ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    std::vector<Point2D> ListOfPoint2D::getPoints() const {
        std::vector<Point2D> points;
        Node* temp = head;
        while (temp) {
            points.push_back(temp->point);
            temp = temp->next;
        }
        return points;
    }

    ListOfPoint2D::~ListOfPoint2D(){
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }


}