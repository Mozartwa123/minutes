#include "minutes.h"
#include <stdlib.h>

int main(){
    minute x = loadminute(10, 1);
    while(x != NULL){
        print_minute(0, '\n', x);
        free_minute(x, 1);
        x = loadminute(10, 1);
    }
}