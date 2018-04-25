//
// Created by student on 4/4/18.
//

#include "item.h"

item::item(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
           int stockRemaining, const std::string &img) : name(name), description(description),
                                                         wholesaleCost(wholesaleCost), retailCost(retailCost),
                                                         stockRemaining(stockRemaining), img(img) {}
std::string item::getName() {
    return item::name;
}
std::string item::getDescription() {
    return item::description;
}
double item::getWholesaleCost() {
    return item::wholesaleCost;
}
double item::getRetailCost() {
    return item::retailCost;
}
int item::getStockRemaining() {
    return item::stockRemaining;
}
void item::reassignStock(int i) {
    item::stockRemaining + i;
}
std::string item::getImg(){
    return item::img;
}
