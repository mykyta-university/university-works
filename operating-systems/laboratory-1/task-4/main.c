#include <stdio.h>
#include "arraylist.h"

static void print_arraylist(ArrayList * list) {
    printf("[");
    for (int index = 0; index < list->size; ++index) {
        printf(" %d,", *((int*) arraylist_get(list, index)));
    }
    printf("]");
}




int main() {
    ArrayList * arrayList = arraylist_create(2);

    int a = 1, b = 2,  c = 3, d = 4, e = 5, f = 6, g = 7;
    int v = 100;
    int iv = 123;
    int iv2 = 321;

    arraylist_add(arrayList, (void *) &a);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_add(arrayList, (void *) &b);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_add(arrayList, (void *) &c);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_add(arrayList, (void *) &d);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_add(arrayList, (void *) &e);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_add(arrayList, (void *) &f);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_add(arrayList, (void *) &g);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_set(arrayList, 5, (void*) &v);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_insert(arrayList, 5, &iv);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_insert(arrayList, 5, &iv2);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    arraylist_remove(arrayList, 5);
                                                    print_arraylist(arrayList);
                                                    printf("\nLength: %d\n", arraylist_length(arrayList));
                                                    printf("\nSize: %d\n", arraylist_size(arrayList));
                                                    printf("\n");
    return 0;
}


