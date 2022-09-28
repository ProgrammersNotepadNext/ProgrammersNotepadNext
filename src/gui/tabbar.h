#pragma once

#include <QTabBar>

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit TabBar(QWidget* parent = nullptr);
    ~TabBar() override = default;

    void setupTabControls(int index);

private:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    //void wheelEvent(QWheelEvent* event) override;

signals:
    void emptySpaceDoubleClicked();
};
