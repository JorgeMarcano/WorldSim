#include "Loader.h"

State* CreateStateInstance()
{
    return malloc(sizeof(State));
}

Result ReleaseStateInstance(State* state)
{
    if (state == NULL)
        return ERROR_NULL;

    if (state->objects)
        free(state->objects);

    if (state->spaces)
        free(state->spaces);

    if (state->objectDesc)
        free(state->objectDesc);

    if (state->spaceDesc)
        free(state->spaceDesc);

    free(state);

    return ERROR_NONE;
}

Result LoadObject(State* state, ObjectDesc* desc)
{
    if (desc == NULL)
        return ERROR_LOAD_OBJ;

    state->objectDesc = desc;
    state->objectSize = desc->size;

    return ERROR_NONE;
}

Result LoadSpace(State* state, SpaceDesc* desc)
{
    if (desc == NULL)
        return ERROR_LOAD_SPACE;

    state->spaceDesc = desc;
    state->spaceSize = desc->size;

    return ERROR_NONE;
}

Result LoadObjectAndSpace(State* state, ObjectDesc* descObj, SpaceDesc* descSpace)
{
    Result result;
    if ((result = LoadObject(state, descObj)) == ERROR_NONE)
        return LoadSpace(state, descSpace);

    return result;
}

Result LoadPhysics(State* state, UpdateObject objectUpdater, UpdateSpace spaceUpdater)
{
    if (state == NULL)
        return ERROR_LOAD_PHYS;

    state->objectUpdater = objectUpdater;
    state->spaceUpdater = spaceUpdater;

    return ERROR_NONE;
}

Result LoadAll(State* state,
                ObjectDesc* descObj,
                SpaceDesc* descSpace,
                UpdateObject objectUpdater,
                UpdateSpace spaceUpdater)
{
    Result result;
    if ((result = LoadObject(state, descObj)) == ERROR_NONE)
        if ((result = LoadSpace(state, descSpace)) == ERROR_NONE)
            return LoadPhysics(state, objectUpdater, spaceUpdater);

    return result;
}

Result LoadInitialState(State* state, InitializerObject objectInit, InitializerSpace spaceInit, Size objectCount, Size spaceCount)
{
    if (state == NULL)
        return ERROR_NULL;

    state->objects = malloc(state->objectSize * objectCount);
    state->objectCount = objectCount;

    state->spaces = malloc(state->spaceSize * spaceCount);
    state->spaceCount = spaceCount;

    for (Size i = 0; i < spaceCount; i++)
        spaceInit(getSpace(i, state->spaces, state->spaceSize), i);

    for (Size i = 0; i < objectCount; i++)
        objectInit(getObject(i, state->objects, state->objectSize), i, state->spaces, spaceCount);

    return ERROR_NONE;
}
