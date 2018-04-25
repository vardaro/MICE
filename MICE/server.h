//
// Created by student on 4/4/18.
//

#ifndef MICE_SERVER_H
#define MICE_SERVER_H

#include <iostream>

class server {
private:
    std::string name;
    int employeeID;
    int numOrders = 0;
    double wage;
public:
    // Polymorphism... two constructor, one doest take num orders as a param
    server(const std::string & name, int employeeID, double wage);
    server(const std::string &name, int employeeID, int numOrders, double wage);

    std::string getName();
    int getEmployeeID();
    int getNumOrders();
    double getWage();
    // OPERATOR OVERLOADING
    // ups their number of orders..
    void operator++();

};


#endif //MICE_SERVER_H
