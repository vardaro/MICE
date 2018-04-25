//
// Created by student on 4/4/18.
//

#include "order.h"
#include <string>

order::order(int serverID, int customerID, double totalCost, const std::string &status, int orderNumber, std::vector<serving> servings) : serverID(
        serverID), customerID(customerID), totalCost(totalCost), status(status), orderNumber(orderNumber), servings(servings) {}


order::order(const std::string & status, std::vector<serving> servings) : status(status), servings(servings) {

}

void order::setOrderNumber(int id) {
        order::orderNumber = id;
}
void order::setStatus(std::string newStatus) {
        order::status = newStatus;
}
std::vector<serving> order::getServings() {
        return order::servings;
}
int order::getOrderNumber() {
        return order::orderNumber;
}
std::string order::getStatus() {
        return order::status;
}

int order::getCustomerID() {
        return order::customerID;
}

int order::getServerID() {
        return order::serverID;
}

double order::getTotalCost() {
        // if total cost has already been calculated, jsut return that value
        if (order::totalCost != -1.0) {
                return order::totalCost;
        }

        int numOrders = order::servings.size();
        double sum = 0.0;
        for (int i = 0; i < numOrders; i++) {
                sum += order::servings[i].getPrice();
        }

        order::totalCost = sum;
        return sum;
}