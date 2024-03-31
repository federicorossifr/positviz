#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "PositVizWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PositVizWindow pw;
    pw.show();
    return QApplication::exec();
}
