#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "../State/State.h"
#include "../Error/Error.h"
#include "../Logger/Logger.h"

#include <stdlib.h>

Result Mainloop(State* state, Logger* logger);

#endif
