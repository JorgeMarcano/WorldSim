#include <stdio.h>
#include "Logger.h"
#include <stdlib.h>

void LPrintState(PrintState printer, State* state)
{
    char* print = printer(state->objects, state->objectCount, state->spaces, state->spaceCount);
    printf(print);
    printf("\n");
    free(print);
}

Logger* StartLog(char* filename, PrintState printer)
{
   Logger* logger = malloc(sizeof(Logger));

   logger->file = fopen (filename,"w");
   logger->printer = printer;

   return logger;
}

void LogState(Logger* logger, State* state)
{
    char* print = logger->printer(state->objects, state->objectCount, state->spaces, state->spaceCount);
    fprintf (logger->file, "%s\n", print);
    free(print);
}

void EndLog(Logger* logger)
{
    fclose(logger->file);
    free(logger);
}
