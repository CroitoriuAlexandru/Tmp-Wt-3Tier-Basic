#include "include/ExampleInterfaceI.h"
#include <Wt/WDateTime.h>

ExampleInterfaceI::ExampleInterfaceI()
: session_()
{
}

void ExampleInterfaceI::addRowData(RowData data, const Ice::Current&)
{
    session_.addRecord(data);
    std::cout << "\n\n datetime data = " << data.dateTimeData << std::endl;
}

AllRowData ExampleInterfaceI::getRowsData(const Ice::Current&)
{
    return session_.getTableData();
}

void ExampleInterfaceI::changeStringData(int id, std::string newStringData, const Ice::Current&)
{
    session_.modifyStringColumn(id, newStringData);
}

void ExampleInterfaceI::changeEnumData(int id, Enumeration newEnumData, const Ice::Current&)
{
    session_.modifyEnumColumn(id, newEnumData);
}

void ExampleInterfaceI::changeDoubleData(int id, double newDoubleData, const Ice::Current&)
{
    session_.modifyDoubleColumn(id, newDoubleData);
}

void ExampleInterfaceI::changeBoolData(int id, bool newBoolData, const Ice::Current&)
{
    session_.modifyBoolColumn(id, newBoolData);
}

void ExampleInterfaceI::changeDateTimeData(int id, std::string newDateTimeData, const Ice::Current&)
{
    session_.modifyDateTimeColumn(id, newDateTimeData);
}

void ExampleInterfaceI::deleteRowData(int id, const Ice::Current&)
{
    session_.deleteRecord(id);
}

