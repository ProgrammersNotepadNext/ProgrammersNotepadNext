#pragma once

#include "gui/tabbar.h"
#include <QTabWidget>
#include <QUrl>
#include <QMenu>

class Editor;
class Tab;

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget* parent = nullptr);
    ~TabWidget() override;

    // Manipulators for tabs.
    auto addTab(Tab* widget, const QString& label) -> int;
    auto insertTab(int index, Tab* widget, const QString& label) -> int;
    auto removeTab(int index, bool clear_from_memory) -> bool;

    // Changes icon/text of the tab.
    void change_title(int index, const QString& new_title, const QString& tool_tip = QString());

    // Returns true if there is only one tab visible and it has no contents and is in unmodified state
    // and not bound to file.
    auto has_only_one_empty_editor() const -> bool;

    auto current_editor() const ->Editor*;
    auto current_tab() const -> Tab*;

    auto index_of_editor(Editor* editor) const -> int;
    auto editor_at(int index) const ->Editor*;
    auto tab_at(int index) const -> Tab*;

    auto editors() const -> QList<Editor*>;
    auto tabs() const -> QList<Tab*>;

    auto tab_with_file(const QString& file_path) const -> Tab*;

    // Returns tab bar.
    auto tab_bar() const -> TabBar*;

public slots:
    bool closeTab(int index);
    void closeAllTabsExceptCurrent();
    void closeAllTabs();
    void closeCurrentTab();

    void gotoNextTab();
    void gotoPreviousTab();

    void makeTabVisible(Tab* tab);
    void makeEditorVisible(Editor* editor);

protected:
    void setup_connections();

private slots:
    void onTabRequestedVisibility();
    void showTabContextMenu(const QPoint& point);

private:
    void indentTabText(int index);
    void prepareNewTab(int index);
};
