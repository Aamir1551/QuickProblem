//
// Created by aamir on 22/02/2021.
//

#include "BinHeap.h"

bool BinHeap::PlaceService(ServiceInstance s) {
    if(s.core > this->max_core_available) {
        return false;
    }
    for(auto const conflict_service : s.inter_aff)
    {
        bool in_bin = this->min_services.find(conflict_service.first) == this->min_services.end();
        if(!in_bin) {
            continue;
        }
        if(this->min_services[conflict_service.first] >= conflict_service.second) {
           return false;
        }
    }
    if(this->is_leaf) {
       // place it in the leaf
       this->max_core_available -= s.core;
        for(auto const conflict_service : s.inter_aff)
        {
            bool in_bin = this->min_services.find(conflict_service.first) == this->min_services.end();
            if(!in_bin) {
                this->min_services[conflict_service.first] = 0;
            } else {
                this->min_services[conflict_service.first] +=1;
            }
            FixHeap();
        }

    } else {
       // Otherwise place it in the left child first, if it is possible, Otherwise place in right leaf
       bool placed_in_left_child = this->left_child->PlaceService(s);
       if(!placed_in_left_child) {
           bool placed_in_right_child = this->right_child->PlaceService(s);
           if(!placed_in_right_child){
               return false;
           }
       }
    }

    return true;
}

void BinHeap::FixHeap() {
    if(parents != nullptr) {
        for(auto const min_service_t : this->min_services) {
            auto t = this->parents->min_services[min_service_t.first];
            this->parents->min_services[min_service_t.first] = max(t, min_service_t.second);
        }
        this->parents->max_core_available = max(this->parents->left_child->max_core_available, this->parents->right_child->max_core_available);
        FixHeap();
    }
}

BinHeap* BinHeap::PlaceServiceInHeap(ServiceInstance s) {
    bool is_item_placed = this->PlaceService(s);
    auto new_root = this;
    if(!is_item_placed) {
       new_root = this->DoubleHeapSize();
       new_root->PlaceService(s);
    }
    return new_root;
}

BinHeap* BinHeap::CreateHeapOfDepth(int depth) {
    BinHeap *bh = new BinHeap(1000);
    BinHeap *left_child;
    BinHeap *right_child;
    if(depth > 0) {
        left_child = CreateHeapOfDepth(depth - 1);
        right_child = CreateHeapOfDepth(depth - 1);
   }
    bh->left_child = left_child;
    bh->right_child = right_child;
    left_child->parents = bh;
    right_child->parents = bh;
    return bh;
}

BinHeap* BinHeap::DoubleHeapSize() {
    int depth = 0;
    BinHeap* current_heap = this;
    while(current_heap->left_child != nullptr) {
        current_heap = current_heap->left_child;
        depth += 1;
    }
    BinHeap *sibling = CreateHeapOfDepth(depth);
    BinHeap *new_root = new BinHeap(1000);

    new_root->left_child = this;
    new_root->right_child = sibling;
    new_root->left_child->parents = this;
    new_root->right_child->parents = this;
    return new_root;
}
