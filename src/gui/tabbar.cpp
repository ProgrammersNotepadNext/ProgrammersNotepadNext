#include "gui/tabbar.h"
#include "gui/glyph_button.h"

#include <QMouseEvent>
#include <QStyle>
#include <QPushButton>
#include "QTabBar"

TabBar::TabBar(QWidget* parent)
    : QTabBar(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
}

namespace GlyphCodes
{
// see
// https://github.com/microsoft/vscode/blob/4ad1d7db1fbeb0f9987f852dd0213c8f771f4aba/src/vs/base/browser/ui/codiconLabel/codicon/codicon.css
constexpr QChar close{0xea76};
constexpr QChar pin{0xeb2b};
}; // namespace GlyphCodes

void TabBar::setupTabControls(int index)
{
    const auto style_hint = style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, nullptr, this);
    const auto button_position = static_cast<ButtonPosition>(style_hint);

    // QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    // QFont monospace(family);

    auto* closebutton = new glyph_button(this);
    closebutton->setFont(QFont("codicon"));
    closebutton->setToolTip(tr("Close (Ctrl + F4)"));
    closebutton->setText(GlyphCodes::close);
    closebutton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    closebutton->setAutoRaise(true);
    closebutton->setContentsMargins(0, 0, 0, 0);

    // Close underlying tab when button is clicked.
    connect(closebutton, &glyph_button::clicked, this, &TabBar::closeTabViaButton);
    setTabButton(index, button_position, closebutton);
}

void TabBar::closeTabViaButton()
{
    const auto* close_button = qobject_cast<QAbstractButton*>(sender());

    if (close_button != nullptr)
    {
        const auto style_hint = style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, nullptr, this);
        const auto button_position = static_cast<ButtonPosition>(style_hint);

        // Find index of tab for this close button.
        for (int i = 0; i < count(); i++)
        {
            if (tabButton(i, button_position) == close_button)
            {
                emit tabCloseRequested(i);
                return;
            }
        }
    }
}

void TabBar::wheelEvent(QWheelEvent* event)
{
    const int current_index = currentIndex();
    const int number_of_tabs = count();

    // Make sure rotating works.
    if (number_of_tabs > 1)
    {
        if (event->delta() > 0)
        {
            // Scroll to the LEFT tab.
            setCurrentIndex(current_index == 0 ? number_of_tabs - 1 : current_index - 1);
        }
        else if (event->delta() < 0)
        {
            // Scroll to the RIGHT tab.
            setCurrentIndex(current_index == number_of_tabs - 1 ? 0 : current_index + 1);
        }
    }
}

void TabBar::mousePressEvent(QMouseEvent* event)
{
    QTabBar::mousePressEvent(event);
    const int tab_index = tabAt(event->pos());

    // Check if user clicked on some tab or on empty space.
#if 0
    if (tab_index >= 0) {
        // Check if user clicked tab with middle button.
        // NOTE: This needs to be done here because destination does not know the original event.
        if ((event->button() & Qt::MouseButton::MiddleButton) == Qt::MouseButton::MiddleButton &&
            qApp->settings()->value(GROUP(GUI), SETTING(GUI::TabCloseMiddleClick)).toBool()) {
            // This tab is closable, so we can close it.
            emit tabCloseRequested(tab_index);
        }
    }
#endif
}

void TabBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    QTabBar::mouseDoubleClickEvent(event);

#if 0
    const int tab_index = tabAt(event->pos());

    // Check if user clicked on some tab or on empty space.
    if (tab_index >= 0) {
        // Check if user clicked tab with middle button.
        // NOTE: This needs to be done here because destination does not know the original event.
        if ((event->button() & Qt::MouseButton::LeftButton) == Qt::MouseButton::LeftButton &&
            qApp->settings()->value(GROUP(GUI), SETTING(GUI::TabCloseDoubleClick)).toBool()) {
            // This tab is closable, so we can close it.
            emit tabCloseRequested(tab_index);
        }
    }
    else if (event->button() == Qt::MouseButton::LeftButton) {
        emit emptySpaceDoubleClicked();
    }
#endif
}
