#include "gui/editortab.h"

#include "gui/tabwidget.h"
#include "mainwindow.h"

#include <QCloseEvent>
#include <QLayout>

EditorTab::EditorTab(MainWindow* text_app, hexeditor* editor)
    : Tab(text_app->tabWidget())
    , m_editor(editor)
{
    auto* lay = new QVBoxLayout(this);

    lay->setMargin(0);
    lay->setSpacing(0);
    lay->addWidget(editor, 1);

    updateTitleFromEditor();
    // m_editor->setReadOnly()

    // connect(m_editor, &TextEditor::visibilityRequested, this, &Tab::visibilityRequested);
    // connect(m_editor, &TextEditor::readOnlyChanged, this, [this](bool read_only) {
    //  updateIcon(read_only);

    // emit iconChanged(m_icon);
    //});
    // connect(m_editor, &TextEditor::savePointChanged, this, [this]() {
    //  updateIcon(m_editor->readOnly());
    //  updateTitleFromEditor();
    //
    //  emit titleChanged(m_title, m_toolTip);
    //});
}

EditorTab::EditorTab(MainWindow* text_app)
    : EditorTab(text_app, new hexeditor(this))
{
}

QMenu* EditorTab::contextMenu() const
{
    auto* menu = new QMenu();
    // don't do shit for now
    // QAction* act_read_only = menu->addAction(qApp->icons()->fromTheme(QSL("lock")), tr("Read-Only Mode"), [this](bool
    // toggle) {
    //    m_editor->setReadOnly(toggle);
    //    });
    //
    // act_read_only->setCheckable(true);
    // act_read_only->setChecked(m_editor->readOnly());

    const auto save_text = tr("Save") + " " + m_title;
    menu->addAction(
        save_text, [this]() { m_editor->save(); }, QKeySequence("Ctrl+S"));

    return menu;
}

hexeditor* EditorTab::primaryEditor() const
{
    return m_editor;
}

QList<hexeditor*> EditorTab::allEditors() const
{
    return QList<hexeditor*>() << primaryEditor();
}

int EditorTab::countOfEditors() const
{
    return 1;
}

void EditorTab::closeEvent(QCloseEvent* /*event*/)
{
    // don't do shit for now
    // bool ok = false;
    //
    // m_editor->closeEditor(ok);
    // m_editor->close();
    //
    // if (!ok) {
    //    event->ignore();
    //}
    // else {
    //    Tab::closeEvent(event);
    //}
}

void EditorTab::updateIcon(bool /*read_only*/)
{
    // if (read_only) {
    //    m_icon = qApp->icons()->fromTheme(QSL("lock"));
    //}
    // else {
    //    m_icon = m_editor->modify() ?
    //        qApp->icons()->fromTheme(QSL("gtk-dialog-warning")) :
    //        QIcon();
    //}
}

void EditorTab::updateTitleFromEditor()
{
    if (m_editor == nullptr)
        return;

    const auto filepath = m_editor->filepath();
    if (filepath.isEmpty())
    {
        m_title = tr("New file");
    }
    else
    {
        m_title = m_editor->filename();
    }
}

QString EditorTab::title() const
{
    return m_title;
}

QString EditorTab::toolTip() const
{
    return m_toolTip;
}

QIcon EditorTab::icon() const
{
    return m_icon;
}
