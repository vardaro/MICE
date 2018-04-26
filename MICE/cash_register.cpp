//
// Created by student on 4/4/18.
//

#include "cash_register.h"
cash_register::cash_register(){}
cash_register::cash_register(double amount) : amount(amount) {

}

void cash_register::applyBalance(double amt) {
    cash_register::amount += amt;
}

double cash_register::getBalance() {
    return cash_register::amount;
}