#ifndef LISTOFPOINT2D_HPP
#define LISTOFPOINT2D_HPP

#include "point2D.hpp"
#include <iostream>

namespace image {
	class ListOfPoint2D{
	private:		
		struct Node{
			Point2D point;
			Node* next;
			Node(const Point2D& p): point(p), next(nullptr){}
		};

		Node* head;

	public:		
		ListOfPoint2D();
		void addPoint(const Point2D& point);
		void showPoints() const;
		~ListOfPoint2D();
	};
}


#endif