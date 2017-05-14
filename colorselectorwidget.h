#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H

#include <QWidget>
#include "coloritem.h"
namespace Ui {
class ColorSelectorWIdget;
}
class ColorSelectorWIdget : public QWidget {
    Q_OBJECT

public:
    explicit ColorSelectorWIdget(QWidget* const parent = nullptr);

    ~ColorSelectorWIdget();

    void addColor(ColorItem *colorItem);

private:
    Ui::ColorSelectorWIdget *ui;

private slots:
    void onColorItemSelected(const bool);

signals:
    void notifyColorSelected(const ColorPair color);

};

#endif // COLORSELECTORWIDGET_H
