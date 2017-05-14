#include "rulerwidget.h"
#include "ui_rulerwidget.h"
#include "configurationwidget.h"
#include "sizeselectionwidget.h"
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QShortcut>

RulerWidget::RulerWidget(QWidget * const parent) :
    QFrame(parent),
    ui(new Ui::RulerWidget),
    position(Position::VERTICAL),
    configurationWidget(nullptr),
    sizeSelectionWidget(nullptr),
    showOptions(false){

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_Hover);

    connect(ui->buttonClose,       &QPushButton::clicked, this, &RulerWidget::onCloseButtonClicked);
    connect(ui->buttonConfigurate, &QPushButton::clicked, this, &RulerWidget::onConfigureButtonClicked);
    connect(ui->buttonMinimize,    &QPushButton::clicked, this, &RulerWidget::onMinimizeButtonClicked);
    connect(ui->buttonRotate,      &QPushButton::clicked, this, &RulerWidget::onRotateButtonClicked);
    showButtons(showOptions);
    setMouseTracking(true);
    ui->meassureWidget->setMouseTracking(true);
    setStyleSheet("QPushButton {background-color: blue; border-radius:15px; border: 1px solir red; color: #FEFEFE;}");

    /*QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect;
    wndShadow->setBlurRadius(10.0);
    wndShadow->setColor(QColor(0, 0, 0, 160));
    wndShadow->setOffset(4.0);
    setGraphicsEffect(wndShadow);*/
}

RulerWidget::~RulerWidget() {
    delete ui;
    delete configurationWidget;
    delete sizeSelectionWidget;
}

void RulerWidget::changeToHorizontal() {
   //setGeometry(x(), y(), DEFAULT_RULER_HEIGHT, RULER_WIDTH);
   setFixedHeight(RULER_WIDTH);
   setFixedWidth(DEFAULT_RULER_HEIGHT);

   ui->topLayout->setDirection(QBoxLayout::TopToBottom);
   ui->bottomLayout->setDirection(QBoxLayout::TopToBottom);
   ui->mainLayout->setDirection(QBoxLayout::LeftToRight);
}

void RulerWidget::changeToVertical() {
    //setGeometry(x(), y(), RULER_WIDTH, DEFAULT_RULER_HEIGHT);
    setFixedWidth(RULER_WIDTH);
    setFixedHeight(DEFAULT_RULER_HEIGHT);
    ui->topLayout->setDirection(QBoxLayout::LeftToRight);
    ui->bottomLayout->setDirection(QBoxLayout::LeftToRight);
    ui->mainLayout->setDirection(QBoxLayout::TopToBottom);
}

void RulerWidget::showButtons(const bool show) {
    ui->buttonClose->setVisible(show);
    ui->buttonConfigurate->setVisible(show);
    ui->buttonMinimize->setVisible(show);
    ui->buttonRotate->setVisible(show);
    const int margin = show ? 5 : 0;
    ui->topLayout->setContentsMargins(margin, margin, margin, margin);
    ui->bottomLayout->setContentsMargins(margin, margin, margin, margin);
}

int RulerWidget::getLenght() const {
    if(position == Position::HORIZONTAL) {
        return width();
    } else {
        return height();
    }
}

void RulerWidget::mousePressEvent(QMouseEvent* event) {
    clickpostion = event->pos();
    if(event->buttons() & Qt::RightButton) {
        showOptions = !showOptions;
        showButtons(showOptions);
    }
}

void RulerWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        onRotateButtonClicked();
    }
}

void RulerWidget::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        move(mapToParent(event->pos() - clickpostion));
    }
    ui->meassureWidget->setMousePosition(event->pos());
}

void RulerWidget::wheelEvent(QWheelEvent* event) {
    int delta = 0;
    if(event->delta() > 0) {
        delta = WHEEL_DELTA;
    } else {
        delta = -WHEEL_DELTA;
    }
    if(position == Position::HORIZONTAL) {
        if(width() >= RULER_WIDTH)
          setFixedWidth(width() + delta);
    } else {
        if(height() >= RULER_WIDTH)
          setFixedHeight(height() + delta);
    }
}

void RulerWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Up) {
        move(x(), y() - 1);
    } else if (event->key() == Qt::Key_Down) {
        move(x(), y() + 1);
    } else if (event->key() == Qt::Key_Left) {
        move(x() - 1, y());
    } else if (event->key() == Qt::Key_Right) {
        move(x() + 1, y());
    } else if (event->key() == Qt::Key_S) {
        if (sizeSelectionWidget == nullptr) {
            sizeSelectionWidget = new SizeSelectionWidget(getLenght());
            connect(sizeSelectionWidget, &SizeSelectionWidget::notifySizeUpdated, this, &RulerWidget::onLengthChanged);
            connect(sizeSelectionWidget, &SizeSelectionWidget::notifyWidgetClosed, this, &RulerWidget::onSizeWidgetClosed);
            sizeSelectionWidget->show();
        }
    } else if (event->key() == Qt::Key_L) {
        ui->meassureWidget->changeSide();
    }
    else if (event->key() == Qt::Key_C) {
        onConfigureButtonClicked();
    }
}

void RulerWidget::onMinimizeButtonClicked() {
    showMinimized();
}

void RulerWidget::onCloseButtonClicked() {
    if (configurationWidget != nullptr) {
        configurationWidget->close();
    }
    if (sizeSelectionWidget != nullptr) {
        sizeSelectionWidget->close();
    }
    close();
}

void RulerWidget::onRotateButtonClicked() {
    if (position == Position::HORIZONTAL) {
        position = Position::VERTICAL;
        changeToVertical();
    } else {
        position = Position::HORIZONTAL;
        changeToHorizontal();
    }
    ui->meassureWidget->setPosition(position);
}

void RulerWidget::onConfigureButtonClicked() {
    if (configurationWidget == nullptr) {
        configurationWidget = new ConfigurationWidget();
        connect(configurationWidget,   &ConfigurationWidget::notifyColorSelected,   ui->meassureWidget, &MeassureWidget::setColor);
        connect(configurationWidget,   &ConfigurationWidget::notifyOpacitySelected, this, &RulerWidget::onOpacitySet);
        connect(configurationWidget,   &ConfigurationWidget::notifyWidgetClosed, this, &RulerWidget::onConfigurationWidgetClosed);
        connect(configurationWidget,   &ConfigurationWidget::notifyUnitSelected,    ui->meassureWidget, &MeassureWidget::setUnit);
        configurationWidget->show();
    }
}

void RulerWidget::onLengthChanged(const int value) {
    if(position == Position::HORIZONTAL) {
        setFixedWidth(value);
    } else {
        setFixedHeight(value);
    }
}

void RulerWidget::onOpacitySet(const int value) {
    qreal opacity = (1.0 / value);
    setWindowOpacity(opacity);
}

void RulerWidget::onConfigurationWidgetClosed() {
    configurationWidget = nullptr;
}

void RulerWidget::onSizeWidgetClosed() {
    sizeSelectionWidget = nullptr;
}
