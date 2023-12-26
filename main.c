#include "binary_tree.h"
#include "enumeration.h"
#include <stdio.h>

int main()
{
    int d;
    printf("input a number from 1...9: ");
    scanf("%d", &d);
    num_pattern_list_print(get_all_pattern(1, d));
    num_pattern_list list = get_all_pattern(1, d);
    printf("trees generated:\n");
    array trees;
    array_init(&trees);

    float height_overall = 0;
    float complete_height_overall = 0;
    float AVL_height_overall = 0;

    float height_sq_overall = 0;
    float complete_sq_height_overall = 0;
    float AVL_height_sq_overall = 0;

    int count;
    int complete_count = 0;
    int AVL_count = 0;

    for (int i = 0; i < list.size; i++) {
        binary_tree* tree = binary_tree_init(list.patterns[i]);
        int duplicated = 0;
        for (int j = 0; j < trees.size; j++) {
            binary_tree* existing = trees.buf[j];
            if (binary_tree_equal(existing, tree)) {
                duplicated = 1;
                break;
            }
        }

        if (duplicated == 1) {
            continue;
        }

        count++;
        int depth = binary_tree_depth(tree) - 1;
        if (binary_tree_is_complete(tree)) {
            complete_count++;
            AVL_count++;
            complete_height_overall += depth;
            complete_sq_height_overall += depth * depth;
            AVL_height_overall += depth;
            AVL_height_sq_overall += depth * depth;
        } else if (binary_tree_is_AVL(tree)) {
            AVL_count++;
            AVL_height_overall += depth;
            AVL_height_sq_overall += depth * depth;
        }

        height_overall += depth;
        height_sq_overall += depth * depth;

        *array_new_element_ptr(&trees) = tree;
        if (binary_tree_is_complete(tree)) {
            num_pattern_print(list.patterns[i]);
            printf("\n");
            binary_tree_print(tree);
        }
    }

    float height_aver = height_overall / count;
    float height_variance = height_sq_overall / count - height_aver * height_aver;
    printf("binary tree: \n\t%d types\n\taverage: %f\n\tvariance: %f\n", count, height_aver, height_variance);

    float complete_height_aver = complete_height_overall / complete_count;
    float complete_height_variance = complete_sq_height_overall / complete_count - complete_height_aver * complete_height_aver;
    printf("complete binary tree: \n\t%d types\n\taverage: %f\n\tvariance: %f\n", complete_count, complete_height_aver, complete_height_variance);

    float AVL_height_aver = AVL_height_overall / AVL_count;
    float AVL_height_variance = AVL_height_sq_overall / AVL_count - AVL_height_aver * AVL_height_aver;
    printf("AVL binary tree: \n\t%d types\n\taverage: %f\n\tvariance: %f\n", AVL_count, AVL_height_aver, AVL_height_variance);

    return 0;
}
