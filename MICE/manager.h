//
// Created by student on 4/4/18.
//

#ifndef MICE_MANAGER_H
#define MICE_MANAGER_H

#include "emporium.h"

class manager {
private:
public:

    void addScoop();
    void addContainer();
    void addTopping();

    void hireServer();
    void createCustomer();

    void viewServerReport();
    void viewCustomerReport();
    void viewInventoryReport();
    void viewOrderReport();
    void viewProfitLoss();
};


#endif //MICE_MANAGER_H
