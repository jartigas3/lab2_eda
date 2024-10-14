#ifndef REGION_HPP
#define REGION_HPP

#include "listofpoint2d.hpp"
#include <iostream>

namespace image {
	class Region{
	private:
		int id;
		int size;
		ListOfPoint2D points;		
	public:
		Region();
		void addPoint(const Point2D& point);
		void setId(int _id);
		void showRegion() const;
		int getSize() const;
		int getId() const;
        virtual ~Region(); 		
	};
}

#endif 