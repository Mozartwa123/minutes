/*

typedef enum partype{
    Int, String, Float
} partype;

typedef struct flags_parameter {
    char* parameter_name;
    partype ptype;
    void* value;
} flpar;

*/

typedef enum sortord{
    Ascending_order, Desceding_order, Disable
} sbl;

typedef struct sorting_options{
    sbl opt;
    int row; // if row=-1, minutes will be sorted by minutes_lenght
} sopt;

extern int starting_point; // if value is negative there is no limitation
extern int ending_point; // if value is negative - it dispays |n| last lines
extern int enable_logging;
extern sopt sort_method;
