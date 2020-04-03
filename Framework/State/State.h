#ifndef STATE_H
#define STATE_H

typedef unsigned long Size;

typedef void* (*UpdateObject)(void* object, 
                                Size objectIndex,
                                void* objects, 
                                Size objectCount, 
                                void* spaces, 
                                Size spaceCount);
typedef void* (*UpdateSpace)(void* space, 
                                Size spaceIndex, 
                                void* objects, 
                                Size objectCount, 
                                void* spaces, 
                                Size spaceCount);

typedef struct ObjectDesc
{
    Size        size;
} ObjectDesc;

typedef struct SpaceDesc
{
    Size        size;
} SpaceDesc;

typedef struct State
{
    Size            objectCount;
    Size            spaceCount;

    Size            objectSize;
    Size            spaceSize;

    void*           objects;
    void*           spaces;

    UpdateObject    objectUpdater;
    UpdateSpace     spaceUpdater;

    ObjectDesc*      objectDesc;
    SpaceDesc*       spaceDesc;
} State;

void* getSpace(Size index, State* state);
void* getObject(Size index, State* state);

Result setSpace(void* space, void* spaces, Size index, State* state);
Result setObject(void* object, void* objects, Size index, State* state);

#endif