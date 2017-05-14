#include "configurationwidget.h"
#include "ui_configurationwidget.h"
#include <QMouseEvent>

ConfigurationWidget::ConfigurationWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConfigurationWidget)
{
    ui->setupUi(this);
    setWindowTitle("Configure ruler");
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &ConfigurationWidget::onButtonCancelClicked);
    connect(ui->buttonOK,     &QPushButton::clicked, this, &ConfigurationWidget::onButtonOkClicked);
    connect(ui->sliderOpacity, &QSlider::valueChanged, this, &ConfigurationWidget::notifyOpacitySelected);
    connect(ui->colorSelectionWidget, &ColorSelectorWIdget::notifyColorSelected, this, &ConfigurationWidget::notifyColorSelected);
    connect(ui->radioPixels, &QRadioButton::clicked, this, &ConfigurationWidget::onRadioPixelsChecked);
    connect(ui->radioCM, &QRadioButton::clicked, this, &ConfigurationWidget::onRadioCMChecked);
    connect(ui->radioInches, &QRadioButton::clicked, this, &ConfigurationWidget::onRadioInchesChecked);
}

ConfigurationWidget::~ConfigurationWidget() {
    delete ui;
}

void ConfigurationWidget::loadConfiguration() {

}

void ConfigurationWidget::onButtonOkClicked() {
    close();
}

void ConfigurationWidget::onButtonCancelClicked() {
    close();
}

void ConfigurationWidget::onRadioPixelsChecked() {
    emit notifyUnitSelected(Unit::PIXEL);
}

void ConfigurationWidget::onRadioCMChecked() {
    emit notifyUnitSelected(Unit::CENTIMETER);
}

void ConfigurationWidget::onRadioInchesChecked() {
    emit notifyUnitSelected(Unit::INCH);
}

void ConfigurationWidget::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        move(mapToParent(event->pos() - clickpostion));
    }
}

void ConfigurationWidget::mousePressEvent(QMouseEvent* event) {
    clickpostion = event->pos();
}

void ConfigurationWidget::closeEvent(QCloseEvent *) {
    emit notifyWidgetClosed();
    close();
}
