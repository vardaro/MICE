//
// Created by student on 4/4/18.
//

#include "customer.h"

customer::customer(const std::string &name, int phoneNumber, int customerID) : name(name), phoneNumber(phoneNumber),
                                                                               customerID(customerID) {}

std::string customer::getName() {
    return name;
}

int customer::getPhoneNumber() {
    return phoneNumber;
}

int customer::getCustomerID() {
    return customerID;
}
