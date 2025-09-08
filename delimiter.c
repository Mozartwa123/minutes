#include <stdio.h>
#include "delimiter.h"

void show_delimiter(dmit d){
    if(d.show) putchar(d.c);
}