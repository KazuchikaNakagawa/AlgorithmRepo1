#ifndef ENUMERATION_H
#define ENUMERATION_H

#include <sys/_types/_size_t.h>

typedef struct _num_pattern {
    struct _num_pattern* parent;
    int d;
} num_pattern;

typedef struct {
    num_pattern** patterns;
    unsigned size;
} num_pattern_list;

typedef struct _num_list {
    struct _num_list* next;
    struct _num_list* prev;
    int d;
} num_list;

num_list* num_list_copy(num_list* list);
num_list* num_list_add(num_list* list, int d);
num_list* num_list_init(int d);
void num_list_deinit(num_list*);

num_pattern* num_pattern_add(num_pattern*, int);
void num_pattern_print(num_pattern*);

void num_pattern_list_init(num_pattern_list*);
void num_pattern_list_add(num_pattern_list*, num_pattern*);
void num_pattern_list_concat(num_pattern_list*, num_pattern_list);
void num_pattern_list_print(num_pattern_list);

num_pattern_list get_all_pattern(int start, int end);

num_pattern_list expand(num_pattern*, num_list*);

#endif