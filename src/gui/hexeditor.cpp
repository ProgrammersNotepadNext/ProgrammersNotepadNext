#include "gui/hexeditor.h"
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>

hexeditor::hexeditor(QString filename, QWidget* parent /*= nullptr*/)
    : QHexEdit(parent)
    , filename_(filename)
    , file_(filename_)
    , is_untitled_(false)
{
    if (!setData(file_))
    {
        throw std::runtime_error("failed to set data to hex editor");
    }
}

hexeditor::hexeditor(QWidget* parent /*= nullptr*/)
    : QHexEdit(parent)
{
}

bool hexeditor::save()
{
    if (is_untitled_)
        return save_as();

    return savefile(filename_);
}

bool hexeditor::save_as()
{
    const auto fileName = QFileDialog::getSaveFileName(this, tr("Save As"), filename_);
    if (fileName.isEmpty())
        return false;

    return savefile(fileName);
}

auto hexeditor::filepath() const -> QString
{
    return filename_;
}

QString hexeditor::filename() const
{
    const auto file_name = std::filesystem::path(filename_.toStdString()).filename();
    return QString::fromStdString(file_name.string());
}

bool hexeditor::savefile(const QString& fileName)
{
    QString tmpFileName = fileName + ".~tmp";

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QFile file(tmpFileName);
    bool ok = write(file);
    if (QFile::exists(fileName))
        ok = QFile::remove(fileName);

    if (ok)
    {
        file.setFileName(tmpFileName);
        ok = file.copy(fileName);
        if (ok)
            ok = QFile::remove(tmpFileName);
    }
    QApplication::restoreOverrideCursor();

    if (!ok)
    {
        QMessageBox::warning(this, tr("HexEdit"), tr("Cannot write file %1.").arg(fileName));
        return false;
    }

    // emit FilenameChanged(fileName);

    // setCurrentFile(fileName);
    // statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}
