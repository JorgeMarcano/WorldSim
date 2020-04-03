#include "Error.h"

char* GetResultCode(Result result)
{
    switch(result)
    {
    case ERROR_NONE:
        return "ERROR NONE";
    case ERROR_NULL:
        return "ERROR NULL POINTER";
    case ERROR_LOAD_OBJ:
        return "ERROR LOADING OBJECT";
    case ERROR_LOAD_SPACE:
        return "ERROR LOADING SPACE";
    case ERROR_LOAD_PHYS:
        return "ERROR LOADING PHYSICS";
    }

    return "ERROR UNDEFINED";
}

void PrintResultCode(Result result)
{
    printf("%s", GetResultCode(result));
}