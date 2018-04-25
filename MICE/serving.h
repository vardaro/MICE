//
// Created by student on 4/4/18.
//

#ifndef MICE_SERVING_H
#define MICE_SERVING_H

#include <vector>
#include "container.h"
#include "scoop.h"
#include "topping.h"


class serving {
protected:
    container servingContainer;
    std::vector<scoop> servingScoops;
    std::vector<topping> servingToppings;

    int containerIndex;
    std::vector<int> scoopIndexes;
    std::vector<int> toppingIndexes;

    double price = -1.0; // set it = to a value it could never be, before calculating it
public:
    serving(container servingContainer, int containerIndex, std::vector<scoop> servingScoops, std::vector<int> scoopIndexes, std::vector<topping> servingToppings, std::vector<int> toppingIndexes);
    double getPrice();

    container getContainer();
    std::vector<scoop> getScoops();
    std::vector<topping> getToppings();

    int getContainerIndex();

    std::vector<int>& getScoopIndexes();

    std::vector<int>& getToppingIndexes();
};


#endif //MICE_ORDER_H
