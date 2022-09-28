#include "application.h"
#include <QCommandLineParser>

int main(int argc, char* argv[])
{
    QCoreApplication::setApplicationName("Programmers Notepad Next");
    QCoreApplication::setOrganizationName("Programmers Notepad Next");
    QCoreApplication::setApplicationVersion("0.1");

    Application app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument(QObject::tr("file"), QObject::tr("The file to open."));
    parser.process(app);

    auto window = Application::newWindow();
    if (auto positionalArguments = parser.positionalArguments(); !positionalArguments.isEmpty())
        Application::openFile(window, positionalArguments.constFirst());

    return Application::exec();
}
