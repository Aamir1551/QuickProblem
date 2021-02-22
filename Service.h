//
// Created by aamir on 22/02/2021.
//

#ifndef QUICKPROBLEM_SERVICE_H
#define QUICKPROBLEM_SERVICE_H

#include <vector>
#include <tuple>
using namespace std;


class ServiceInstance {

public:
    int id;
    int core;
    int intra_value;

    vector<pair<int, int>> inter_aff; // service_id, max number of allowed conflicts with this service id

    ServiceInstance(int id, int core, int intra_value) {
        this->id = id;
        this->core = core;
        this->intra_value = intra_value;
    }

    void AddIntraAff(int s, int capacity);

};

#endif //QUICKPROBLEM_SERVICE_H
