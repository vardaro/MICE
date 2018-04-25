//
// Created by student on 4/4/18.
//

#ifndef MICE_SCOOP_H
#define MICE_SCOOP_H

#include "item.h"
#include "topping.h"

class scoop: public item {
private:
public:
    //Constructor without topping
    scoop(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
          int stockRemaining, const std::string &img);

    std::string stringify();
};


#endif //MICE_SCOOP_H
