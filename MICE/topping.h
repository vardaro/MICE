//
// Created by student on 4/4/18.
//

#ifndef MICE_TOPPING_H
#define MICE_TOPPING_H

#include "item.h"

#include <iostream>
class topping : public item {
public:
    topping(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
            int stockRemaining, const std::string &img);
std::string stringify();
};


#endif //MICE_TOPPING_H
