#include "include/App.h"

#include "include/PageOne.h"
#include "include/PageTwo.h"

#include <Wt/WApplication.h>

App::App()
	: WContainerWidget()
{
	addStyleClass("application");
	createNavigation();
}

void App::createNavigation()
{
	navigation_ = addWidget(std::make_unique<Wt::WNavigationBar>());
	navigation_->setObjectName("navigation");

	// navigation->setResponsive(true);
	navigation_->addStyleClass("navbar navbar-dark bg-dark navbar-expand-sm");
	navigation_->setTitle("Navigation", Wt::WLink(Wt::LinkType::InternalPath, "/PageOne"));

	contentsStack_ = addWidget(std::make_unique<Wt::WStackedWidget>());
	contentsStack_->setTransitionAnimation(Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::EaseInOut), true);
	contentsStack_->addStyleClass("contents");

	auto mainMenu_ = navigation_->addMenu(std::make_unique<Wt::WMenu>(contentsStack_));
	mainMenu_->setInternalPathEnabled();

	// create pages content
	auto pageOne = std::make_unique<PageOne>();
	auto pageTwo = std::make_unique<PageTwo>();

	// create menu items 
	auto menuItemOne = std::make_unique<Wt::WMenuItem>("Page One", std::move(pageOne));
	auto menuItemTwo = std::make_unique<Wt::WMenuItem>("Page Two", std::move(pageTwo));

	menuItemOne->setPathComponent("page_one");
	menuItemTwo->setPathComponent("page_two");

	// add pages to stack
	mainMenu_->addItem(std::move(menuItemOne));
	mainMenu_->addItem(std::move(menuItemTwo));

	// default starting page
	Wt::WApplication::instance()->setInternalPath("/page_one", true);

}
