#include "../Framework/State/State.h"
#include "../Framework/Error/Error.h"
#include "../Framework/Loader/Loader.h"
#include "../Framework/Mainloop/Mainloop.h"

#include "Structs.h"

#include <stdlib.h>
#include <time.h>

void ObjectUpdate(void* object,
                    void* destObj,
                    Size objectIndex,
                    void* objects,
                    Size objectCount,
                    void* spaces,
                    Size spaceCount);

void SpaceUpdate(void* space,
                    void* destSpace,
                    Size spaceIndex,
                    void* objects,
                    Size objectCount,
                    void* spaces,
                    Size spaceCount);

Result InitObject(void* object, Size objectIndex, void* spaces, Size spacesSize);
Result InitSpace(void* space, Size spaceIndex);

int main()
{
    srand(time(0));

    //Instantiate State Object
    State* stateInstance = CreateStateInstance();

    Result result;

    //Load all the parts
    ObjectDesc descObj;
    descObj.size = (Size) sizeof(Object);
    SpaceDesc descSpace;
    descSpace.size = (Size) sizeof(Space);

    result = LoadAll(stateInstance, &descObj, &descSpace, ObjectUpdate, SpaceUpdate);
    if(result != ERROR_NONE)
    {
        PrintResultCode(result);
        ReleaseStateInstance(stateInstance);
        return (int) result;
    }

    //Load initial state
    result = LoadInitialState(stateInstance, InitObject, InitSpace, OBJECT_COUNT, SPACE_COUNT);
    if(result != ERROR_NONE)
    {
        PrintResultCode(result);
        ReleaseStateInstance(stateInstance);
        return (int) result;
    }

    //Start the Mainloop
    result = Mainloop(stateInstance);
    if(result != ERROR_NONE)
    {
        PrintResultCode(result);
        ReleaseStateInstance(stateInstance);
        return (int) result;
    }

    ReleaseStateInstance(stateInstance);

    return 0;
}

Result InitObject(void* object, Size objectIndex, void* spaces, Size spacesSize)
{
    Object* currObj = (Object*) object;

    currObj->location = getSpace(rand() % spacesSize, spaces, sizeof(Space));
    currObj->xSpeed = rand() % OBJECT_SPEED_X_MAX;
    currObj->ySpeed = rand() % OBJECT_SPEED_Y_MAX;

    return ERROR_NONE;
}

Result InitSpace(void* space, Size spaceIndex)
{
    Space* currSpace = (Space*) space;

    currSpace->x = spaceIndex % SPACE_X_SIZE;
    currSpace->y = spaceIndex / SPACE_X_SIZE;

    return ERROR_NONE;
}

void SpaceUpdate(void* space,
                    void* destSpace,
                    Size spaceIndex,
                    void* objects,
                    Size objectCount,
                    void* spaces,
                    Size spaceCount)
{
    memoryCopy(space, destSpace, sizeof(Space));
    return;
}

void ObjectUpdate(void* object,
                    void* destObj,
                    Size objectIndex,
                    void* objects,
                    Size objectCount,
                    void* spaces,
                    Size spaceCount)
{
    Object* dest = (Object*) destObj;
    Object* src = (Object*) object;

    int currX = src->location->x + src->xSpeed;
    int currY = src->location->y + src->ySpeed;

    dest->xSpeed = src->xSpeed;
    dest->ySpeed = src->ySpeed;

    dest->location = getSpace(currX + currY * SPACE_X_SIZE, spaces, sizeof(Space));

    return;
}
