#include "image/listofregion.hpp"
#include "image/region.hpp"
#include <memory>
#include <list>

namespace image {
    ListOfRegion::ListOfRegion() : head(nullptr) {}

    void ListOfRegion::addRegion(std::shared_ptr<Region> region) {
        Node* newNode = new Node(region);
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

    void ListOfRegion::showRegions() const {
        Node* temp = head;
        while (temp) {
            temp->region->showRegion();
            temp = temp->next;
        }
    }

    std::shared_ptr<Region> ListOfRegion::getRegionById(int id) const {
        Node* temp = head;
        while (temp) {
            if (temp->region->getId() == id) {
                return temp->region;
            }
            temp = temp->next;
        }
        return nullptr; // Si no se encuentra
    }

    std::list<std::shared_ptr<Region>> ListOfRegion::getAllRegions() const {
        std::list<std::shared_ptr<Region>> allRegions;
        Node* temp = head;
        while (temp) {
            allRegions.push_back(temp->region);
            temp = temp->next;
        }
        return allRegions;
    }

    int ListOfRegion::size() const {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

    ListOfRegion::~ListOfRegion() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
}
