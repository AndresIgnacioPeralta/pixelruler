#include "coloritem.h"
#include <QPainter>

ColorItem::ColorItem(const ColorPair color) :
    QPushButton(),
    itemColor(color) {
    setCheckable(true);
    setFixedSize(30, 30);
}

ColorPair ColorItem::getColor() const {
    return itemColor;
}

void ColorItem::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(itemColor.main);
    painter.setPen(itemColor.main);
    painter.drawRect(rect());
    if(isChecked()) {
        painter.setBrush(QColor("#FEFEFE"));
        painter.setPen(QColor("#FEFEFE"));
        painter.drawEllipse(QPoint(width() / 2, height() / 2), 4, 4);
    }
}
