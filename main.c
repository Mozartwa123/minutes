#include "minutes_set.h"
#include <stdio.h>
#include "minute_data.h"
 // #include <stdio.h>

int main(void){
    mset x = load_mset(10, 10, 0);
    print_mset(0, 0, '\n', ' ', x);
    minute m = sumset(x, 0);
    print_minute(0, ' ', m);
    putchar('\n');
    m = divide_int_minute(m, x -> len);
    print_minute(0, ' ', m);
    putchar('\n');
    sort_minutes_by_len(x, void_minutescmp);
    puts("Sorting");
    print_mset(0, 0, '\n', ' ', x);
    qsort_minutes_by_row(x, 1, compare_by_film_data_row);
    print_mset(0, 0, '\n', ' ', x);
    free_mset(x, 0);
}