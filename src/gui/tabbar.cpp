#include "gui/tabbar.h"

#include <QMouseEvent>
#include <QStyle>
#include <QPushButton>
#include "QTabBar"

TabBar::TabBar(QWidget* parent)
    : QTabBar(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void TabBar::setupTabControls(int index)
{
    //const auto style_hint = style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, nullptr, this);
    //const auto button_position = static_cast<ButtonPosition>(style_hint);

    // QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    // QFont monospace(family);
}

//void TabBar::wheelEvent(QWheelEvent* event)
//{
//    const int current_index = currentIndex();
//    const int number_of_tabs = count();
//
//    // Make sure rotating works.
//    if (number_of_tabs > 1)
//    {
//        if (event->angleDelta().x() > 0)
//        {
//            // Scroll to the LEFT tab.
//            setCurrentIndex(current_index == 0 ? number_of_tabs - 1 : current_index - 1);
//        }
//        else if (event->pixelDelta().x() < 0)
//        {
//            // Scroll to the RIGHT tab.
//            setCurrentIndex(current_index == number_of_tabs - 1 ? 0 : current_index + 1);
//        }
//    }
//}

void TabBar::mousePressEvent(QMouseEvent* event)
{
    QTabBar::mousePressEvent(event);
    //const int tab_index = tabAt(event->pos());

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
