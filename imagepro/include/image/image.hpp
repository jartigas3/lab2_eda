#include <string>
#include <list>
#include "region.hpp"

namespace image {
	class Image; 
	typedef unsigned char uchar;
	

	class Image{
	private:
		int width;
		int height;
		int th_value;
		uchar* data;
	public:
		Image();
		Image(int w, int h);
		Image(int w, int h, uchar* _data);
		void threshold(); 
    	int getValue(int row, int col);
		void show();
		std::list<std::shared_ptr<Region>> getRegions();
		void exploreRegion(int row, int col, bool* visites, Region& region);
        virtual ~Image(); 
		static Image* readImage(std::string &path);        
	};
}
