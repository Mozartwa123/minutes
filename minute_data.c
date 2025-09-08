#include "minutes.h"
#include "minutes_set.h"
#include "minute_data.h"
#include <stdlib.h>

int minute_void_converter(const void* fst_minute, const void* snd_minute, int (*cmpfun)(minute, minute)){
    return cmpfun(*(minute*)fst_minute, *(minute*)snd_minute);
}

int void_minutescmp(const void* fst_minute, const void* snd_minute){
    return minute_void_converter(fst_minute, snd_minute, minutescmp);
}

void sort_minutes_by_len(mset x, int (*cmpfun)(const void*, const void*)){
    if(minute_set_null(x)){
        return;
    }
    qsort(x -> minute_tab, x -> len, sizeof(minute), cmpfun);
}

/* 
    Now I would like to implement quick sort myself, because I had problems with using qsort to sort, 
    by different rows in intdata 
*/

int partition_minutes(mset x, int sorted_by, int b, int e, int (*rowcmp)(minute, minute, int)){
    minute* mtab = x->minute_tab;
    minute pivot = mtab[b];
    int i = b - 1;
    int j = e + 1;
    int cmpresult;
    while(1){
        do{
            i++;
            cmpresult = rowcmp(mtab[i], pivot, sorted_by);
        } while(cmpresult == -1);
        if(cmpresult < -1){
            return -42;
        }
        do{
            j--;
            cmpresult = rowcmp(mtab[j], pivot, sorted_by);
        } while(cmpresult == 1);
        if(cmpresult < -1){
            return -42;
        }
        if(i >= j){
            return j;
        }
        minute temp = mtab[i];
        mtab[i] = mtab[j];
        mtab[j] = temp;
    }
}

void quick_sort_minutes_help(mset x, int sorted_by, int b, int e, int (*rowcmp)(minute, minute, int)){
    if(e <= b){ return; }
    int p = partition_minutes(x, sorted_by, b, e, rowcmp);
    if(p == -42){
        return;
    }
    quick_sort_minutes_help(x, sorted_by, b, p, rowcmp);
    quick_sort_minutes_help(x, sorted_by, p+1, e, rowcmp);
}

void qsort_minutes_by_row(mset x, int sorted_by, int (*rowcmp)(minute, minute, int)){
    if(minute_set_null(x)){
        return;
    }
    quick_sort_minutes_help(x, sorted_by, 0, x -> len - 1, rowcmp);
}