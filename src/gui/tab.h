#pragma once

#include <QWidget>
#include <QIcon>
#include <QList>
#include <QMenu>

class tab_widget;
class hexeditor;

class Tab : public QWidget
{
    Q_OBJECT
public:
    explicit Tab(tab_widget* parent);

    // Returns context menu.
    // NOTE: Caller must take ownership of the menu.
    virtual QMenu* contextMenu() const = 0;

    // Returns primary editor.
    virtual hexeditor* primaryEditor() const = 0;

    // Returns list of all editors, sorted from
    // most significant to less significant.
    virtual QList<hexeditor*> allEditors() const = 0;

    // Return count of editors.
    virtual int countOfEditors() const = 0;

    // Title and icon of a tab.
    virtual QString title() const = 0;
    virtual QIcon icon() const = 0;
    virtual QString toolTip() const = 0;

    // Returns index of this tab in tab widget.
    // NOTE: Returns value < 0 if this tab is not in tab widget.
    int index() const;

public slots:
    void requestVisibility();

signals:
    void iconChanged(QIcon icon);
    void titleChanged(QString title, QString tool_tip);
    void visibilityRequested();

private:
    tab_widget* tabwidget_;
};
