#include "minutes.h"
#include "minutes_set.h"
#include "logs.h"
#include <stdlib.h>
#include <stdio.h>

int minute_set_null(mset x){
    if(x == NULL || x -> minute_tab == NULL){
        fputs("Given mset is null!", stderr);
        return 1;
    }
    return 0;
}

void free_mset(mset x, int log_enabled){
    if(minute_set_null(x)){
        return;
    }
    for (int i = 0; i < x -> len; i++)
    {
        free_minute((x -> minute_tab)[i], log_enabled);
    }
    free(x -> minute_tab);
    free(x);
    x = NULL;
}

mset mset_allocate(int initial_size, int log_wanted){
    if(initial_size <= 0){
        fprintf(stderr, "Initial size must be greater than 0, but given value is %i\n", initial_size);
    }
    minute* mtab = (minute*)malloc(initial_size * sizeof(minute));
    if(mtab == NULL){
        return NULL;
    }
    mset newmset = (mset)malloc(sizeof(msetalias));
    if(newmset == NULL){
        free(mtab); 
        return NULL;
    }
    putlog(log_wanted, "Realocation succesfull\n");
    newmset -> len = 0;
    newmset -> realen = initial_size;
    newmset -> minute_tab = mtab;
    return newmset;
}

mset mset_reallocate(mset x, int newsize, int log_wanted){
    if(log_wanted){
        puts("REALOCATION!");
    }
    if(minute_set_null(x)){
        return NULL;
    }
    if(newsize <= x -> len){
        fprintf(stderr, "New size %i is smaller than quatity of elements in the set %i\n", newsize, x -> len);
        return NULL;
    }
    // size_t size = (size_t)(newsize * sizeof(minute));

    minute* temp = (minute*)realloc(x -> minute_tab, newsize * sizeof(minute));
    if(temp == NULL){
        fprintf(stderr, "Failed to reallocate to %i\n", newsize);
        free_mset(x, log_wanted);
        return 0;
    }
    x -> realen = newsize;
    x -> minute_tab = temp;
    return x;
}

mset load_mset(int initial_set_size, int initial_int_data_size, int log_wanted){
    mset x = mset_allocate(initial_set_size, log_wanted);
    if(minute_set_null(x)){
        return NULL;
    }
    x -> len = 0;
    while(1){
        if(x -> len >= x -> realen){
            //putlog(log_wanted, "UWAGA, REALOKACJA!");
            mset temp = mset_reallocate(x, x->realen + initial_set_size, log_wanted);
            if(temp == NULL){
                free_mset(x, log_wanted);
                return NULL;
            } else {
                x = temp;
            }
        }
        minute m = loadminute(initial_int_data_size, log_wanted);
        if(m == NULL){
            // printf("Sram!\n");
            return x;
        }
        //print_minute(0, ' ', m);
        (x->minute_tab)[x-> len] = m;
        x -> len = x -> len + 1;
    }
    if(x -> len < x -> realen){
        mset_reallocate(x, x -> realen, log_wanted);
    }
    return x;
}

void print_mset(int enable_puctors_minutes, int enable_punctors_intdata, char delimitter_minutes, char delimitter_intdata, mset x){
    if(minute_set_null(x)){
        return;
    }
    for(int i = 0; i < x->len; i++){
        if(enable_puctors_minutes){
            printf("%i) ", i);
        }
        print_minute(enable_punctors_intdata, delimitter_intdata, (x -> minute_tab)[i]);
        putchar(delimitter_minutes);
    }
}

minute sumset(mset x, int log_wanted){
    if(minute_set_null(x)){
        return NULL;
    }
    if(x -> len <= 0){
        fprintf(stderr, "Len must be greater than 0");
        return 0;
    }
    minute m = copy_minute((x -> minute_tab)[0]);
    for(int i = 1; i < x -> len; i++){
        minute nval = sum_two_minutes(m, (x -> minute_tab)[i], log_wanted);
        if(isnull(nval)){
            free_minute(m, log_wanted);
            return NULL;
        }
        m = nval;
    }
    return m;
}

minute get_minute(mset x, int i){
    if(i < 0){
        fprintf(stderr, "[Error] Demanded index %i is less than 0\n", i);
    }
    if(minute_set_null(x)){
        return NULL;
    }
    if(x -> len <= i){
        fprintf(stderr, "[Error] Demanded index %i is greater than lenght if mset %i\n", i, x -> len);
        return NULL;
    }
    return (x -> minute_tab)[i];
}