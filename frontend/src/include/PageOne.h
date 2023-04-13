#pragma once
#include "../../../comunication/Example.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>

#include <Wt/WLineEdit.h>
#include <Wt/WComboBox.h>
#include <Wt/WDoubleSpinBox.h>
#include <Wt/WCheckBox.h>

#include <Wt/WDateEdit.h>
#include <Wt/WTimeEdit.h>

class PageOne : public Wt::WContainerWidget
{
public:

    PageOne();

private:

    Wt::WTemplate* formTemplate_;

    std::unique_ptr<Wt::WTemplate> create_formWidget();
    std::unique_ptr<Wt::WContainerWidget> create_tableWidget();
    std::unique_ptr<Wt::WComboBox> createComboBox();

    Wt::WLineEdit* stringInput_;
    Wt::WComboBox* selectInput_;
    Wt::WDoubleSpinBox* doubleInput_;
    Wt::WCheckBox* boolInput_;
    // date has two inputs because in the dbo it is stored as a timepoint
    Wt::WDateEdit* dateInput_;
    Wt::WTimeEdit* timeInput_;
    
    std::string dateFormat_ = "dd/MM/yyyy";
    std::string timeFormat_ = "HH:mm";
    std::string dateTimeFormat_ = Wt::WString(dateFormat_ + " " + timeFormat_).toUTF8();

    Wt::WTable* table_;

    void submitBtnClicked();
    void displayData();

    ExampleModule::AllRowData getAllRowsData();
    void deleteRecord(int rowId);

    void stringInputChanged(int rowId, std::string stringData);
    void selectInputChanged(int rowId, ExampleModule::Enumeration enumValue);
    void doubleInputChanged(int rowId, double doubleData);
    void boolInputChanged(int rowId, bool boolData);
    void dateTimeInputChanged(int rowId, Wt::WDateTime dateTimeData);

};
