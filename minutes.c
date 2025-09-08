#include <stdlib.h>
#include <stdio.h>
#include "minutes.h"
#include "intdata.h"
#include "logs.h"

minute allocate_minute(int minutes, int seconds, intdata film_data){
    minute new_minute = (minute)malloc(sizeof(minute_alias));
    if(new_minute == NULL){
        fprintf(stderr, "Błąd alokacji dla %i:%i ", minutes, seconds); print_int_data(0, ' ', film_data);
        return NULL;
    }
    new_minute->minutes = minutes;
    new_minute->seconds = seconds;
    new_minute->film_data = film_data;
    return killcarryseconds(new_minute);
}

void free_minute(minute del_minute, int log_wanted){
    if(del_minute == NULL){
        fputs("Double free prevented!\n", stderr);
        return;
    }
    free_intdata(del_minute -> film_data, log_wanted);
    free(del_minute);
    del_minute = NULL;
}

minute killcarryseconds(minute susminute){
    if(susminute == NULL){
        fputs("Given datas are NULL!\n", stderr);
        return NULL;
    }
    if(susminute->seconds > 59){
        susminute -> seconds -= 60;
        (susminute->minutes)++;
    }
    return susminute;
}

minute sum_two_minutes(minute fst_minute, minute snd_minute, int log_wanted){
    if(fst_minute == NULL || snd_minute == NULL){
        fputs("One of given datas are NULL!\n", stderr);
        return NULL;
    }
    fst_minute -> minutes += snd_minute->minutes;
    fst_minute -> seconds += snd_minute->seconds;
    intdata temp = calculate_intdatas(fst_minute -> film_data, snd_minute -> film_data, addints);
    if(temp == NULL){
        putlog(log_wanted, "Error during summing minutes: "); print_minute_as_log(log_wanted, fst_minute); putchar('\n'); print_minute_as_log(log_wanted, snd_minute);
        return NULL;
    }
    free_intdata(fst_minute -> film_data, log_wanted);
    fst_minute -> film_data = temp;
    //free_minute(snd_minute, log_wanted);
    return killcarryseconds(fst_minute);
}

void print_minute(int enable_puctors, char delimitter, minute printed){
    if(printed == NULL){
        fputs("Given datas are NULL!\n", stderr);
        return;
    }
    printf("%i:%i ", printed->minutes, printed->seconds); print_int_data(enable_puctors, delimitter, printed -> film_data);
}

void print_minute_as_log(int log_st, minute printed){
    if(log_st){
        print_minute(0, ' ', printed);
    }
}

int isnull(minute susminute){
    if(susminute == NULL){
        fputs("ISNULL: Given datas are NULL!\n", stderr);
        return 1;
    }
    return 0;
}

minute loadminute(int intdata_inital_size, int log_wanted){
    int min, sec;
    if(scanf("%i:%i", &min, &sec)!=2){
        fputs("Reading data error! The input should be minutes:seconds [additional int data] \n", stderr);
        return NULL;
    }
    getchar();
    intdata film_data = load_intdata(log_wanted, intdata_inital_size);
    if(isnull_intdata(film_data)) return NULL;
    minute new_minute = allocate_minute(min, sec, film_data);
    if(isnull(new_minute)){
        return NULL;
    }
    putlog(log_wanted, "Minute allocated succsessfully!\n");
    return new_minute;
}

int minutescmp(minute fst_minute, minute snd_minute){
    if(isnull(fst_minute) || isnull(snd_minute)){
        return -2;
    }
    int minute_cmp = fst_minute->minutes > snd_minute->minutes ? 1 
    : (fst_minute->minutes < snd_minute->minutes ? -1 : 0);
    if(minute_cmp!=0){
        return minute_cmp;
    }
    int snd_cmp = fst_minute->seconds > snd_minute->seconds ? 1
    : (fst_minute->seconds < snd_minute->seconds ? -1 : 0);
    return snd_cmp;
}

int minutescmp_rev(minute fst_minute, minute snd_minute){
    int n = minutescmp(fst_minute, snd_minute);
    return n == -2 ? -2 : ((n ^ (-1)) + 1);
}

int compare_by_film_data_row(minute fst_minute, minute snd_minute, int film_data_row_num){
    if(isnull(fst_minute) || isnull(snd_minute)){
        return -2;
    }
    rsucc preread1 = read_col(fst_minute -> film_data, film_data_row_num);
    rsucc preread2 = read_col(snd_minute -> film_data, film_data_row_num);
    if(preread1.failed || preread2.failed){
        return -3;
    }
    int data1 = preread1.read;
    int data2 = preread2.read;
    //printf("comparing %i and %i", fst_minute->displays, snd_minute->displays);
    return data1 > data2 ? 1 : (data1 == data2 ? 0 : -1);
}

minute copy_minute(minute copied){
    if(isnull(copied)){
        return NULL;
    }
    intdata x = cp_intdata(copied -> film_data);
    return allocate_minute(copied->minutes, copied->seconds, x);
}

int copy_minutes_compare(minute suss, minute curr, 
    int (*minute_comparing_fun)(minute, minute), int* curr_pos, int suss_pos){
    if(isnull(suss) || isnull(curr)){
        return -2;
    }
    int cmp_res = minute_comparing_fun(suss, curr);
    if(cmp_res == 1){
        curr->minutes = suss-> minutes;
        curr->seconds = suss-> seconds;
        curr->film_data = suss -> film_data;
        *curr_pos = suss_pos;
    }
    return cmp_res;
}

minute divide_int_minute(minute divided, int divider){
    if(isnull(divided)){
        return NULL;
    }
    divided->minutes/=divider;
    divided->seconds/=divider;
    divided->film_data = calculate_intdata_by_int(divided->film_data, divider, divints);
    return divided;
}