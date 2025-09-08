#include <stdio.h>
#include "logs.h"

void putlog(int log_st, char* log_message){
    if(log_st!=0){
        fputs(log_message, stdout);
    }
}