/*
 * prim.hpp
 *
 *  Created on: Aug 13, 2020
 *      Author: d-w-h
 */

#ifndef PRIM_HPP_
#define RPIM_HPP_

#include "user_types.hpp"

class Prim {
private:
    int heap_size;
    int length;
    node* heap;
    node* node_array;
    float** weight_mat;
    node* min_node_arr;
    std::vector <edge> edge_set;

    int parent(int i);
    int left(int i);
    int right(int i);
    void min_heapify(node A[], int i);
    void build_min_heap();
    node heap_extract_min();

public:
    Prim(bool** adj_mat, float** weight_mat, int size);
    ~Prim();

    void prim_algo();
    bool min_heap_verify();
    void print_heap();
    void print_mst();
    void print_size_mst();
};

#endif /* PRIM_HPP_ */
