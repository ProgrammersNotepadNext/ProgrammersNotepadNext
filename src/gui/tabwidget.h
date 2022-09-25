#pragma once

#include "gui/tabbar.h"
#include <QTabWidget>
#include <QUrl>
#include <QMenu>

class glyph_button;
class hexeditor;
class Tab;

class tab_widget : public QTabWidget
{
    Q_OBJECT

public:
    explicit tab_widget(QWidget* parent = nullptr);
    ~tab_widget() override;

    // Manipulators for tabs.
    auto add_tab(Tab* widget, const QString& label) -> int;
    auto add_tab(Tab* widget, const QIcon& icon, const QString& label) -> int;
    auto insert_tab(int index, Tab* widget, const QString& label) -> int;
    auto insert_tab(int index, Tab* widget, const QIcon& icon, const QString& label) -> int;
    auto remove_tab(int index, bool clear_from_memory) -> bool;

    // Changes icon/text of the tab.
    void change_title(int index, const QString& new_title, const QString& tool_tip = QString());
    void change_icon(int index, const QIcon& new_icon);

    // Returns true if there is only one tab visible and it has no contents and is in unmodified state
    // and not bound to file.
    auto has_only_one_empty_editor() const -> bool;

    auto current_editor() const -> hexeditor*;
    auto current_tab() const -> Tab*;

    auto index_of_editor(hexeditor* editor) const -> int;
    auto editor_at(int index) const -> hexeditor*;
    auto tab_at(int index) const -> Tab*;

    auto editors() const -> QList<hexeditor*>;
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
    void makeEditorVisible(hexeditor* editor);

protected:
    void setup_connections();

private slots:
    void onTabRequestedVisibility();
    void showTabContextMenu(const QPoint& point);

private:
    void indentTabText(int index);
    void prepareNewTab(int index);
};

inline TabBar* tab_widget::tab_bar() const
{
    return static_cast<TabBar*>(QTabWidget::tabBar());
}
