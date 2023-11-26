#include "binary_tree.h"
#include "enumeration.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void array_init(array* arr)
{
    arr->buf = NULL;
    arr->size = 0;
}

binary_tree** array_new_element_ptr(array* arr)
{
    arr->buf = realloc(arr->buf, sizeof(binary_tree*) * ++arr->size);
    return &arr->buf[arr->size - 1];
}

bool binary_tree_equal(binary_tree* lhs, binary_tree* rhs)
{
    if (lhs == NULL && rhs == NULL) {
        return true;
    } else if (lhs == NULL) {
        return false;
    } else if (rhs == NULL) {
        return false;
    }

    if (lhs->data != rhs->data) {
        return false;
    }

    return binary_tree_equal(lhs->left, rhs->left)
        && binary_tree_equal(lhs->right, rhs->right);
}

int binary_tree_depth(binary_tree* tree)
{
    if (tree == NULL) {
        return 0;
    }
    int lh = binary_tree_depth(tree->left);
    int rh = binary_tree_depth(tree->right);
    if (lh >= rh) {
        return lh + 1;
    } else {
        return rh + 1;
    }
}

binary_tree* binary_tree_init(num_pattern* pattern)
{
    binary_tree* root = malloc(sizeof(binary_tree));
    binary_leaf_init(root, pattern->d);
    for (
        num_pattern* ptn = pattern->parent;
        ptn != NULL;
        ptn = ptn->parent) {
        binary_tree_insert(&root, ptn->d);
    }
    return root;
}

void binary_leaf_init(binary_tree* leaf, int d)
{
    leaf->data = d;
    leaf->left = NULL;
    leaf->right = NULL;
}

void binary_tree_insert(binary_tree** tree, int d)
{
    binary_tree** insert_tree = (*tree)->data > d ? &(*tree)->left : &(*tree)->right;
    if (*insert_tree == NULL) {
        binary_tree* leaf = malloc(sizeof(binary_tree));
        binary_leaf_init(leaf, d);
        *insert_tree = leaf;
    } else {
        binary_tree_insert(insert_tree, d);
    }
}

int BTP_width(int depth)
{
    if (depth <= 0) {
        return 0;
    }
    if (depth == 1) {
        return 1;
    }

    if (depth == 2) {
        return 5;
    }
    return 2 * BTP_width(depth - 1) + 1;
}

int BTP_height(int depth)
{
    if (depth <= 0) {
        return 0;
    }
    if (depth == 1) {
        return 1;
    }
    return BTP_height(depth - 1) + depth;
}

void BTP(binary_tree* tree, char** field, int x, int y)
{
    // printf("(%d, %d) depth: %d\n", x, y, binary_tree_depth(tree));
    if (tree == NULL) {
        return;
    }
    // print itself
    field[y][x] = '0' + tree->data;

    // print lhs
    int ldepth = binary_tree_depth(tree->left);
    int ly = y;
    int lx = x;
    for (int i = 0; i < ldepth; i++) {
        field[++ly][--lx] = '/';
    }
    BTP(tree->left, field, --lx, ++ly);

    // print rhs
    int rdepth = binary_tree_depth(tree->right);
    int ry = y;
    int rx = x;
    for (int i = 0; i < rdepth; i++) {
        field[++ry][++rx] = '\\';
    }
    BTP(tree->right, field, ++rx, ++ry);
}

void binary_tree_print(binary_tree* tree)
{
    int depth = binary_tree_depth(tree);
    // alloc
    char** field;
    int width = BTP_width(depth);
    int height = BTP_height(depth);
    field = malloc(sizeof(char*) * height);

    for (int i = 0; i < height; i++) {
        field[i] = malloc(sizeof(char) * width);
        for (int w = 0; w < width; w++) {
            field[i][w] = ' ';
        }
    }

    // printf("depth: %d -> estimated size: %dx%d\n", depth, width, height);

    // print from center
    BTP(tree, field, width / 2, 0);

    // print to stdout and free them
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%c", field[y][x]);
        }
        free(field[y]);
        printf("\n");
    }
    printf("\n");
    free(field);
}

bool binary_tree_is_AVL(binary_tree* tree)
{
    int ldepth = binary_tree_depth(tree->left);
    int rdepth = binary_tree_depth(tree->right);
    return abs(ldepth - rdepth) <= 1
        && binary_tree_is_complete(tree->left)
        && binary_tree_is_complete(tree->right);
}

int binary_tree_count(binary_tree* tree)
{
    if (tree == NULL) {
        return 0;
    }
    return 1 + binary_tree_count(tree->left) + binary_tree_count(tree->right);
}

bool binary_tree_is_complete(binary_tree* tree)
{
    if (tree == NULL) {
        return true;
    }
    int lc = binary_tree_count(tree->left);
    int rc = binary_tree_count(tree->right);
    return abs(lc - rc) <= 1
        && binary_tree_is_complete(tree->left)
        && binary_tree_is_complete(tree->right);
}
