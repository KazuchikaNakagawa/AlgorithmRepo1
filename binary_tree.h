#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "enumeration.h"
#include <stdbool.h>

typedef struct _bt {
    struct _bt *left, *right;
    int data;
} binary_tree;

binary_tree* binary_tree_init(num_pattern*);
void binary_tree_insert(binary_tree**, int);
void binary_leaf_init(binary_tree*, int);
bool binary_tree_equal(binary_tree*, binary_tree*);
bool binary_tree_is_complete(binary_tree*);
bool binary_tree_is_AVL(binary_tree* tree);
int binary_tree_depth(binary_tree*);
void binary_tree_print(binary_tree*);

typedef struct {
    binary_tree** buf;
    unsigned size;
} array;

void array_init(array*);
binary_tree** array_new_element_ptr(array*);

#endif /* BINARY_TREE_H */