#pragma once

#include <qhexedit/qhexedit.h>
#include <filesystem>

// glue object to handle file handler and the hexeditor
class hexeditor : public QHexEdit
{
    Q_OBJECT
public:
    // create new empty
    hexeditor(QWidget* parent = nullptr);
    // load file
    hexeditor(QString filename, QWidget* parent = nullptr);

    bool save();
    bool save_as();

    auto filepath() const -> QString;
    auto filename() const -> QString;

private:
    bool savefile(const QString& fileName);

    QString filename_{};
    QFile file_{};
    bool is_untitled_{true};
};