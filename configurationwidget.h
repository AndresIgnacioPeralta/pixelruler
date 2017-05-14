#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <QFrame>
#include "constants.h"
namespace Ui {
class ConfigurationWidget;
}

class ConfigurationWidget : public QFrame {
    Q_OBJECT

public:
    explicit ConfigurationWidget(QWidget *parent = 0);

    ~ConfigurationWidget();

private:
    Ui::ConfigurationWidget *ui;

    QPoint clickpostion;

    void loadConfiguration();

    virtual void mouseMoveEvent(QMouseEvent* event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void closeEvent(QCloseEvent *);

public slots:
    void onButtonOkClicked();

    void onButtonCancelClicked();

    void onRadioPixelsChecked();

    void onRadioCMChecked();

    void onRadioInchesChecked();

signals:
    void notifyColorSelected(const ColorPair color);

    void notifyOpacitySelected(const int value);

    void notifyUnitSelected(const Unit unit);

    void notifyWidgetClosed();
};

#endif // CONFIGURATIONWIDGET_H
