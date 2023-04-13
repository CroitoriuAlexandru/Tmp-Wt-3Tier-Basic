#include "include/PageOne.h"

#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WBreak.h>

#include <iostream>
#include <iomanip>

#include <Ice/Ice.h>
#include <stdexcept>
 
PageOne::PageOne()
    : WContainerWidget()
{
    addStyleClass("my-3 border p-3 container-lg");

    formTemplate_ =  addWidget(std::move(create_formWidget()));
    addWidget(std::make_unique<Wt::WContainerWidget>())->setStyleClass("border my-3");
    addWidget(std::make_unique<Wt::WText>("Table representation from dbo "))->setStyleClass("fs-5 d-block text-decoration-underline text-center");
    addWidget(std::move(create_tableWidget()));
    displayData();
}

std::unique_ptr<Wt::WTemplate> PageOne::create_formWidget()
{
    auto formTemplate = std::make_unique<Wt::WTemplate>(Wt::WString::tr("form"));
    formTemplate->setStyleClass("d-flex flex-column align-items-center");
    formTemplate->addFunction("id", &Wt::WTemplate::Functions::id);


    // input for text to be recorder in dbo
    stringInput_ = formTemplate->bindWidget("string-input", std::make_unique<Wt::WLineEdit>());
    stringInput_->setPlaceholderText("Enter text here");
    
    // input for enumeration to be recorder in dbo
    selectInput_ = formTemplate->bindWidget("selection-input", std::move(createComboBox()));

    // input for double to be recorder in dbo
    doubleInput_ = formTemplate->bindWidget("double-input", std::make_unique<Wt::WDoubleSpinBox>());
    doubleInput_->setRange(0, 100);
    doubleInput_->setSingleStep(2.5);
    doubleInput_->setDecimals(2);
    doubleInput_->setValue(0);


    // input for switch to be recorder in dbo
    boolInput_ = formTemplate->bindWidget("bool-input", std::make_unique<Wt::WCheckBox>());

    // input for date to be recorder in dbo
    dateInput_ = formTemplate->bindWidget("date-input", std::make_unique<Wt::WDateEdit>());
    dateInput_->setFormat(dateFormat_);
    dateInput_->setDate(Wt::WDate::currentServerDate());
    dateInput_->setReadOnly(true);
    timeInput_ = formTemplate->bindWidget("time-input", std::make_unique<Wt::WTimeEdit>());
    timeInput_->setFormat(timeFormat_);
    timeInput_->setTime(Wt::WTime(12, 0, 0, 0));
    timeInput_->setReadOnly(true);

    formTemplate->bindEmpty("submit-info");

    auto submitBtn = formTemplate->bindWidget("submit-btn", std::make_unique<Wt::WPushButton>("Submit"));
    submitBtn->clicked().connect(this, &PageOne::submitBtnClicked);

    return formTemplate;
}

std::unique_ptr<Wt::WContainerWidget> PageOne::create_tableWidget()
{
    auto viewWidget = std::make_unique<Wt::WContainerWidget>();
    viewWidget->setStyleClass("w-100 view-widget");

    table_ = viewWidget->addWidget(std::make_unique<Wt::WTable>());
    table_->setStyleClass("table table-striped table-bordered table-hover");
    table_->setHeaderCount(1);
    table_->setWidth(Wt::WLength("100%"));
    table_->columnAt(0)->setWidth(Wt::WLength("8%"));
    auto refreshBtn = table_->elementAt(0, 0)->addWidget(std::make_unique<Wt::WPushButton>("<i class=\"bi bi-arrow-clockwise\"></i>", Wt::TextFormat::XHTML));
    table_->elementAt(0, 1)->addWidget(std::make_unique<Wt::WText>("String"));
    table_->elementAt(0, 2)->addWidget(std::make_unique<Wt::WText>("Selection"));
    table_->elementAt(0, 3)->addWidget(std::make_unique<Wt::WText>("Double"));
    table_->elementAt(0, 4)->addWidget(std::make_unique<Wt::WText>("Bool"));
    table_->elementAt(0, 5)->addWidget(std::make_unique<Wt::WText>("DateTime"));
    auto dateTimeColumn =  table_->columnAt(5); 
    dateTimeColumn->setWidth(Wt::WLength("250px"));
    refreshBtn->clicked().connect(this, [=](){ displayData(); });
    return viewWidget;
}

void PageOne::displayData()
{
    // clear table data
    for(int i = table_->rowCount() - 1; i > 0; --i)
        table_->removeRow(i);

    // get data from dbo
    ExampleModule::AllRowData data = getAllRowsData();
    
    // display data in table
    for (int i = 0; i < data.size(); ++i)
    {
        auto tableRow = table_->insertRow(i + 1);
        // id column del btn

        auto delBtnXml = "<i class=\"bi bi-trash\"></i> " + std::to_string(data[i].id) + " ";
        auto delBtn = table_->elementAt(i + 1, 0)->addWidget(std::make_unique<Wt::WPushButton>(delBtnXml , Wt::TextFormat::XHTML));

        // string field column
        auto stringInput_field = table_->elementAt(i + 1, 1)->addWidget(std::make_unique<Wt::WLineEdit>(data[i].stringData));
        stringInput_field->textInput().connect(this, [=](){
            stringInputChanged(data[i].id, stringInput_field->text().toUTF8());
            std::cout << "\n\n record id = " << data[i].id << "\n";
            std::cout <<  "string new value = " << stringInput_field->text().toUTF8() << "\n\n";
        });

        // enumeration column
        auto selectInput_field = table_->elementAt(i + 1, 2)->addWidget(std::move(createComboBox()));
        if(data[i].enumData == ExampleModule::Enumeration::value1)
            selectInput_field->setCurrentIndex(0);
        else if(data[i].enumData == ExampleModule::Enumeration::value2)
            selectInput_field->setCurrentIndex(1);
        else 
            selectInput_field->setCurrentIndex(2);

        selectInput_field->changed().connect(this, [=](){

            ExampleModule::Enumeration enumData;
            if(selectInput_field->currentIndex() == 0)
                enumData = ExampleModule::Enumeration::value1;
            else if(selectInput_field->currentIndex() == 1)
                enumData = ExampleModule::Enumeration::value2;
            else
                enumData = ExampleModule::Enumeration::value3;
    
            selectInputChanged(data[i].id, enumData);
            std::cout << "\n\n record id = " << data[i].id << "\n";
            std::cout <<  "enum new value index = " << selectInput_field->currentIndex() << "\n\n";
        });

        // double field column
        auto doubleInput_field = table_->elementAt(i + 1, 3)->addWidget(std::make_unique<Wt::WDoubleSpinBox>()); 
        doubleInput_field->setRange(0, 100);
        doubleInput_field->setSingleStep(2.5);
        doubleInput_field->setDecimals(2);
        doubleInput_field->setValue(data[i].doubleData);

        doubleInput_field->changed().connect(this, [=](){
            doubleInputChanged(data[i].id, doubleInput_field->value());
            std::cout << "\n\n record id = " << data[i].id << "\n";
            std::cout <<  "double new value = " << doubleInput_field->value() << "\n\n";
        });

        // bool field column
        auto boolInput_field = table_->elementAt(i + 1, 4)->addWidget(std::make_unique<Wt::WCheckBox>());
        boolInput_field->setChecked(data[i].boolData);
        auto boolText = table_->elementAt(i + 1, 4)->addWidget(std::make_unique<Wt::WText>("On"));
        if(data[i].boolData)
            boolText->setText("On");
        else
            boolText->setText("Off");

        boolInput_field->changed().connect(this, [=](){
            boolInputChanged(data[i].id, boolInput_field->isChecked());
            if(boolInput_field->isChecked()){
                boolText->setText("On");
                std::cout << "\n\n record id = " << data[i].id << "\n";
                std::cout <<  "bool new value = true \n\n";
            }else {
                boolText->setText("Off");
                std::cout << "\n\n record id = " << data[i].id << "\n"; 
                std::cout <<  "bool new value = false \n\n";
            }
        });

        // date field column
        auto dateTime = Wt::WDateTime().fromString(data[i].dateTimeData, dateTimeFormat_);
        auto dateInput_field = table_->elementAt(i + 1, 5)->addWidget(std::make_unique<Wt::WDateEdit>());
        auto dateTimeCell = table_->elementAt(i + 1, 5);
        dateTimeCell->setStyleClass("d-flex");
        dateInput_field->setFormat("dd/MM/yyyy");
        dateInput_field->setDate(dateTime.date());
        std::cout << "\n\n record id = " << dateTime.toString(dateTimeFormat_) << "\n\n";
        dateInput_field->changed().connect(this, [=](){
            auto newDate = dateInput_field->date();
            std::cout << "\n record id = " << data[i].id << "\n";
            std::cout <<  "date new value = " << newDate.toString(dateFormat_) << "\n\n";
            auto dateTime = Wt::WDateTime(newDate, timeInput_->time());
            dateTimeInputChanged(data[i].id, dateTime);
        });

        auto timeInput_Field = table_->elementAt(i + 1, 5)->addWidget(std::make_unique<Wt::WTimeEdit>());
        timeInput_Field->setFormat("hh:mm");
        timeInput_Field->setTime(dateTime.time());
        timeInput_Field->setWidth(Wt::WLength("90px"));
        timeInput_Field->changed().connect(this, [=](){
            auto newTime = timeInput_Field->time();
            std::cout << "\n record id = " << data[i].id << "\n";
            std::cout <<  "time new value = " << newTime.toString(timeFormat_) << "\n\n";

            auto dateTime = Wt::WDateTime(dateInput_field->date(), newTime);
            dateTimeInputChanged(data[i].id, dateTime);
        });

        // delete record from dbo and row froom table
        delBtn->clicked().connect(this, [=](){
            deleteRecord(data[i].id);
            table_->removeRow(tableRow->rowNum());
            std::cout << "\n\n record id = " << data[i].id << " DELETED \n\n";
        });
    }
}

void PageOne::submitBtnClicked()
{
    ExampleModule::RowData data;
    // get string date
    data.stringData = stringInput_->text().toUTF8();

    // get enumeration data
    if(selectInput_->currentIndex() == 0)
        data.enumData = ExampleModule::Enumeration::value1;
    else if(selectInput_->currentIndex() == 1)
        data.enumData = ExampleModule::Enumeration::value2;
    else if(selectInput_->currentIndex() == 2)
        data.enumData = ExampleModule::Enumeration::value3;
    else 
        std::cout << "\n\n\n\n\n\n error at selectInput_, selected out of range \n\n\n\n\n\n\n\n";

    // get double data
    if(doubleInput_->validate() != Wt::ValidationState::Valid){
        std::cout << "doubleInput_ validation failed\n";
        formTemplate_->bindWidget("submit-info", std::make_unique<Wt::WText>("only numbers between 0 and 100 are allowed, please try again"));
        doubleInput_->setValue(0);
        doubleInput_->setFocus();
        return;
    }
    data.doubleData = doubleInput_->value();

    // get switch data
    data.boolData = boolInput_->isChecked();

    // get date data
    auto dateTime = Wt::WDateTime(dateInput_->date(), timeInput_->time());
    data.dateTimeData = dateTime.toString(dateTimeFormat_).toUTF8();

    // add record to dbo
    try {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->addRowData(data);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // clear form submit info
    formTemplate_->bindEmpty("submit-info");
    displayData();
}

std::unique_ptr<Wt::WComboBox> PageOne::createComboBox()
{
    auto comboBox = std::make_unique<Wt::WComboBox>();
    comboBox->addItem("Value 1");
    comboBox->addItem("Value 2");
    comboBox->addItem("Value 3");
    return comboBox;
}

ExampleModule::AllRowData PageOne::getAllRowsData()
{
    ExampleModule::AllRowData data;
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        data = exampleInterface->getRowsData();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
    return data;
}

void PageOne::stringInputChanged(int rowId, std::string stringData)
{
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->changeStringData(rowId, stringData);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
}

void PageOne::selectInputChanged(int rowId, ExampleModule::Enumeration enumValue)
{
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->changeEnumData(rowId, enumValue);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
}

void PageOne::doubleInputChanged(int rowId, double doubleValue)
{
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->changeDoubleData(rowId, doubleValue);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
}

void PageOne::boolInputChanged(int rowId, bool boolValue)
{
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->changeBoolData(rowId, boolValue);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
}

void PageOne::dateTimeInputChanged(int rowId, Wt::WDateTime dateTime)
{
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->changeDateTimeData(rowId, dateTime.toString(dateTimeFormat_).toUTF8());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
}

void PageOne::deleteRecord(int rowId)
{
    try
    {
        Ice::CommunicatorHolder ich = Ice::initialize();
        auto base = ich->stringToProxy("Example:default -p 10000");
        auto exampleInterface = Ice::checkedCast<ExampleModule::ExampleInterfacePrx>(base);
        if(!exampleInterface)
        {
            throw std::runtime_error("Invalid proxy");
        }

        exampleInterface->deleteRowData(rowId);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n\n";
    }
}

