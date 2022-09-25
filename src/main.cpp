#include <QApplication>
#include <QFontDatabase>
#include <QIcon>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(hexactly);

    QApplication app(argc, argv);
    app.setApplicationName("Hexactly");
    app.setOrganizationName("Hexactly");
    app.setWindowIcon(QIcon(":images/hexactly.ico"));

    QFontDatabase::addApplicationFont(":/images/codicon.ttf");

    auto* main_window = new MainWindow;
    main_window->show();

    return app.exec();
}
