//
// Created by aamir on 22/02/2021.
//

#ifndef QUICKPROBLEM_BINHEAP_H
#define QUICKPROBLEM_BINHEAP_H
#include <map>
#include <iostream>
#include <unordered_map>
#include "Service.h"

using namespace std;

class BinHeap {

public:
    BinHeap *left_child = nullptr;
    BinHeap *right_child = nullptr;
    BinHeap *parents = nullptr;
    int max_core_available; // maximum amount of core available (if leaf) or max core available over the children of this node
    unordered_map<int, int> min_services;
    // unordered_map = (service_id, min number of services at a bin below this node)
    // Stores the minimum number of services at every bin below this node
    // min_services takes value of the number of services of type, if, BinHeap is leaf (i.e it is a bin)

    bool is_leaf = false;

    // Do not need to consider case, where all bins are giving us a conflict

    explicit BinHeap(int max_core_available){
        this->max_core_available = max_core_available;
    };
    BinHeap* PlaceServiceInHeap(ServiceInstance s);

private:
    bool PlaceService(ServiceInstance s);
    void FixHeap();
    BinHeap* DoubleHeapSize();
    BinHeap* CreateHeapOfDepth(int depth);
};


#endif //QUICKPROBLEM_BINHEAP_H
