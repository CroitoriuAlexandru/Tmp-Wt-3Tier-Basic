#include "include/ExampleInterfaceI.h"
#include <memory>

using namespace std;
using namespace ExampleModule;
 

int
main(int argc, char* argv[])
{
    try
    {
        Ice::CommunicatorHolder ich(argc, argv);
        auto adapter = ich->createObjectAdapterWithEndpoints("ExampleAdapter", "default -p 10000");
        auto servant = std::make_shared<ExampleInterfaceI>();
        adapter->add(servant, Ice::stringToIdentity("Example"));
        adapter->activate();
        ich->waitForShutdown();
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}