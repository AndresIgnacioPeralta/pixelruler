#include "rulerwidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleFile(":/style.qss");
    styleFile.open(QFile::ReadOnly);
    qApp->setStyleSheet(QLatin1String(styleFile.readAll()));
    RulerWidget w;
    w.show();

    return a.exec();
}
