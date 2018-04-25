//
// Created by student on 4/4/18.
//

#ifndef MICE_CUSTOMER_H
#define MICE_CUSTOMER_H

#include <iostream>

class customer {
private:
    std::string name;
    int phoneNumber;
    int customerID;
public:
    customer(const std::string &name, int phoneNumber, int customerID);

    std::string getName();
    int getPhoneNumber();
    int getCustomerID();
};


#endif //MICE_CUSTOMER_H
