#pragma once

#include "gui/tab.h"
#include "gui/hexeditor.h"
#include <QIcon>

class MainWindow;

class EditorTab : public Tab
{
    Q_OBJECT
public:
    EditorTab(MainWindow* text_app, hexeditor* editor);
    explicit EditorTab(MainWindow* text_app);

    auto contextMenu() const -> QMenu* override;
    auto primaryEditor() const -> hexeditor* override;
    auto allEditors() const -> QList<hexeditor*> override;
    auto countOfEditors() const -> int override;
    auto icon() const -> QIcon override;
    auto title() const -> QString override;
    auto toolTip() const -> QString override;

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void updateIcon(bool read_only);
    void updateTitleFromEditor();

private:
    hexeditor* m_editor{nullptr};
    QIcon m_icon{nullptr};
    QString m_title{};
    QString m_toolTip{};
};
