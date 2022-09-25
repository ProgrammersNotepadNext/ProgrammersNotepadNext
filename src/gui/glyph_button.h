#pragma once

#include <QToolButton>

struct padding
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
};

class glyph_button : public QToolButton
{
    Q_OBJECT

public:
    explicit glyph_button(QWidget* parent = nullptr);
    ~glyph_button() override = default;

    auto explicitColor() const -> QColor;
    void setExplicitColor(const QColor& explicit_color);

public slots:
    void setPadding(int left, int top, int right, int bottom);
    void setChecked(bool checked);
    void reactOnActionChange(QAction* action);
    void reactOnSenderActionChange();

protected:
    void paintEvent(QPaintEvent* e) override;

private:
    QColor explicit_color_;
    padding padding_{};
    qreal enabled_opacity_{0.7};
    qreal disabled_opacity_{0.3};
};
