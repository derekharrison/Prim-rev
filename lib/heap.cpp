/*
 * heap.cpp
 *
 *  Created on: Aug 13, 2020
 *      Author: d-w-h
 */

#include <iostream>

#include "../inc/functions.hpp"
#include "../inc/heap.hpp"

Heap::Heap(float** weight_mat, int size) {
    this->heap_size = size;
    this->length = size;
    this->A = new node[size+1];
    this->A[0].key = inf;
    this->B = new node[size];
    this->min_node_arr = new node[this->heap_size+1];
    this->weight_mat = float2D(size);
    init_weight_mat(this->weight_mat, weight_mat, size);
}

Heap::~Heap() {
    delete [] this->A;
    delete [] this->B;
    delete [] min_node_arr;
    delete_float2D(this->weight_mat, this->length);
}

int Heap::parent(int i) {
    return i/2;
}

int Heap::left(int i) {
    return 2*i;
}

int Heap::right(int i) {
    return 2*i + 1;
}

void Heap::min_heapify(node A[], int i) {
    int l, r, smallest;
    l = Heap::left(i);
    r = Heap::right(i);
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
        Heap::min_heapify(A, smallest);
    }
}

void Heap::build_min_heap() {
    for(int i = (this->heap_size)/2; i > 0; --i) {
        Heap::min_heapify(this->A, i);
    }
}

void Heap::set_heap(node B[]) {
    for(int i = 1; i < this->heap_size + 1; ++i) {
        this->A[i] = B[i-1];
        this->B[i-1] = B[i-1];
    }
}

void Heap::get_heap(node B[]) {
    for(int i = 1; i < this->heap_size + 1; ++i) {
        B[i-1] = this->A[i];
    }
}

bool Heap::min_heap_verify() {
    bool is_min_heap = true;
    for(int i = (this->heap_size - 1)/2; i > 0; --i) {
        int l, r;
        l = Heap::left(i);
        r = Heap::right(i);
        if(this->A[i].key > this->A[l].key || this->A[i].key > this->A[r].key) {
            is_min_heap = false;
        }
    }

    return is_min_heap;
}

void Heap::print_heap() {
    for(int i = this->heap_size/2; i > 0; --i) {
        int l, r;
        l = Heap::left(i);
        r = Heap::right(i);
        if(l < this->heap_size + 1 && r < this->heap_size + 1) {
            printf("node: %i, key: %.2f, key left child: %.2f, key right child: %.2f\n", i, this->A[i].key,  this->A[l].key,  this->A[r].key);
        }
    }
}

void Heap::print_mst() {
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

node Heap::heap_extract_min() {
    if(this->heap_size < 1) {
        printf("heap size is less than 1\n");
    }
    node min = this->A[1];
    this->B[this->A[1].index].in_q = false;
    this->A[1] = this->A[this->heap_size];
    this->heap_size = this->heap_size - 1;
    Heap::min_heapify(this->A, 1);

    return min;
}

void Heap::prim_algo() {
    int* index_map = new int[this->length+1];
    index_map[0] = 0; // to ensure that index_map doesn't contain garbage at index 0
    for(int it = 0; it < this->length; ++it) {
        node min_node = Heap::heap_extract_min();
        min_node_arr[it] = min_node;
        for(int i = 1; i < this->heap_size + 1; ++i) {
            index_map[this->A[i].index] = i;
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
                this->A[index_a].key = this->weight_mat[start_vertex][end_vertex];
            }
        }

        Heap::build_min_heap();
    }
}
