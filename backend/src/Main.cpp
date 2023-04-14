#include "include/ExampleInterfaceI.h"
#include <Ice/Ice.h>

#include <Wt/Dbo/FixedSqlConnectionPool.h>
#include <Wt/Dbo/backend/Sqlite3.h>

#include <fstream>
#include <memory>

using namespace std;
using namespace ExampleModule;
 

int
main(int argc, char* argv[])
{

    ifstream connFile("comunication.txt");
    std::ifstream dboConnFile("dboConnString.txt");

    if(!dboConnFile.is_open())
    {
        std::cerr << "\n\n Could not open dboConnString.txt \n\n";
    }
    std::string dboConnString;
    getline(dboConnFile, dboConnString);
    std::cout << "\n\nDbo connection string <" << dboConnString << ">\n";

    if(!connFile.is_open())
    {
        cerr << "Could not open comunication.txt" << endl;
        return 1;
    }

    string connAdapter;
    string connString;
    string proxyString;
    getline(connFile, connAdapter);
    getline(connFile, connString);
    getline(connFile, proxyString);


    std::cout << "\n\nIce connection adapter <" << connAdapter << ">\n";
    std::cout << "Ice connection string <" << connString << ">\n";
    std::cout << "Ice proxy string <" << proxyString << ">\n\n";

    auto myDbo = std::make_unique<Wt::Dbo::backend::Sqlite3>(dboConnString);
    myDbo->setProperty("show-queries", "true");
    auto dboPool = std::make_unique<Wt::Dbo::FixedSqlConnectionPool>(std::move(myDbo), 1);

    try
    {
        Ice::CommunicatorHolder ich(argc, argv);
        auto adapter = ich->createObjectAdapterWithEndpoints(connAdapter, connString);
        auto servant = std::make_shared<ExampleInterfaceI>(std::move(dboPool->getConnection()));
        adapter->add(servant, Ice::stringToIdentity(proxyString));
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