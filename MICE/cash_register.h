//
// Created by student on 4/4/18.
//

#ifndef MICE_CASH_REGISTER_H
#define MICE_CASH_REGISTER_H


class cash_register {
private:
    double amount;
public:
    cash_register();
    cash_register(double amount);
    void applyBalance(double amt);
    double getBalance();
};


#endif //MICE_CASH_REGISTER_H
