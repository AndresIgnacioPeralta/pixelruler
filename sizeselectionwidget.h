#ifndef SIZESELECTIONWIDGET_H
#define SIZESELECTIONWIDGET_H

#include <QFrame>

namespace Ui {
class SizeSelectionWidget;
}

class SizeSelectionWidget : public QFrame
{
    Q_OBJECT

public:
    explicit SizeSelectionWidget(const int size, QWidget *parent = 0);

    ~SizeSelectionWidget();

private:
    Ui::SizeSelectionWidget *ui;

    virtual void keyPressEvent(QKeyEvent* event);

    virtual void closeEvent(QCloseEvent *);

signals:
    void notifySizeUpdated(const int size);

    void notifyWidgetClosed();
};

#endif // SIZESELECTIONWIDGET_H
