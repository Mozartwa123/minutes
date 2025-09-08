#include <stdio.h>

typedef struct intdata_struct* intdata;
typedef struct intdata_struct{
    int len; //number of integers in inttab
    int realen; // number of rows in inttab
    int* inttab; // the set of integers
} intdata_alias;

typedef struct reading_succsess {
    int read;
    int failed;
} rsucc;

int isnull_intdata(intdata x); // 1 -> x is NULL, 2 -> x is not null, but x -> inttab is null, 0 -> x is not null at all
void free_intdata(intdata x, int log_wanted); // save wrapper for deleting inttdata
intdata make_intdata(int intdata_initial_size); // create empty intdata with given initial size
intdata realloc_intdata(intdata x, int newsize, int log_wanted); //realoc intdata x to newsize with logging enabled
intdata load_intdata(int log_wanted, int intdata_initial_size, FILE* source_stream); //load intdata with separated by single-char delimitter
void print_int_data(int enable_punctors, char delimiter, intdata x); //print intdata with optional punctors (0 disables punctors), given delimitter
intdata cp_intdata(intdata x);
intdata calculate_intdatas(intdata x, intdata y, int (*calucation)(int, int));
int addints(int x, int y);
int divints(int x, int y);
rsucc read_col(intdata x, int col);
intdata calculate_intdata_by_int(intdata x, int con, int (*calucation)(int, int));