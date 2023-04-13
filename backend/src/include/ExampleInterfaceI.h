#pragma once
#include "../../../comunication/Example.h"
#include "Session.h"
#include <Ice/Ice.h>

using namespace ExampleModule;

class ExampleInterfaceI : public ExampleInterface
{
public:
    ExampleInterfaceI();

    virtual void addRowData(RowData data, const Ice::Current&) override;
    virtual AllRowData getRowsData(const Ice::Current&) override;
    virtual void changeStringData(int id, std::string newStringData, const Ice::Current&) override;
    virtual void changeEnumData(int id, Enumeration newEnumData, const Ice::Current&) override;
    virtual void changeDoubleData(int id, double newDoubleData, const Ice::Current&) override;
    virtual void changeBoolData(int id, bool newBoolData, const Ice::Current&) override;
    virtual void changeDateTimeData(int id, std::string newDateTimeData, const Ice::Current&) override;
    virtual void deleteRowData(int id, const Ice::Current&) override;

private:
    Session session_;
};
 