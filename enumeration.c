#include "enumeration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

num_list* num_list_delete(num_list* list, int d)
{
    for (num_list* ptr = list->next; ptr != list; ptr = ptr->next) {
        if (ptr->d == d) {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            return ptr;
        }
    }
    return NULL;
}

void num_list_deinit(num_list* list)
{
    for (num_list* iter = list->next; iter != list;) {
        iter = iter->next;
        free(iter->prev);
    }
    free(list);
}

void num_pattern_print(num_pattern* ptn)
// {
//     if (ptn == NULL) {
//         return;
//     }
//     if (ptn->parent == NULL) {
//         printf("%d ", ptn->d);
//     } else {
//         num_pattern_print(ptn->parent);
//         printf("%d ", ptn->d);
//     }
// }

// void num_pattern_print_reversed(num_pattern* ptn)
{
    printf("%d ", ptn->d);
    if (ptn->parent != NULL) {
        num_pattern_print(ptn->parent);
    }
}

num_pattern_list expand(num_pattern* array, num_list* list)
{
    // printf("expands ");
    // num_pattern_print(array);
    // printf("\n");
    if (list->next == list && list->prev == list) {
        num_pattern_list result;
        num_pattern_list_init(&result);
        if (array == NULL) {
            return result;
        }
        num_pattern_list_add(&result, array);
        return result;
    }

    num_pattern_list result;
    num_pattern_list_init(&result);
    for (num_list* iter = list->next; iter != list; iter = iter->next) {
        num_pattern* new_pattern = num_pattern_add(array, iter->d);
        num_list* num_list_c = num_list_copy(list);
        free(num_list_delete(num_list_c, iter->d));
        // printf("deleting %d\n", iter->d);
        num_pattern_list rec_expand = expand(new_pattern, num_list_c);
        num_pattern_list_concat(&result, rec_expand);
        num_list_deinit(num_list_c);
    }
    return result;
}

void num_pattern_list_concat(num_pattern_list* lhs, num_pattern_list rhs)
{
    for (int i = 0; i < rhs.size; i++) {
        num_pattern_list_add(lhs, rhs.patterns[i]);
    }
}

num_list* num_list_copy(num_list* list)
{
    num_list* result = num_list_init(0);
    for (num_list* ptr = list->next; ptr != list; ptr = ptr->next) {
        num_list_add(result, ptr->d);
    }
    return result;
}

num_list* num_list_add(num_list* list, int d)
{
    num_list* element = num_list_init(d);
    list->prev->next = element;
    element->prev = list->prev;
    element->next = list;
    list->prev = element;
    return list;
}

num_list* num_list_init(int d)
{
    num_list* result = malloc(sizeof(num_list));
    result->d = d;
    result->next = result;
    result->prev = result;
    return result;
}

void num_pattern_list_init(num_pattern_list* list)
{
    list->patterns = NULL;
    list->size = 0;
}

void num_pattern_list_add(num_pattern_list* list, num_pattern* pattern)
{
    list->patterns = realloc(list->patterns, sizeof(num_pattern*) * ++list->size);
    list->patterns[list->size - 1] = pattern;
}

num_pattern* num_pattern_add(num_pattern* pattern, int d)
{
    num_pattern* new = malloc(sizeof(num_pattern));
    new->d = d;
    new->parent = pattern;
    return new;
}

num_pattern_list get_all_pattern(int start, int end)
{

    // making [start...end]
    num_list* list = num_list_init(0);
    for (int i = start; i <= end; i++) {
        // printf("%d ", i);
        num_list_add(list, i);
    }
    // printf("\n");

    num_pattern_list result = expand(NULL, list);
    num_list_deinit(list);

    return result;
}

void num_pattern_list_print(num_pattern_list list)
{
    for (int i = 0; i < list.size; i++) {
        num_pattern_print(list.patterns[i]);
        printf("\n");
    }
}
