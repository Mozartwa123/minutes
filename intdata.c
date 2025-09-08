#include <stdlib.h>
#include <stdio.h>
#include "logs.h"
#include "intdata.h"
// #include "delimiter.h"

int isnull_intdata(intdata x){
    if(x == NULL){
        fputs("Given intdata is null!\n", stderr);
        return 1;
    }
    if(x -> inttab == NULL){
        fputs("Given intdata inttab is null!\n", stderr);
        return 2;
    }
    return 0;
}

void free_intdata(intdata x, int log_wanted){
    switch (isnull_intdata(x))
    {
    case 1:
        return;
    case 0:
        free(x -> inttab);
        putlog(log_wanted, "Inttab is free");
        x -> inttab = NULL;
        free(x);
        putlog(log_wanted, "Intdata is free\n");
        x = NULL;
        break;
    default:
        free(x);
        putlog(log_wanted, "Intdata is free\n");
        x = NULL;
        break;
    }
}

intdata make_intdata(int intdata_initial_size){
    intdata x = (intdata)malloc(sizeof(intdata_alias));
    if(x == NULL){
        fprintf(stderr, "Intdata alocation error\n");
        return NULL;
    }
    int* inttab = (int*)malloc(intdata_initial_size * sizeof(int));
    if(inttab == NULL){
        fprintf(stderr, "Fail to allocate %i ints\n", intdata_initial_size);
        free(x);
        return NULL;
    }
    x -> inttab = inttab;
    x -> realen = intdata_initial_size;
    x -> len = 0;
    return x;
}

intdata realloc_intdata(intdata x, int newsize, int log_wanted){
    if(isnull_intdata(x)){
        return NULL;
    }
    if(x -> len == newsize){
        return x;
    }
    int* temp = x -> inttab;
    //printf("%i\n", newsize);
    x -> inttab = (int*)realloc(x -> inttab, newsize * sizeof(int));
    if(x -> inttab == NULL){
        fprintf(stderr, "Fail to reallocate to %i ints\n", newsize);
        x -> inttab = temp;
        free_intdata(x, log_wanted);
    }
    x -> realen = newsize;
    return x;
}

intdata load_intdata(int log_wanted, int intdata_initial_size, FILE* source_stream){
    //printf("Data\n");
    intdata x = make_intdata(intdata_initial_size);
    if(isnull_intdata(x)){
        return NULL;
    }
    int i = 0;
    int data;
    char c = ' ';
    for(; c != '\n' && fscanf(source_stream,"%i", &data) == 1; i++){
        //printf("Data\n");
        c = fgetc(source_stream);
        if(i == x -> realen){
            if(realloc_intdata(x, x->realen + intdata_initial_size, log_wanted) == NULL){
                return NULL;
            }
        }
        (x -> inttab)[i] = data;
    }
    if(i < x -> realen){
        if(realloc_intdata(x, i, log_wanted) == NULL){
                return NULL;
        }
    }
    //fclose(source_stream);
    x -> len = i;
    return x;
}

void print_int_data(int enable_punctors, char delimiter, intdata x){
    if(isnull_intdata(x)){
        return;
    }
    for(int i = 0; i < x -> len; i++){
        if(enable_punctors){
            printf("%i. ", i);
        }
        printf("%i%c", (x->inttab)[i], delimiter);
    }
}


intdata cp_intdata(intdata x){
    intdata x1 = make_intdata(x -> len);
    if(isnull_intdata(x1)){
        return NULL;
    }
    for(int i = 0; i < x -> len; i++){
        (x1 -> inttab)[i] = (x -> inttab)[i];
    }
    x1 -> len = x -> len;
    x1 -> realen = x -> realen;
    return x1;
}

int addints(int x, int y){
    return x + y;
}

int divints(int x, int y){
    return x / y;
}

intdata calculate_intdatas(intdata x, intdata y, int (*calucation)(int, int)){
    if(isnull_intdata(x) || isnull_intdata(y)) return NULL;
    intdata result;
    intdata adding;
    if(y -> len < x -> len) {
        result = cp_intdata(x);
        adding = y;
    } else { 
        result = cp_intdata(y); 
        adding = x; 
    }
    if(isnull_intdata(result)) return NULL;
    for(int i = 0; i < adding -> len; i++){
        (result -> inttab)[i] = calucation((result -> inttab)[i], (adding -> inttab)[i]);
    }
    return result;
}

intdata calculate_intdata_by_int(intdata x, int con, int (*calucation)(int, int)){
    if(isnull_intdata(x)) return NULL;
    for(int i = 0; i < x -> len; i++){
        (x -> inttab)[i] = calucation((x -> inttab)[i], con);
    }
    return x;
}

rsucc read_col(intdata x, int col){
    if(isnull_intdata(x)){
        rsucc a = { 0, 1 };
        return a;
    }
    if(col >= x -> len){
        rsucc a = { 1, 1 };
        fprintf(stderr, "Number of expected column %i is greater than quantity of avaiable columns %i", col, x -> len);
        return a;
    }
    rsucc a = { (x -> inttab)[col], 0 };
    return a;
}
