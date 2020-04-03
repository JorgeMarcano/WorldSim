#include "../Framework/State/State.h"
#include "../Framework/Error/Error.h"
#include "../Framework/Loader/Loader.h"

int main()
{
    State* stateInstance = CreateStateInstance();

    

    ReleaseStateInstance(stateInstance);

    return 0;
}