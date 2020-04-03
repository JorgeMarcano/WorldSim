#include "Mainloop.h"

void Mainloop(State* state)
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
            currElement = getObject(i, state);
            currElement = state->objectUpdater(currElement, i, 
                                                state->objects, 
                                                state->objectCount, 
                                                state->spaces,
                                                state->spaceCount);
            setObject(currElement, swapObjects, i, state);
        }

        //For every space element
        for (Size i = 0; i < state->spaceCount; i++)
        {
            currElement = getSpace(i, state);
            currElement = state->spaceUpdater(currElement, i, 
                                                state->objects, 
                                                state->objectCount, 
                                                state->spaces,
                                                state->spaceCount);
            setSpace(currElement, swapSpaces, i, state);
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

    return;
}