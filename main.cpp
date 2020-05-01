#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec::codecForLocale();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
