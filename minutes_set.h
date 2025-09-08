#include "minutes.h"

typedef struct minute_set_struct* mset;
typedef struct minute_set_struct{
    minute* minute_tab;
    int len;
    int realen;
} msetalias;

int minute_set_null(mset x);
void free_mset(mset x, int log_enabled);
mset mset_allocate(int initial_size, int log_wanted);
mset mset_reallocate(mset x, int newsize, int log_wanted);
mset load_mset(int initial_set_size, int initial_int_data_size, int log_wanted);
void print_mset(int enable_puctors_minutes, int enable_punctors_intdata, char delimitter_minutes, char delimitter_intdata, mset x);
minute sumset(mset x, int log_wanted);