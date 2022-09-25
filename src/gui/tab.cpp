#include "gui/tab.h"
#include "gui/tabwidget.h"

Tab::Tab(tab_widget* parent)
    : QWidget(parent)
    , tabwidget_(parent)
{
}

int Tab::index() const
{
    if (!tabwidget_)
        return -1;

    // \todo I am pretty sure this can be done better
    const auto widget = static_cast<QWidget*>(const_cast<Tab*>(this));
    return tabwidget_->indexOf(widget);
}

void Tab::requestVisibility()
{
    emit visibilityRequested();
}
