#include "colorselectorwidget.h"
#include "ui_colorselectorwidget.h"
#include "constants.h"

#include <QDebug>

static QList<ColorPair> colorSchemes = QList<ColorPair>() <<
                                       ColorPair(QColor("#3498db"), QColor("#2980b9")) <<
                                       ColorPair(QColor("#9b59b6"), QColor("#8e44ad")) <<
                                       ColorPair(QColor("#34495e"), QColor("#2c3e50")) <<
                                       ColorPair(QColor("#f1c40f"), QColor("#f39c12")) <<
                                       ColorPair(QColor("#e67e22"), QColor("#d35400")) <<
                                       ColorPair(QColor("#2ecc71"), QColor("#27ae60")) <<
                                       ColorPair(QColor("#e74c3c"), QColor("#c0392b"));


ColorSelectorWIdget::ColorSelectorWIdget(QWidget * const parent) :
    QWidget(parent),
    ui(new Ui::ColorSelectorWIdget) {
    ui->setupUi(this);

    for(ColorPair color : colorSchemes) {
        ColorItem* item = new ColorItem(color);
        addColor(item);
        connect(item, &ColorItem::clicked, this, &ColorSelectorWIdget::onColorItemSelected);
    }
}

ColorSelectorWIdget::~ColorSelectorWIdget() {
    delete ui;
}

void ColorSelectorWIdget::addColor(ColorItem* colorItem) {
    ui->layoutColorContainer->addWidget(colorItem);
}

void ColorSelectorWIdget::onColorItemSelected(const bool) {
    ColorItem* selected = qobject_cast<ColorItem*>(sender());
    for(auto index = 0; index < ui->layoutColorContainer->count(); ++index) {
        ColorItem* widget = qobject_cast<ColorItem*>(ui->layoutColorContainer->itemAt(index)->widget());
        if(widget != selected) {
            widget->setChecked(false);
        }
    }
    emit notifyColorSelected(selected->getColor());
}
