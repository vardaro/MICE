//
// Created by student on 4/4/18.
//

#include "server.h"

server::server(const std::string &name, int employeeID, int numOrders, double wage) : name(name),
                                                                                      employeeID(employeeID),
                                                                                      numOrders(numOrders),
                                                                                      wage(wage) {}
server::server(const std::string &name, int employeeID, double wage) : name(name),
                                                                       employeeID(employeeID),
                                                                       wage(wage) {}
void server::operator++() {
    server::numOrders++;
}

std::string server::getName() {
    return name;
}

int server::getEmployeeID() {
    return employeeID;
}

int server::getNumOrders() {
    return numOrders;
}

double server::getWage() {
    return wage;
}