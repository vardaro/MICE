//
// Created by student on 4/4/18.
//

#ifndef MICE_ITEM_H
#define MICE_ITEM_H

#include <iostream>

class item
{
  protected:
    std::string name;
    std::string description;
    double wholesaleCost;
    double retailCost;
    int stockRemaining;
    std::string img;

  public:
    item(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
         int stockRemaining, const std::string &img);

    item() {}
    std::string getName();
    std::string getDescription();
    double getWholesaleCost();
    double getRetailCost();
    int getStockRemaining();
    std::string getImg();
    void reassignStock(int i);
    // OPERATOR OVERLOADING
    void operator--()
    {
        stockRemaining = stockRemaining - 1;
    }
};

#endif //MICE_ITEM_H
