#pragma once
#include <Wt/Dbo/Dbo.h>
#include "../../../comunication/Example.h"

namespace dbo = Wt::Dbo;
class TableData;
typedef dbo::collection< dbo::ptr<TableData> > TablesData;

class TableData  {
public:

    ExampleModule::Enumeration enum_field;
    std::string string_field;
    double double_field;
    bool bool_field;
    std::chrono::system_clock::time_point dateTime_field;
    
    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, string_field, "string_field");
        dbo::field(a, enum_field,  "enum_field");
        dbo::field(a, double_field, "double_field");
        dbo::field(a, bool_field, "bool_field");
        dbo::field(a, dateTime_field, "dateTime_field");
    }


};