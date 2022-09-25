#pragma once

#include <qhexedit/qhexedit.h>
#include <QDialog>
#include <QtCore>

namespace Ui
{
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(QHexEdit* hexEdit, QWidget* parent = nullptr);
    ~SearchDialog();
    qint64 findNext();
    Ui::SearchDialog* ui;

private slots:
    void on_pbFind_clicked();
    void on_pbReplace_clicked();
    void on_pbReplaceAll_clicked();

private:
    QByteArray getContent(int comboIndex, const QString& input);
    qint64 replaceOccurrence(qint64 idx, const QByteArray& replaceBa);

    QHexEdit* hex_editor_;
    QByteArray find_buffer_array_;
};
