#include "include/Session.h"
#include <Wt/Dbo/backend/Sqlite3.h>
#include "include/TableTest.h"
#include <Wt/WDateTime.h>

Session::Session()
{
    setConnection(std::make_unique<Wt::Dbo::backend::Sqlite3>("test.db"));
    try {

        mapClass<TableData>("example_table");
        createTables();

    }catch(Wt::Dbo::Exception& e) {
        std::cout << e.what() << std::endl;
    }
}

Session::~Session()
{
}

void Session::addRecord(ExampleModule::RowData rowData)
{
    Wt::Dbo::Transaction transaction(*this);

    auto tableData = std::make_unique<TableData>(); 
    tableData->string_field = rowData.stringData;
    tableData->enum_field = rowData.enumData;
    tableData->double_field = rowData.doubleData;
    tableData->bool_field = rowData.boolData;

    auto dateTime = Wt::WDateTime().fromString(rowData.dateTimeData, dateTimeFormat);
    tableData->dateTime_field = dateTime.toTimePoint();

    add(std::move(tableData));
    transaction.commit();
}

ExampleModule::AllRowData Session::getTableData()
{
    Wt::Dbo::Transaction transaction(*this);
    ExampleModule::AllRowData allRowData;
    TablesData tablesData = find<TableData>();
    for (auto& row : tablesData) {
        ExampleModule::RowData rowData;
        rowData.id = row.id();
        rowData.stringData = row->string_field;
        rowData.enumData = row->enum_field;
        rowData.doubleData = row->double_field;
        rowData.boolData = row->bool_field;
        auto dateTime = Wt::WDateTime(row->dateTime_field);

        rowData.dateTimeData = dateTime.toString(dateTimeFormat).toUTF8(); 

        allRowData.push_back(rowData);
    }
    return allRowData;
}

void Session::deleteRecord(int id)
{
    Wt::Dbo::Transaction transaction(*this);
    dbo::ptr<TableData> tableTest_row = find<TableData>().where("id = ?").bind(id);
    tableTest_row.remove();

    transaction.commit();
}

void Session::modifyStringColumn(int id, std::string data)
{
    Wt::Dbo::Transaction transaction(*this);
    dbo::ptr<TableData> tableTest_row = find<TableData>().where("id = ?").bind(id);
    tableTest_row.modify()->string_field = data;
    transaction.commit();
}

void Session::modifyEnumColumn(int id, ExampleModule::Enumeration data)
{
    Wt::Dbo::Transaction transaction(*this);
    dbo::ptr<TableData> tableTest_row = find<TableData>().where("id = ?").bind(id);
    tableTest_row.modify()->enum_field = data;
    transaction.commit();
}

void Session::modifyDoubleColumn(int id, double data)
{
    Wt::Dbo::Transaction transaction(*this);
    dbo::ptr<TableData> tableTest_row = find<TableData>().where("id = ?").bind(id);
    tableTest_row.modify()->double_field = data;
    transaction.commit();
}

void Session::modifyBoolColumn(int id, bool data)
{
    Wt::Dbo::Transaction transaction(*this);
    dbo::ptr<TableData> tableTest_row = find<TableData>().where("id = ?").bind(id);
    tableTest_row.modify()->bool_field = data;
    transaction.commit();
}

void Session::modifyDateTimeColumn(int id, std::string newDateTimeData)
{
    Wt::Dbo::Transaction transaction(*this);
    dbo::ptr<TableData> tableTest_row = find<TableData>().where("id = ?").bind(id);
    auto dateTime = Wt::WDateTime().fromString(newDateTimeData, dateTimeFormat);
    tableTest_row.modify()->dateTime_field = dateTime.toTimePoint();
    transaction.commit();
}

