#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WMenu.h>

class App : public Wt::WContainerWidget
{
public:
    App();
private:
    Wt::WNavigationBar* navigation_;
    Wt::WStackedWidget* contentsStack_;
    Wt::WMenu* mainMenu_;

    void createNavigation();


};