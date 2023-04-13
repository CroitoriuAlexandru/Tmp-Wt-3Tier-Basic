#include "include/PageTwo.h"
#include <Wt/WText.h>

PageTwo::PageTwo()
    : WContainerWidget()
{
    addStyleClass("page-two");
    addWidget(std::make_unique<Wt::WText>("Page Two"));
}