#ifndef RULERWIDGET_H
#define RULERWIDGET_H

#include <QFrame>
#include "constants.h"

namespace Ui {
class RulerWidget;
}

class SizeSelectionWidget;
class ConfigurationWidget;
class RulerWidget : public QFrame {
    Q_OBJECT

public:
    explicit RulerWidget(QWidget* const parent = nullptr);

    ~RulerWidget();

private:
    Ui::RulerWidget *ui;

    Position position;

    QPoint clickpostion;

    ConfigurationWidget* configurationWidget;

    SizeSelectionWidget* sizeSelectionWidget;

    bool showOptions;

    void changeToHorizontal();

    void changeToVertical();

    void showButtons(const bool show);

    int getLenght() const;

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseDoubleClickEvent(QMouseEvent* event);

    virtual void mouseMoveEvent(QMouseEvent* event);

    virtual void wheelEvent(QWheelEvent* event);

    virtual void keyPressEvent(QKeyEvent* event);

private slots:
    void onMinimizeButtonClicked();

    void onCloseButtonClicked();

    void onRotateButtonClicked();

    void onConfigureButtonClicked();

    void onLengthChanged(const int value);

    void onOpacitySet(const int value);

    void onConfigurationWidgetClosed();

    void onSizeWidgetClosed();
};

#endif // RULERWIDGET_H
