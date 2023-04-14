#include "include/App.h"
#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <Wt/Dbo/Exception.h>
#include "include/Theme.h"

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment &env)
{
	auto app = std::make_unique<Wt::WApplication>(env);
	app->setTitle("Simple Application Template");
	app->setTheme(std::make_shared<Theme>());

	// add mesage resource bundle from templates
	app->messageResourceBundle().use(app->appRoot() + "resources/templates/General");

	// add custom javascript files
	app->require("resources/Js/Utility.js");

	app->instance()->setInternalPath("/");

	// add application to root
	app->root()->addWidget(std::make_unique<App>());
	return app;
}

int main(int argc, char **argv)
{
	try
	{
		// Server setup
		Wt::WServer server{argc, argv, WTHTTP_CONFIGURATION};

		server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

		server.run();
	}
	catch (Wt::WServer::Exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (Wt::Dbo::Exception &e)
	{
		std::cerr << "Dbo exception: " << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}