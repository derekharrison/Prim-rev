/*
 * heap.cpp
 *
 *  Created on: Aug 13, 2020
 *      Author: d-w-h
 */

#include <iostream>

#include "../inc/functions.hpp"
#include "../inc/heap.hpp"

Prim::Prim(bool** adj_mat, float** weight_mat, int size) {
    this->heap_size = size;
    this->length = size;
    this->heap = new node[size+1];
    this->heap[0].key = inf;
    this->B = new node[size];
    this->min_node_arr = new node[size+1];
    this->weight_mat = float2D(size);
    init_weight_mat(this->weight_mat, weight_mat, size);
    make_edge_set(this->edge_set, adj_mat, weight_mat, size);
    init_node_arr(this->edge_set, this->B, size);
    set_heap(this->heap, this->B, size);
    Prim::build_min_heap();
}

Prim::~Prim() {
    delete [] this->heap;
    delete [] this->B;
    delete [] min_node_arr;
    delete_float2D(this->weight_mat, this->length);
}

int Prim::parent(int i) {
    return i/2;
}

int Prim::left(int i) {
    return 2*i;
}

int Prim::right(int i) {
    return 2*i + 1;
}

void Prim::min_heapify(node A[], int i) {
    int l, r, smallest;
    l = Prim::left(i);
    r = Prim::right(i);
    if(l < this->heap_size + 1 && A[l].key < A[i].key) {
        smallest = l;
    }
    else {
        smallest = i;
    }
    if(r < this->heap_size + 1 && A[r].key < A[smallest].key) {
        smallest = r;
    }
    if(smallest != i) {
        node dummy;
        dummy = A[i];
        A[i] = A[smallest];
        A[smallest] = dummy;
        Prim::min_heapify(A, smallest);
    }
}

void Prim::build_min_heap() {
    for(int i = this->heap_size/2; i > 0; --i) {
        Prim::min_heapify(this->heap, i);
    }
}

bool Prim::min_heap_verify() {
    bool is_min_heap = true;
    for(int i = (this->heap_size - 1)/2; i > 0; --i) {
        int l, r;
        l = Prim::left(i);
        r = Prim::right(i);
        if(this->heap[i].key > this->heap[l].key || this->heap[i].key > this->heap[r].key) {
            is_min_heap = false;
        }
    }

    return is_min_heap;
}

void Prim::print_heap() {
    for(int i = this->heap_size/2; i > 0; --i) {
        int l, r;
        l = Prim::left(i);
        r = Prim::right(i);
        if(l < this->heap_size + 1 && r < this->heap_size + 1) {
            printf("node: %i, key: %.2f, key left child: %.2f, key right child: %.2f\n", i, this->heap[i].key,  this->heap[l].key,  this->heap[r].key);
        }
    }
}

void Prim::print_mst() {
    float total_weight_mst = 0.0;
    for(int i = 1; i < this->length; ++i) {
        int parent_index = this->B[i].parent_index;
        int current_index = this->B[i].index;
        float weight = this->weight_mat[parent_index][current_index];
        total_weight_mst += weight;
        printf("went from %i to %i totaling: %.4f\n", parent_index, current_index, weight);
    }

    printf("total weight mst: %.4f\n", total_weight_mst);
}

node Prim::heap_extract_min() {
    if(this->heap_size < 1) {
        printf("heap size is less than 1\n");
    }
    node min = this->heap[1];
    this->B[this->heap[1].index].in_q = false;
    this->heap[1] = this->heap[this->heap_size];
    this->heap_size = this->heap_size - 1;
    Prim::min_heapify(this->heap, 1);

    return min;
}

void Prim::prim_algo() {
    int* index_map = new int[this->length+1];
    index_map[0] = 0; // to ensure that index_map doesn't contain garbage at index 0
    for(int it = 0; it < this->length; ++it) {
        node min_node = Prim::heap_extract_min();
        min_node_arr[it] = min_node;
        for(int i = 1; i < this->heap_size + 1; ++i) {
            index_map[this->heap[i].index] = i;
        }

        for(unsigned int i = 0; i < min_node.adj_nodes.size(); ++i) {
            int start_vertex = min_node.index;
            int end_vertex = min_node.adj_nodes[i];
            int index_a = index_map[end_vertex];
            node v = this->B[end_vertex];
            if(v.in_q && this->weight_mat[start_vertex][end_vertex] < v.key) {
                this->B[end_vertex].parent_index = min_node.index;
                this->B[end_vertex].index = end_vertex;
                this->B[end_vertex].pi = &min_node_arr[it];
                this->B[end_vertex].key = this->weight_mat[start_vertex][end_vertex];
                this->heap[index_a].key = this->weight_mat[start_vertex][end_vertex];
            }
        }

        Prim::build_min_heap();
    }
}
