#pragma once
#include <Wt/Dbo/Session.h>
#include "../../../comunication/Example.h"
#include <chrono>

class Session : public Wt::Dbo::Session 
{
public:
    Session();
    ~Session();

    void addRecord(ExampleModule::RowData exampleTable_Data);
    void deleteRecord(int id);
    std::vector<ExampleModule::RowData> getTableData();
    
    void modifyStringColumn(int id, std::string data);
    void modifyEnumColumn(int id, ExampleModule::Enumeration data);
    void modifyDoubleColumn(int id, double data);
    void modifyBoolColumn(int id, bool data);
    void modifyDateTimeColumn(int id, std::string newDateTimeData);

private:
    std::string dateTimeFormat = "dd/MM/yyyy HH:mm";
};
