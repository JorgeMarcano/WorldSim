#ifndef LOGGER_H
#define LOGGER_H

#include "../State/State.h"

typedef char* (*PrintState)(void* object, Size objectSize, void* spaces, Size spacesSize);

typedef struct Logger
{
    FILE* file;
    PrintState printer;
} Logger;

void LPrintState(PrintState printer, State* state);
Logger* StartLog(char* filename, PrintState printer);
void LogState(Logger* logger, State* state);
void EndLog(Logger* logger);

#endif
