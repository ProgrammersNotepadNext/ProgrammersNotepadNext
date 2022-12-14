#include "searchdialog.h"
#include "ui_searchdialog.h"

#include <QMessageBox>

SearchDialog::SearchDialog(QHexEdit* hexEdit, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    hex_editor_ = hexEdit;
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

qint64 SearchDialog::findNext()
{
    const auto from = hex_editor_->cursorPosition() / 2;
    find_buffer_array_ = getContent(ui->cbFindFormat->currentIndex(), ui->cbFind->currentText());
    qint64 idx = -1;

    if (find_buffer_array_.length() > 0)
    {
        if (ui->cbBackwards->isChecked())
            idx = hex_editor_->lastIndexOf(find_buffer_array_, from);
        else
            idx = hex_editor_->indexOf(find_buffer_array_, from);
    }
    return idx;
}

void SearchDialog::on_pbFind_clicked()
{
    findNext();
}

void SearchDialog::on_pbReplace_clicked()
{
    auto idx = findNext();
    if (idx >= 0)
    {
        const auto replaceBa = getContent(ui->cbReplaceFormat->currentIndex(), ui->cbReplace->currentText());
        replaceOccurrence(idx, replaceBa);
    }
}

void SearchDialog::on_pbReplaceAll_clicked()
{
    qint64 replaceCounter = 0;
    qint64 idx = 0;
    qint64 goOn = QMessageBox::Yes;

    while ((idx >= 0) && (goOn == QMessageBox::Yes))
    {
        idx = findNext();
        if (idx >= 0)
        {
            QByteArray replaceBa = getContent(ui->cbReplaceFormat->currentIndex(), ui->cbReplace->currentText());
            auto result = replaceOccurrence(idx, replaceBa);

            if (result == QMessageBox::Yes)
                replaceCounter += 1;

            if (result == QMessageBox::Cancel)
                goOn = result;
        }
    }

    if (replaceCounter > 0)
        QMessageBox::information(this, tr("QHexEdit"), QString(tr("%1 occurrences replaced.")).arg(replaceCounter));
}

QByteArray SearchDialog::getContent(int comboIndex, const QString& input)
{
    QByteArray findBa;
    switch (comboIndex)
    {
        case 0: // hex
            findBa = QByteArray::fromHex(input.toLatin1());
            break;
        case 1: // text
            findBa = input.toUtf8();
            break;
    }
    return findBa;
}

qint64 SearchDialog::replaceOccurrence(qint64 idx, const QByteArray& replaceBa)
{
    int result = QMessageBox::Yes;
    if (replaceBa.length() >= 0)
    {
        if (ui->cbPrompt->isChecked())
        {
            result = QMessageBox::question(this, tr("QHexEdit"), tr("Replace occurrence?"),
                                           QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            if (result == QMessageBox::Yes)
            {
                hex_editor_->replace(idx, replaceBa.length(), replaceBa);
                hex_editor_->update();
            }
        }
        else
        {
            hex_editor_->replace(idx, find_buffer_array_.length(), replaceBa);
        }
    }
    return result;
}
