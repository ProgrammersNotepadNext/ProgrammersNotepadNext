#include "gui/glyph_button.h"

#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QStyle>
#include <QStyleOption>
#include <QToolButton>

glyph_button::glyph_button(QWidget* parent)
    : QToolButton(parent)
{
}

void glyph_button::paintEvent(QPaintEvent* /*e*/)
{
    QPainter painter(this);
    /*
    +----------+
    |          |
    |  +----+  |
    |  |    |  |
    |  +----+  |
    |          |
    +----------+
    */

    // padding
    const auto vertical_offset = padding_.left - padding_.right;
    const auto horizontal_offset = padding_.top - padding_.bottom;

    const auto button_size = size();
    const auto padded_width = button_size.width() - vertical_offset;
    const auto padded_height = button_size.height() - horizontal_offset;

    auto rect = QRect(padding_.left, padding_.top, padded_width, padded_height);

    if (!isEnabled())
    {
        painter.setOpacity(disabled_opacity_);
    }
    else
    {
        if (isChecked() || underMouse())
        {
            painter.setOpacity(enabled_opacity_);
        }
    }

    if (icon().isNull())
    {
        if (explicit_color_.isValid())
        {
            painter.fillRect(rect, explicit_color_);
        }
        else
        {
            rect.adjust(0, 0, -1, -1);
            painter.drawRect(rect);

            painter.drawText(rect, text(), QTextOption(Qt::AlignCenter));
        }
    }
    else
    {
        icon().paint(&painter, rect);
    }
}

QColor glyph_button::explicitColor() const
{
    return explicit_color_;
}

void glyph_button::setExplicitColor(const QColor& explicit_color)
{
    explicit_color_ = explicit_color;

    update();
}

void glyph_button::setPadding(int left, int top, int right, int bottom)
{
    padding_.left = left;
    padding_.top = top;
    padding_.right = right;
    padding_.bottom = bottom;

    update();
}

void glyph_button::setChecked(bool checked)
{
    QToolButton::setChecked(checked);
    update();
}

void glyph_button::reactOnActionChange(QAction* action)
{
    if (action != nullptr)
    {
        setEnabled(action->isEnabled());
        setCheckable(action->isCheckable());
        setChecked(action->isChecked());
        setIcon(action->icon());
        setToolTip(action->toolTip());
    }
}

void glyph_button::reactOnSenderActionChange()
{
    reactOnActionChange(qobject_cast<QAction*>(sender()));
}
