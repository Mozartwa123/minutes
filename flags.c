#include "flags.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int starting_point = -42;
int ending_point = 0;
int enable_logging = 0;
sopt sort_method = {-1, Disable};
sbl sorting_order_len = Disable;

char** get_parameter_and_value(char* flag){
    char** output = (char**)malloc(sizeof(char*) * 2);
    output[0] = strtok_r(flag, "=", &flag);
    output[1] = strtok_r(flag, "=", &flag);
    return output;
}


void read_parameters (int argc, char** argv){
    for(int i = 1; i < argc; i++){
        char** tab = get_parameter_and_value(argv[i]);
        /*
        for(int i = 0; i < 2; i++){
            if(argv[i] != NULL){
                printf("%s ", tab[i]);
            }
        }*/
        if(tab && tab[0]){
            if(!strcmp(tab[0], "--help")){
                puts("Welcome to the \"minutes\" program!");

                puts("USAGE: minutes [OPTIONS] [FILE]");
                puts("minutes -> read data from standart input");
                puts("--read-file=filename -> read data from the text file, which name is filename. Alternatevily you can use minutes < FILE");
                puts("--help -> display help info and exit");
                puts("--enable-logs -> enable logging");
                puts("--show-first-lines=n -> show first n lines of the calculations");
                puts("--show-lines-range=n+m -> show n, n + 1 ..., m - 1, m lines");
                puts("--show-last-lines=n -> show last n lines");
                puts("--sort-by-len=option -> sort minutes by lenght (avaiable options: asceding, desceding, disable - the last is by default)");
                puts("--sort-by-row=n+option -> sort by n - 1 row (not including minutes), option, like higher");
                if(argc < 3){
                    free(tab);
                    exit(0);
                }
            } if (!strcmp(tab[0], "--enable-logs")){
                puts("Logs enabled");
                enable_logging = 1;
            } else if(tab[1]){
                if(!strcmp(tab[0], "--show-first-lines")){
                    char* endptr;
                    int lines_quantity = (int)strtoul(tab[1], &endptr, 10);
                    if(strcmp(endptr, "")){
                        puts("Invalid input. Type \"minutes --help\" for more information");
                    } else {
                        starting_point = 0;
                        ending_point = lines_quantity;
                        printf("Set starting_point to %i to %i\n", starting_point, ending_point);
                    }
                } else if(!strcmp(tab[0], "--sort-by-len")){
                    if(!strcmp(tab[1], "asceding")){
                        sorting_order_len = Ascending_order;
                        printf("Order will be asceding (by minutes lenght)\n");
                    } else if(!strcmp(tab[1], "desceding")){
                        sorting_order_len = Desceding_order;
                        printf("Order will be asceding (by minutes lenght)\n");
                    } else if(!strcmp(tab[1], "disable")){
                        sorting_order_len = Disable;
                        printf("Sorting disabled!\n");
                    } else {
                        puts("Invalid input. Type \"minutes --help\" for more information");
                    }
                } else if(!strcmp(tab[0], "--show-lines-range")){
                    char* n_str = strtok_r(tab[1], "+", &tab[1]);
                    char* m_str = strtok_r(tab[1], "+", &tab[1]);
                    if(n_str && m_str){
                        char* end_ptr;
                        int n = (int)strtoul(n_str, &end_ptr, 10);
                        int m = (int)strtoul(m_str, &end_ptr, 10);
                        if(strcmp(end_ptr, "")){
                            puts("Invalid input. Type \"minutes --help\" for more information");
                        } else {
                            starting_point = n;
                            ending_point = m;
                            printf("Set starting_point to %i to %i\n", starting_point, ending_point);
                        }
                    }
                } else {
                    puts("Invalid input or unimplemented option. Type \"minutes --help\" for more information");
                }
            }
        }
        putchar('\n');
        free(tab);
    }
}

int main(int argc, char** argv){
    read_parameters(argc, argv);
}