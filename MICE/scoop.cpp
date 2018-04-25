//
// Created by student on 4/4/18.
//

#include "scoop.h"
#include <sstream>
scoop::scoop(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
             int stockRemaining, const std::string &img) : item(name, description, wholesaleCost, retailCost,
                                                                stockRemaining, img) {}

std::string scoop::stringify() {
    std::ostringstream o;
    o << "\nNAME: " << name;
    o << "\nDESC: "<< description;
    o << "\nWC: $" << wholesaleCost;
    o << "\nRC: $" << retailCost;
    o << "\nSTOCK: " << stockRemaining;
    return o.str();
}