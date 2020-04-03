#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

typedef unsigned char Result;

#define ERROR_NONE              0
#define ERROR_NULL              1
#define ERROR_LOAD_OBJ          2
#define ERROR_LOAD_SPACE        3
#define ERROR_LOAD_PHYS         4
#define ERROR_INDEX_OOB         5

char* GetResultCode(Result result);

void PrintResultCode(Result result);

#endif
