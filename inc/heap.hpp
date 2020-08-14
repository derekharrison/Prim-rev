/*
 * heap.hpp
 *
 *  Created on: Aug 13, 2020
 *      Author: d-w-h
 */

#ifndef HEAP_HPP_
#define HEAP_HPP_

#include "user_types.hpp"

class Heap {
private:
    int heap_size;
    int length;
    node* A;
    node* B;
    float** weight_mat;
    node* min_node_arr;
    std::vector <edge> edge_set;

public:
    Heap(bool** adj_mat, float** weight_mat, int size);
    ~Heap();

    node heap_extract_min();
    void prim_algo();
    int parent(int i);
    int left(int i);
    int right(int i);
    void min_heapify(node A[], int i);
    void build_min_heap();
    bool min_heap_verify();
    void print_heap();
    void print_mst();
};

#endif /* HEAP_HPP_ */
