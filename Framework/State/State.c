#include "State.h"

void* getSpace(Size index, void* spaces, Size size)
{
    if (spaces == NULL)
        return NULL;

    char* loc = spaces;

    loc = loc + (index * size);

    return (void*) loc;
}

void* getObject(Size index, void* objects, Size size)
{
    if (objects == NULL)
        return NULL;

    char* loc = objects;

    loc = loc + (index * size);

    return (void*) loc;
}

Result setSpace(void* space, void* spaces, Size index, State* state)
{
    if (state == NULL || space == NULL || spaces == NULL)
        return ERROR_NULL;
    if (index >= state->spaceCount)
        return ERROR_INDEX_OOB;

    void* destLocation = getSpace(index, state->spaces, state->spaceSize);

    memoryCopy(space, destLocation, state->spaceSize);

    return ERROR_NONE;
}

Result setObject(void* object, void* objects, Size index, State* state)
{
    if (state == NULL || object == NULL || objects == NULL)
        return ERROR_NULL;
    if (index >= state->objectCount)
        return ERROR_INDEX_OOB;

    void* destLocation = getObject(index, state->objects, state->objectSize);

    memoryCopy(object, destLocation, state->objectSize);

    return ERROR_NONE;
}
