//
// Created by aamir on 22/02/2021.
//

#include "Service.h"

void ServiceInstance::AddIntraAff(int s, int capacity) {
    this->inter_aff.emplace_back(make_pair(s, capacity));
}
