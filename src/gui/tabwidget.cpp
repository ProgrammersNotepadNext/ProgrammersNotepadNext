#include "gui/tabwidget.h"
#include "gui/tab.h"
#include "gui/tabbar.h"
#include "gui/texteditor.h"
#include <QToolButton>

tab_widget::tab_widget(QWidget* parent)
    : QTabWidget(parent)
{
    setTabBar(new TabBar(this));
    setUsesScrollButtons(true);
    setMovable(true);
    setIconSize(QSize(14, 14));
    setDocumentMode(true);

    setup_connections();
}

tab_widget::~tab_widget() = default;

void tab_widget::setup_connections()
{
    connect(tab_bar(), &TabBar::tabCloseRequested, this, &tab_widget::closeTab);
    connect(tab_bar(), &TabBar::customContextMenuRequested, this, &tab_widget::showTabContextMenu);
}

bool tab_widget::closeTab(int index)
{
    return remove_tab(index, true);
}

void tab_widget::closeAllTabsExceptCurrent()
{
    // Close tabs after active tab.
    int index_of_active = currentIndex();

    for (int i = count() - 1; i >= 0; i--)
    {
        if (i != index_of_active)
        {
            if (i < index_of_active)
            {
                index_of_active--;
            }

            closeTab(i);
        }
    }
}

void tab_widget::closeAllTabs()
{
    for (int i = count() - 1; i >= 0; i--)
    {
        closeTab(i);
    }
}

void tab_widget::closeCurrentTab()
{
    if (currentIndex() >= 0)
    {
        closeTab(currentIndex());
    }
}

void tab_widget::gotoNextTab()
{
    if (currentIndex() == count() - 1)
    {
        setCurrentIndex(0);
    }
    else
    {
        setCurrentIndex(currentIndex() + 1);
    }
}

void tab_widget::gotoPreviousTab()
{
    if (currentIndex() == 0)
    {
        setCurrentIndex(count() - 1);
    }
    else
    {
        setCurrentIndex(currentIndex() - 1);
    }
}

void tab_widget::indentTabText(int index)
{
#if defined(Q_OS_MACOS)
    if (!tabIcon(index).isNull())
    {
        // We have closable tab with some icon, fix the title.
        const QString text = tabText(index);

        if (!text.startsWith(QSL("  ")))
        {
            setTabText(index, QSL("  ") + text);
        }
    }
#else
    Q_UNUSED(index)
#endif
}

bool tab_widget::remove_tab(int index, bool clear_from_memory)
{
    auto widg = widget(index);
    bool closed = widg != nullptr && widg->close();

    if (closed)
    {
        if (clear_from_memory)
        {
            widg->deleteLater();
        }

        QTabWidget::removeTab(index);
    }

    return closed;
}

void tab_widget::showTabContextMenu(const QPoint& point)
{
    const auto current_tab_index = tab_bar()->tabAt(point);
    if (current_tab_index < 0)
        return;

    const auto current_tab = tab_at(current_tab_index);

    // \todo change this as a tab object should not be responsible for creating the menu object
    auto menu = current_tab->contextMenu();
    if (menu == nullptr)
        return;

    connect(menu, &QMenu::aboutToHide, menu, &QMenu::deleteLater);

    menu->addAction(
        tr("Close"), [this, current_tab_index]() { closeTab(current_tab_index); }, QKeySequence("Ctrl+F4"));
    menu->addAction(tr("Close All Tabs"), [this]() { closeAllTabs(); });
    // \todo there is a naming issue and design issue here. we already know what the 'current' tab is.
    menu->addAction(tr("Close All But This"), [this]() { closeAllTabsExceptCurrent(); });
    menu->addSeparator();
    // \todo implement this
    menu->addAction(tr("Copy Full Path"), [this]() { /* copyFullPath();*/ });
    menu->addAction(tr("Open Containing Folder"), [this]() { /* copyFullPath();*/ });
    menu->addSeparator();
    menu->addAction(tr("Pin Tab"), [this]() { /* copyFullPath();*/ });

    // show
    menu->exec(tab_bar()->mapToGlobal(point));
}

void tab_widget::makeTabVisible(Tab* tab)
{
    if (tab != nullptr)
    {
        setCurrentWidget(tab);
    }
}

void tab_widget::makeEditorVisible(hexeditor* editor)
{
    if (editor != nullptr)
    {
        setCurrentIndex(index_of_editor(editor));
    }
}

bool tab_widget::has_only_one_empty_editor() const
{
    // auto editor = textEditorAt(0);
    // editor->data().isEmpty()

    return count() == 1; // && !textEditorAt(0)->modify() &&
                         // textEditorAt(0)->length() == 0 && textEditorAt(0)->filePath().isEmpty();
}

hexeditor* tab_widget::current_editor() const
{
    return editor_at(currentIndex());
}

Tab* tab_widget::current_tab() const
{
    return tab_at(currentIndex());
}

int tab_widget::index_of_editor(hexeditor* editor) const
{
    int i = 0;

    for (const auto tab : tabs())
    {
        if (tab->primaryEditor() == editor)
            return i;
        i++;
    }

    return -1;
}

hexeditor* tab_widget::editor_at(int index) const
{
    const auto tab = tab_at(index);
    if (tab == nullptr)
        return nullptr;
    return tab->primaryEditor();
}

Tab* tab_widget::tab_at(int index) const
{
    if (index < 0 || index >= count())
        return nullptr;

    return qobject_cast<Tab*>(widget(index));
}

QList<hexeditor*> tab_widget::editors() const
{
    auto editors = QList<hexeditor*>();

    for (int i = 0; i < count(); i++)
    {
        const auto edit = editor_at(i);

        if (edit != nullptr)
            editors.append(edit);
    }

    return editors;
}

QList<Tab*> tab_widget::tabs() const
{
    auto tabs = QList<Tab*>();

    for (int i = 0; i < count(); i++)
    {
        const auto tab = tab_at(i);

        if (tab != nullptr)
            tabs.append(tab);
    }

    return tabs;
}

Tab* tab_widget::tab_with_file(const QString& /*file_path*/) const
{
#if 0
for (int i = 0; i < count(); i++) {
        Tab* edit = tabAt(i);

        if (edit != nullptr &&
            edit->primaryEditor() != nullptr &&
            QFileInfo(edit->primaryEditor()->filePath()) == QFileInfo(file_path)) {
            return edit;
        }
    }
#endif

    return nullptr;
}

void tab_widget::onTabRequestedVisibility()
{
    makeTabVisible(qobject_cast<Tab*>(sender()));
}

void tab_widget::prepareNewTab(int index)
{
    tab_bar()->setupTabControls(index);
    indentTabText(index);
    connect(tab_at(index), &Tab::visibilityRequested, this, &tab_widget::onTabRequestedVisibility);
}

int tab_widget::add_tab(Tab* widget, const QIcon& icon, const QString& label)
{
    const int index = QTabWidget::addTab(widget, icon, label);

    prepareNewTab(index);

    return index;
}

int tab_widget::add_tab(Tab* widget, const QString& label)
{
    const int index = QTabWidget::addTab(widget, label);

    prepareNewTab(index);

    return index;
}

int tab_widget::insert_tab(int index, Tab* widget, const QIcon& icon, const QString& label)
{
    const int tab_index = QTabWidget::insertTab(index, widget, icon, label);

    prepareNewTab(index);

    return tab_index;
}

int tab_widget::insert_tab(int index, Tab* widget, const QString& label)
{
    const int tab_index = QTabWidget::insertTab(index, widget, label);

    prepareNewTab(index);

    return tab_index;
}

void tab_widget::change_icon(int index, const QIcon& new_icon)
{
    setTabIcon(index, new_icon);
    indentTabText(index);
}

void tab_widget::change_title(int index, const QString& new_title, const QString& tool_tip)
{
    setTabText(index, new_title);
    setTabToolTip(index, tool_tip);
    indentTabText(index);
}
