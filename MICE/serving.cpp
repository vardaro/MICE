#include "serving.h"

serving::serving(container servingContainer, int containerIndex, std::vector<scoop> servingScoops, std::vector<int> scoopIndexes, std::vector<topping> servingToppings, std::vector<int> toppingIndexes) : servingContainer(servingContainer),
                                                                                                                                                                                                           containerIndex(containerIndex),
                                                                                                                                                                                                               servingScoops(servingScoops),
                                                                                                                                                                                                           scoopIndexes(scoopIndexes),
                                                                                                                                                                                                               servingToppings(servingToppings),
                                                                                                                                                                                                           toppingIndexes(toppingIndexes)
{
    getPrice();
}

// returns the price if its available, if not, calculuate it first
double serving::getPrice()
{
    // quick check if this function has already bee called once before
    if (serving::price != -1.0) {
        return serving::price;
    }

    // otherwise do the manuel calculation....
    double price = servingContainer.getRetailCost();

    // add price of all servings
    int numScoops = servingScoops.size();
    for (int i = 0; i < numScoops; i++)
    {
        price += servingScoops[i].getRetailCost();
    }

    int numToppings = servingToppings.size();
    for (int i = 0; i < numToppings; i++)
    {
        price += servingToppings[i].getRetailCost();
    }
    serving::price = price;
    return price;
}

container serving::getContainer()
{
    return serving::servingContainer;
}

std::vector<scoop> serving::getScoops()
{
    return serving::servingScoops;
}

std::vector<topping> serving::getToppings()
{
    return serving::servingToppings;
}

int serving::getContainerIndex() {
    return serving::containerIndex;
}

std::vector<int>& serving::getScoopIndexes() {
    return serving::scoopIndexes;
}

std::vector<int>& serving::getToppingIndexes() {
    return serving::toppingIndexes;
}