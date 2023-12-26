#include "binary_tree.h"
#include "enumeration.h"
#include <stdio.h>

extern int BTP_width(int);
extern int BTP_height(int);

int main()
{
    for (int i = 0; i < 10; i++) {
        printf("depth %d -> %dx%d\n", i, BTP_width(i + 1), BTP_height(i + 1));
    }
}
