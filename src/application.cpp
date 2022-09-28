#include "application.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv)
{
}

Application::~Application()
{
}

void Application::openFile(MainWindow* window, const QString& file)
{
    window->openFile(file);
}

auto Application::newWindow() -> MainWindow*
{
    auto window = new MainWindow();
    window->show();
    window->raise();
    return window;
}
