#include <stdio.h>
#include <stdlib.h>


void rageQuit(const char* fname, int lineno, const char* fxname, char* msg){
    fprintf(stderr, "[ERROR] %s\nin %s/%s(..) at line %d.\n", msg, fname, fxname, lineno);
    exit(1);
}


