#pragma once

#include "mainwindow.h"
#include <QApplication>

class Application : public QApplication
{
public:
    Q_OBJECT

public:
    explicit Application(int& argc, char** argv);
    ~Application() override;

    static void openFile(MainWindow* window, const QString& file);
    static auto newWindow() ->MainWindow*;
};