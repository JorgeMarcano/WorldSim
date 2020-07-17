#include "../Framework/State/State.h"
#include "../Framework/Error/Error.h"
#include "../Framework/Loader/Loader.h"
#include "../Framework/Mainloop/Mainloop.h"
#include "../Framework/Logger/Logger.h"

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

char* Printer(void* object, Size objectSize, void* spaces, Size spacesSize);

int main()
{
    srand(time(0));

    //Instantiate State Object
    State* stateInstance = CreateStateInstance();

    Logger* loggerInstance = StartLog("log.log", Printer);

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
    result = Mainloop(stateInstance, loggerInstance);
    if(result != ERROR_NONE)
    {
        PrintResultCode(result);
        ReleaseStateInstance(stateInstance);
        return (int) result;
    }

    ReleaseStateInstance(stateInstance);
    EndLog(loggerInstance);

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

    int currX = (src->location->x + src->xSpeed) % SPACE_X_SIZE;
    int currY = (src->location->y + src->ySpeed) % SPACE_Y_SIZE;

    dest->xSpeed = src->xSpeed;
    dest->ySpeed = src->ySpeed;

    dest->location = getSpace(currX + currY * SPACE_X_SIZE, spaces, sizeof(Space));

    return;
}

char* Printer(void* object, Size objectSize, void* spaces, Size spacesSize)
{
    //Must leave enough space for every "space", for every end of line, one at the end for an extra end of line, and the null
    Size totalSize = spacesSize * sizeof(char) + SPACE_Y_SIZE + 2;
    char* text = malloc(totalSize);
    text[totalSize - 1] = '\0';
    text[totalSize - 2] = '\n';

    for (int i = 0; i < totalSize - 3; i++)
        text[i] = 'O';

    for (int i = 0; i < SPACE_Y_SIZE; i++)
        text[(SPACE_X_SIZE + 1) * i + SPACE_X_SIZE] = '\n';

    Object obj;
    for (int i = 0; i < objectSize; i++)
    {
        obj = ((Object*) object)[i];
        text[obj.location->y * (SPACE_X_SIZE + 1) + obj.location->x] = 'X';
    }

    return text;
}
