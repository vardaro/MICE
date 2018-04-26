//
// Created by student on 4/4/18.
//

#include "emporium.h"

emporium::emporium(){}

std::vector<container>& emporium::getContainers() {
    return emporium::containerTypes;
}
std::vector<scoop>& emporium::getScoops() {
    return emporium::scoopTypes;
}
std::vector<topping>& emporium::getToppings() {
    return emporium::toppingTypes;
}

std::vector<order>& emporium::getOrders() {
    return emporium::orders;
}

std::vector<server>& emporium::getServers() {
    return emporium::servers;
}

std::vector<customer>& emporium::getCustomers() {
    return emporium::customers;
}

cash_register& emporium::getCashRegister() {
    return emporium::cashRegister;
}

// this function accepts an order object as param, and emplaces the order object to the 
// order vector member
// however before doing this, it reduces the stock of each involved object by 1
void emporium::makeOrder(order newOrder) {
    int numServings = newOrder.getServings().size();

    // iterate of servings
    for (int i = 0; i < numServings; i++) {

        // get the index of the containerm, then decrement the container at that index by 1
        int conIndex = newOrder.getServings()[i].getContainerIndex();
        --emporium::containerTypes[conIndex]; // decrement the stock

        for (int j = 0; j < newOrder.getServings()[i].getScoops().size(); j++) {
            int curScoopIndex = newOrder.getServings()[i].getScoopIndexes()[j]; // now that we have the index of the current iteration
            // fucking decrement that shit
            --emporium::scoopTypes[curScoopIndex];
        }

        // now do the same for the toppings.......
        for (int j = 0; j < newOrder.getServings()[i].getToppings().size(); j++) {
            int curIndex = newOrder.getServings()[i].getToppingIndexes()[j]; // now that we have the index of the current iteration
            // fucking decrement that shit
            --emporium::toppingTypes[curIndex];
        }
    }

    // now add the total cost toteh cash register...
    emporium::cashRegister.applyBalance(newOrder.getTotalCost());

    // yayy now set those private members! (no im not going to worry about the stock in the object vectors bc that sounds annoying and will be annoying to implement AND has no impact)
    emporium::orders.emplace_back(newOrder);
}

void emporium::initCashRegister(double amt) {
    emporium::cashRegister = cash_register(amt);
}