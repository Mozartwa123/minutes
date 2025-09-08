#include "minutes.h"
#include "minutes_set.h"

void sort_minutes_by_len(mset x, int (*cmpfun)(const void*, const void*));
int void_minutescmp(const void* fst_minute, const void* snd_minute);
void qsort_minutes_by_row(mset x, int sorted_by, int (*rowcmp)(minute, minute, int));