#include "gui/hexeditor.h"
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include <filesystem>

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

void hexeditor::Save()
{
    if (is_untitled_)
    {
        SaveAs();
        return;
    }

    savefile(filename_);
}

void hexeditor::SaveAs()
{
    const auto fileName = QFileDialog::getSaveFileName(this, tr("Save As"), filename_);
    if (fileName.isEmpty())
        return;

    savefile(fileName);
}

auto hexeditor::Filepath() const -> QString
{
    return filename_;
}

QString hexeditor::Filename() const
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
