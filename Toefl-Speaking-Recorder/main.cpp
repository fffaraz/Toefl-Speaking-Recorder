#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    auto lp = QCoreApplication::libraryPaths();
    lp.append(QDir::currentPath() + "/plugins");
    QCoreApplication::setLibraryPaths(lp);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
