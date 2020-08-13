/*
 * main.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: d-w-h
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include "../inc/functions.hpp"
#include "../inc/heap.hpp"
#include "../inc/user_types.hpp"

int main(int argc, char* argv[])
{
    int size = 30;
    std::vector <edge> edge_set;
    float density = 0.5;
    bool** adj_mat = bool2D(size);
    float** weight_mat = float2D(size);
    node* node_arr = new node[size];

    /* Populate adjancy and weight matrices with random data */
    populate_adj_and_weight(adj_mat, weight_mat, size, density);

    /* Make edge set */
    make_edge_set(edge_set, adj_mat, weight_mat, size);

    /* Initialize node array */
    init_node_arr(edge_set, node_arr, size);

    /* Create, set and build heap */
    Heap my_heap(weight_mat, size);
    my_heap.set_heap(node_arr);
    my_heap.build_min_heap();

    /* Execute Prim's algorithm */
    my_heap.prim_algo();

    /* Print minimum spanning tree */
    my_heap.print_mst();

    /* Free allocated data */
    delete_bool2D(adj_mat, size);
    delete_float2D(weight_mat, size);

    return 0;
}
