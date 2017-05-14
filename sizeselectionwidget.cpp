#include "sizeselectionwidget.h"
#include "ui_sizeselectionwidget.h"
#include "constants.h"
#include <QKeyEvent>

SizeSelectionWidget::SizeSelectionWidget(const int size, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SizeSelectionWidget) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    ui->spinSize->setValue(size);
    connect(ui->spinSize, SIGNAL(valueChanged(int)), this, SIGNAL(notifySizeUpdated(int)));
    ui->spinSize->selectAll();
    ui->spinSize->setMinimum(RULER_WIDTH);
}

SizeSelectionWidget::~SizeSelectionWidget() {
    delete ui;
}

void SizeSelectionWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        emit notifySizeUpdated(ui->spinSize->value());
        close();
    } else if(event->key() == Qt::Key_Escape) {
        close();
    }
}

void SizeSelectionWidget::closeEvent(QCloseEvent *){
    emit notifyWidgetClosed();
    close();
}
