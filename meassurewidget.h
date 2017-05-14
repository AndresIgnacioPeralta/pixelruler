#ifndef MEASSUREWIDGET_H
#define MEASSUREWIDGET_H

#include <QFrame>
#include "constants.h"

namespace Ui {
class MeassureWidget;
}

class MeassureWidget : public QFrame {
    Q_OBJECT

public:
    explicit MeassureWidget(QWidget* const parent = nullptr);

    ~MeassureWidget();

    void setPosition(const Position pos);

    void setMousePosition(const QPoint mousePos);

private:
    Ui::MeassureWidget *ui;

    Position position;

    Unit rulerUnit;

    ColorPair rulerColor;

    qreal rulerOpacity;

    LinesSide side;

    QPoint mousePosition;

    int drawingMinUnit;

    int drawingMiddleUnit;

    int drawingBasicUnit;

    void drawHorizontalLines(QPainter& painter);

    void drawVerticalLines(QPainter& painter);

    void drawMousePositionLine(QPainter& painter);

    virtual void paintEvent(QPaintEvent* event);

public slots:
    void setColor(const ColorPair color);

    void setUnit(const Unit unit);

    void setOpacity(const int);

    void changeSide();
};

#endif // MEASSUREWIDGET_H
