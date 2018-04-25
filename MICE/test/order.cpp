#include "../order.h"
#include "../container.h"
#include "../scoop.h"
#include "../topping.h"
#include "../serving.h"
#include <vector>

int main() {
    container c("name", "desc", 12.0, 14.0, 5, "img", 5);
    scoop s("name", "desc", 12.0, 14.0, 2, "img");
    topping t("name", "desc", 12.0, 14.0, 2, "img");

    std::vector<scoop> scoopVec = {s};
    std::vector<scoop> toppingVec = {t};
    serving testServing(c, scoopVec, toppingVec);

    std::cout << testServing.getPrice() << std::endl;
}