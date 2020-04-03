#ifndef LOADER_H
#define LOADER_H

#include "../State/State.h"
#include "../Error/Error.h"
#include <stdlib.h>

typedef Result (*InitializerObject)(void* object, Size objectIndex, void* spaces, Size spacesSize);
typedef Result (*InitializerSpace)(void* space, Size spaceIndex);

State* CreateStateInstance();

Result ReleaseStateInstance(State* state);

Result LoadObject(State* state, ObjectDesc* desc);
Result LoadSpace(State* state, SpaceDesc* desc);
Result LoadObjectAndSpace(State* state, ObjectDesc* descObj, SpaceDesc* descSpace);
Result LoadPhysics(State* state, UpdateObject objectUpdater, UpdateSpace spaceUpdater);
Result LoadAll(State* state,
                ObjectDesc* descObj,
                SpaceDesc* descSpace,
                UpdateObject objectUpdater,
                UpdateSpace spaceUpdater);

ObjectDesc* parseObject(char* ressource);
ObjectDesc* parseSpace(char* ressource);

Result LoadInitialState(State* state, InitializerObject objectInit, InitializerSpace spaceInit, Size objectCount, Size spaceCount);

#endif
