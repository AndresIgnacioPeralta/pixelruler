#ifndef COLORITEM_H
#define COLORITEM_H

#include <QPushButton>
#include "constants.h"

class ColorItem : public QPushButton {
    Q_OBJECT
public:
    ColorItem(const ColorPair color);

    ColorPair getColor() const;

private:
    const ColorPair itemColor;

    virtual void paintEvent(QPaintEvent* event);
};

#endif // COLORITEM_H
