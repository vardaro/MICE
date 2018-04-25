//
// Created by student on 4/4/18.
//

#ifndef MICE_ORDER_H
#define MICE_ORDER_H

#include <iostream>
#include <vector>
#include "serving.h"

class order {
private:
    int serverID;
    int customerID;
    double totalCost = -1.0;
    std::string status;
    int orderNumber;
    std::vector<serving> servings;
public:
    // POLYMORPHISM

    // Two constructors with different signatures, the first take all private fields, the second only needing the order status and servings vector
    order(int serverID, int customerID, double totalCost, const std::string &status, int orderNumber, std::vector<serving> servings);

    order(const std::string &status, std::vector<serving> servings);

    std::vector<serving> getServings();
    void setOrderNumber(int id);
    void setStatus(std::string newStatus);
    std::string getStatus();
    int getOrderNumber();
    int getServerID();
    int getCustomerID();

    double getTotalCost();
};


#endif //MICE_ORDER_H
