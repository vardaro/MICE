//
// Created by student on 4/4/18.
//

#ifndef MICE_CONTAINER_H
#define MICE_CONTAINER_H

#include "item.h"
#include <v8.h>
#include <node.h>

#include "scoop.h"
#include <vector>

using namespace v8;

class container : public item
{
private:
  int scoopCount;

public:
  container(const std::string &name, const std::string &description, double wholesaleCost, double retailCost,
            int stockRemaining, const std::string &img, int scoopCount);

  std::string stringify();

  int getScoopCount();

};

#endif //MICE_CONTAINER_H
