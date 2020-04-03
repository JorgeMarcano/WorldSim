#include "Tools.h"

void memoryCopy(void* source, void* dest, unsigned long size)
{
    if (source == NULL || dest == NULL)
        return;

    char* src = (char*) source;
    char* des = (char*) dest;

    for (unsigned long i = 0; i < size; i++)
        des[i] = src[i];

    return;
}
