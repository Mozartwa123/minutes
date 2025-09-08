#include "intdata.h"
#include <stdio.h>

int main(){
    intdata x = load_intdata(1, 10);
    intdata y = load_intdata(1, 10);
    if(isnull_intdata(x) || isnull_intdata(y)){
        return 1;
    }
    print_int_data(0, ';', x);
    putchar('\n');
    print_int_data(0, ';', y);
    putchar('\n');
    intdata z = calculate_intdatas(x, y, addints);
    if(isnull_intdata(z)){
        return 1;
    }
    print_int_data(0, ';', z);
    putchar('\n');
    free_intdata(x, 1);
    free_intdata(y, 1);
    return 0;
}