//
// Created by student on 4/4/18.
//

#include "container.h"
#include <sstream>

using namespace v8;
container::container(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
                     int stockRemaining, const std::string &img, int scoopCount) : item(name, description,
                                                                                        wholesaleCost, retailCost,
                                                                                        stockRemaining, img),
                                                                                   scoopCount(scoopCount) {}

std::string container::stringify()
{
    std::ostringstream out;
    out << "\nNAME: " << name;
    out << "\nDESC: " << description;
    out << "\nWC: $" << wholesaleCost;
    out << "\nRC: $" << retailCost;
    out << "\nSTOCK: " << stockRemaining;
    out << "\nTHE SCOOP COUNT: " << scoopCount;
    return out.str();
}

int container::getScoopCount()
{
    return container::scoopCount;
}
