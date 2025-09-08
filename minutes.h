#include "intdata.h"

typedef struct minute_struct* minute;
typedef struct minute_struct{
    int seconds;
    int minutes;
    intdata film_data;
} minute_alias;

minute allocate_minute(int minutes, int seconds, intdata film_data);
void free_minute(minute del_minute, int log_wanted);
minute killcarryseconds(minute susminute);
minute sum_two_minutes(minute fst_minute, minute snd_minute, int log_wanted);
void print_minute(int enable_puctors, char delimitter, minute printed);
int isnull(minute susminute);
minute loadminute(int intdata_inital_size, int log_wanted, FILE* source_stream);
minute copy_minute(minute copied);
int minutescmp(minute fst_minute, minute snd_minute);
int compare_by_film_data_row(minute fst_minute, minute snd_minute, int film_data_row_num);
void print_minute_as_log(int log_st, minute printed);
int minutescmp_rev(minute fst_minute, minute snd_minute);
minute copy_minute(minute copied);
int copy_minutes_compare(minute suss, minute curr, int (*minute_comparing_fun)(minute, minute), int* curr_pos, int suss_pos);
minute divide_int_minute(minute divided, int divider);
