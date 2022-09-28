#pragma once

#include <QWidget>
#include <QList>
#include <QMenu>

class TabWidget;
class Editor;

class Tab : public QWidget
{
    Q_OBJECT
public:
    explicit Tab(TabWidget* parent);

    // Returns context menu.
    // NOTE: Caller must take ownership of the menu.
    virtual auto contextMenu() const->QMenu* = 0;

    // Returns primary editor.
    virtual auto primaryEditor() const->Editor* = 0;

    // Returns list of all editors, sorted from
    // most significant to less significant.
    virtual auto allEditors() const -> QList<Editor*> = 0;

    // Return count of editors.
    virtual auto countOfEditors() const -> int = 0;

    // Title and icon of a tab.
    virtual auto title() const ->QString = 0;
    virtual auto toolTip() const ->QString = 0;

    // Returns index of this tab in tab widget.
    // NOTE: Returns value < 0 if this tab is not in tab widget.
    auto index() const -> int;

public slots:
    void requestVisibility();

signals:
    //void iconChanged(QIcon icon);
    void titleChanged(QString title, QString tool_tip);
    void visibilityRequested();

private:
    TabWidget* tabwidget_;
};
