#include <iostream>

#include "container.h"
#include "scoop.h"
#include "topping.h"

#include <vector>
#include <iostream>

void menu() {
    std::cout<< "what do you wnat to do" << std::endl;
    std::cout<< "1. show all" << std::endl;
    std::cout<< "2. create container" << std::endl;
    std::cout<< "3. create scoop" << std::endl;
    std::cout<< "4. create topping" << std::endl;
    std::cout<< "5. leave" << std::endl;

}

int main() {
    std::vector<container> containers;
    containers.emplace_back(container("BOWL", "A DISH FOR YOUR ICE CREAM", 1000.0, 2000.0, 5, "", 4));
    containers.emplace_back(container("CONE", "ICE CREAM IN A WAFFLE CONE", 3.0, 4.0, 5, "", 2));
    containers.emplace_back(container("CUP", "THE BOWLS UNDERACHIEVING BROTHER", 3.0, 4.0, 5, "", 2));

    std::vector<scoop> scoops;
    scoops.emplace_back(scoop("RASPBERRY", "THE HEALTHIEST BERRY", 1.0,2.0,20,""));
    scoops.emplace_back(scoop("VANILLA", "FOR THE BORING", 1.0,2.0,20,""));
    scoops.emplace_back(scoop("CHOCOLATE", "CHOCOLATE ICE CREAM SCOOP", 1.0,2.0,20,""));

    std::vector<topping> toppings;
    toppings.emplace_back(topping("LIGHT", "LIGHT TOPPING", 1.0, 2.0, 40, ""));
    toppings.emplace_back(topping("HEAVY", "HEAVY TOPPING", 1.0, 2.0, 40, ""));
    toppings.emplace_back(topping("NORMAL", "NORMAL TOPPING", 1.0, 2.0, 40, ""));
    toppings.emplace_back(topping("DRENCH", "DRENCH TOPPING", 1.0, 2.0, 40, ""));

    int choice;

    menu();
    std::cin >> choice;
    std::cin.ignore();

    while (choice != 5) {
        switch (choice) {
            case 1: {
                for (int i = 0; i < containers.size(); i++) {
                    std::cout << containers[i].stringify() << std::endl;
                }
                std::cout<<"\n" <<std::endl;
                for (int i = 0; i < scoops.size(); i++) {
                    std::cout << scoops[i].stringify() << std::endl;
                }
                std::cout<<"\n" <<std::endl;

                for (int i = 0; i < toppings.size(); i++) {
                    std::cout << toppings[i].stringify() << std::endl;
                }
                break;
            }

            case 2: {
                std::string name, desc;
                double wc, rc;
                int stock;
                std::cout << "enter name" << std::endl;
                getline(std::cin, name);
                std::cout << "enter description" << std::endl;
                getline(std::cin, desc);
                std::cout << "enter wholesale cost" << std::endl;
                std::cin >> wc;
                std::cout << "enter retail cost" << std::endl;
                std::cin >> rc;
                std::cout << "enter stock" << std::endl;
                std::cin >> stock;

                containers.emplace_back(container(name,desc,wc,rc,stock,"", 0));
                break;
            }

            case 3: {
                std::string name, desc;
                double wc, rc;
                int stock;
                std::cout << "enter name" << std::endl;
                getline(std::cin, name);
                std::cout << "enter description" << std::endl;
                getline(std::cin, desc);
                std::cout << "enter wholesale cost" << std::endl;
                std::cin >> wc;
                std::cout << "enter retail cost" << std::endl;
                std::cin >> rc;
                std::cout << "enter stock" << std::endl;
                std::cin >> stock;

                scoops.emplace_back(scoop(name,desc,wc,rc,stock, ""));
                break;
            }

            case 4: {
                std::string name, desc;
                double wc, rc;
                int stock;
                std::cout << "enter name" << std::endl;
                getline(std::cin, name);
                std::cout << "enter description" << std::endl;
                getline(std::cin, desc);
                std::cout << "enter wholesale cost" << std::endl;
                std::cin >> wc;
                std::cout << "enter retail cost" << std::endl;
                std::cin >> rc;
                std::cout << "enter stock" << std::endl;
                std::cin >> stock;

                toppings.emplace_back(topping(name,desc,wc,rc,stock,""));
                break;
            }

        }
        menu();
        std::cin >> choice;
        std::cin.ignore();

    }

    return 0;
}