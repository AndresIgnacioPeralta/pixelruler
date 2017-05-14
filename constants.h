#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStringList>
#include <QList>

enum class Position {
    HORIZONTAL,
    VERTICAL
};

enum class Unit {
    CENTIMETER,
    PIXEL,
    INCH
};

enum class LinesSide {
    LEFT,   //TOP
    RIGHT,  //BOTTOM
    BOTH
};

static const unsigned int RULER_WIDTH(86);
static const unsigned int DEFAULT_RULER_HEIGHT(500);
static const int WHEEL_DELTA(15);
static const QColor fontColor("#FEFEFE");
static const QColor mousePositionColor("cyan");

static const int RULER_SMALL_LINE(10u); //draw a line every x pixels
static const int RULER_BIG_LINE(50u); //draw a big line every x pixels
static const unsigned int RULER_LINE_LENGHT(10u);
static const unsigned int RULER_BIG_LINE_LENGHT(20u);
static const unsigned int RULER_NUMBER_HOFFSET(4u);
static const unsigned int RULER_NUMBER_VOFFSET(2u);

struct ColorPair {
    QColor main;
    QColor alter;
    ColorPair(const QColor m, const QColor a) : main(m), alter(a) {}
    ColorPair() : main(QColor("#3498db")), alter(QColor("#2980b9")) {}
    void operator=(ColorPair pair1) {
        main = pair1.main;
        alter = pair1.alter;
    }
};

#endif // CONSTANTS_H
