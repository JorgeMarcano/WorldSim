#include "Mainloop.h"

Result Mainloop(State* state)
{
    int isRunning = 1;

    void* currElement;

    //Create our swap buffers
    void* swapObjects = malloc(state->objectSize * state->objectCount);
    void* swapSpaces = malloc(state->spaceSize * state->spaceCount);

    while(isRunning)
    {
        //For every object
        for (Size i = 0; i < state->objectCount; i++)
        {
            state->objectUpdater(getObject(i, state->objects, state->objectSize),
                                    getObject(i, swapObjects, state->objectSize),
                                    i,
                                    state->objects,
                                    state->objectCount,
                                    state->spaces,
                                    state->spaceCount);
        }

        //For every space element
        for (Size i = 0; i < state->spaceCount; i++)
        {
            state->spaceUpdater(getSpace(i, state->spaces, state->spaceSize),
                                    getSpace(i, swapSpaces, state->spaceSize),
                                    i,
                                    state->objects,
                                    state->objectCount,
                                    state->spaces,
                                    state->spaceCount);
        }

        //Swap both buffers
        currElement = state->objects;
        state->objects = swapObjects;
        swapObjects = currElement;

        currElement = state->spaces;
        state->spaces = swapSpaces;
        swapSpaces = currElement;

        //Log state

        //Update isRunning
        //currently, temporarily simply runs one billion times
        isRunning++;
        isRunning %= 10000000;
    }

    //Free out swap buffers
    free(swapObjects);
    free(swapSpaces);

    return ERROR_NONE;
}
