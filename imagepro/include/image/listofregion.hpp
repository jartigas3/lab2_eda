#ifndef LISTOFREGION_HPP
#define LISTOFREGION_HPP

#include "region.hpp"
#include <memory>
#include <list>
#include <iostream>

namespace image {
    class ListOfRegion {
    private:
        struct Node {
            std::shared_ptr<Region> region;
            Node* next;
            Node(std::shared_ptr<Region> r) : region(r), next(nullptr) {}
        };
        Node* head;

    public:
        ListOfRegion();
        void addRegion(std::shared_ptr<Region> region);
        void showRegions() const;
        std::shared_ptr<Region> getRegionById(int id) const;
		std::list<std::shared_ptr<Region>> getAllRegions() const;
		int size() const;
        ~ListOfRegion();
    };
}

#endif
