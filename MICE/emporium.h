//
// Created by student on 4/4/18.
//

#ifndef MICE_EMPORIUM_H
#define MICE_EMPORIUM_H

#include <iostream>
#include <vector>
#include "container.h"
#include "scoop.h"
#include "topping.h"
#include "server.h"
#include "customer.h"
#include "order.h"
#include "cash_register.h"

class emporium {
private:
    std::vector<container> containerTypes;
    std::vector<scoop> scoopTypes;
    std::vector<topping> toppingTypes;

    std::vector<server> servers;
    std::vector<customer> customers;
    std::vector<order> orders;
    cash_register cashRegister;
public:
    emporium();
    std::vector<container>& getContainers();
    std::vector<scoop>& getScoops();
    std::vector<topping>& getToppings();
    
    std::vector<server>& getServers();
    std::vector<customer>& getCustomers();
    std::vector<order>& getOrders();
    cash_register& getCashRegister();

    void makeOrder(order newOrder);
    
    void initCashRegister(double amt);
    
};


#endif //MICE_EMPORIUM_H
