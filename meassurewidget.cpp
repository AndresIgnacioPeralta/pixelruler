#include "meassurewidget.h"
#include "ui_meassurewidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

MeassureWidget::MeassureWidget(QWidget * const parent) :
    QFrame(parent),
    ui(new Ui::MeassureWidget),
    rulerOpacity(1.0),
    side(LinesSide::BOTH),
    drawingMinUnit(10),
    drawingMiddleUnit(50),
    drawingBasicUnit(1){
    ui->setupUi(this);
    setMouseTracking(true);
}

MeassureWidget::~MeassureWidget() {
    delete ui;
}

void MeassureWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(rulerOpacity);
    painter.setBrush(QBrush(rulerColor.main));
    painter.setPen(rulerColor.main);
    painter.drawRect(rect());
    painter.setOpacity(1.0);
    painter.setBrush(QBrush(rulerColor.alter));
    painter.setPen(rulerColor.alter);
    if(position == Position::HORIZONTAL) {
        QRect rectHorizontal(rect().topLeft().rx(), rect().topLeft().ry(), rect().bottomRight().rx(), rect().bottomRight().ry() / 2);
        painter.drawRect(rectHorizontal);
        painter.setPen(QColor(fontColor));
        drawHorizontalLines(painter);
    } else {
        QRect rectVertical(rect().topLeft().rx(), rect().topLeft().ry(), rect().bottomRight().rx() / 2, rect().bottomRight().ry());
        painter.drawRect(rectVertical);
        painter.setPen(QColor(fontColor));
        drawVerticalLines(painter);
    }
    drawMousePositionLine(painter);
}

void MeassureWidget::setPosition(const Position pos) {
    position = pos;
    update();
}

void MeassureWidget::setMousePosition(const QPoint mousePos) {
    mousePosition = mousePos;
    update();
}

void MeassureWidget::setColor(const ColorPair color) {
    rulerColor = color;
    update();
}

void MeassureWidget::setUnit(const Unit unit) {
    rulerUnit = unit;
    if(unit == Unit::CENTIMETER) {
        drawingMinUnit = width() / widthMM();
        drawingMiddleUnit = drawingMinUnit * 10;
        drawingBasicUnit = 10;
    } else if (unit == Unit::INCH) {
        drawingMinUnit = logicalDpiX();
        drawingMiddleUnit = drawingMinUnit * 10;
        drawingBasicUnit = 1;
    } else {
        drawingMinUnit = 10;
        drawingMiddleUnit = 50;
    }
    update();
}

void MeassureWidget::setOpacity(const int) {
    /*rulerOpacity = 1 / opacity;l
    setWindowOpacity(rulerOpacity);
    update();*/
}

void MeassureWidget::changeSide() {
    side = LinesSide(((int(side) + 1) % 3));
    update();
}

void MeassureWidget::drawHorizontalLines(QPainter &painter) {
    for(auto i = drawingMinUnit; i < width(); i+= drawingMinUnit) {
        int length = RULER_LINE_LENGHT;
        if(i % drawingMiddleUnit == 0) {
            length = RULER_BIG_LINE_LENGHT;
            painter.drawText(QPoint(i + RULER_NUMBER_HOFFSET, length + RULER_NUMBER_VOFFSET), QString::number(i / drawingBasicUnit));
        }
        if(side == LinesSide::LEFT) {
            painter.drawLine(i, 0, i, length);
        } else if (side == LinesSide::RIGHT) {
            painter.drawLine(i, RULER_WIDTH - length, i, RULER_WIDTH);
        } else {
            painter.drawLine(i, 0, i, length);
            painter.drawLine(i, RULER_WIDTH - length, i, RULER_WIDTH);
        }
    }
}

void MeassureWidget::drawVerticalLines(QPainter &painter) {
    for(auto i = drawingMinUnit; i < height(); i+= drawingMinUnit) {
        int length = RULER_LINE_LENGHT;
        if(i % drawingMiddleUnit == 0) {
            length = RULER_BIG_LINE_LENGHT;
            painter.drawText(QPoint(length + RULER_NUMBER_VOFFSET, i + RULER_NUMBER_HOFFSET), QString::number(i / drawingBasicUnit));
        }
        if(side == LinesSide::LEFT) {
            painter.drawLine(0, i, length, i);
        } else if (side == LinesSide::RIGHT) {
            painter.drawLine(RULER_WIDTH - length, i, RULER_WIDTH, i);
        } else {
            painter.drawLine(0, i, length, i);
            painter.drawLine(RULER_WIDTH - length, i, RULER_WIDTH, i);
        }
    }
}

void MeassureWidget::drawMousePositionLine(QPainter &painter) {
    painter.setPen(QColor(mousePositionColor));
    if(position == Position::HORIZONTAL) {
        painter.drawText(width() / 2, height() / 2, QString::number(mousePosition.x()));
        painter.drawLine(mousePosition.x(), 0, mousePosition.x(), RULER_WIDTH);
    } else {
        painter.drawText(width() / 2, height() / 2, QString::number(mousePosition.y()));

        painter.drawLine(0, mousePosition.y(), RULER_WIDTH, mousePosition.y());
    }
}
