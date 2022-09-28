#pragma once

#include "gui/tab.h"
#include "gui/hexeditor.h"
#include <QIcon>

class MainWindow;

class EditorTab : public Tab
{
    Q_OBJECT
public:
    EditorTab(MainWindow* text_app, Editor* editor);
    explicit EditorTab(MainWindow* text_app);

    auto contextMenu() const -> QMenu* override;
    auto primaryEditor() const ->Editor* override;
    auto allEditors() const -> QList<Editor*> override;
    auto countOfEditors() const -> int override;
    auto title() const -> QString override;
    auto toolTip() const -> QString override;

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void updateTitleFromEditor();

private:
    Editor* m_editor{nullptr};
    QString m_title{};
    QString m_toolTip{};
};
