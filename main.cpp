#include "mainwindow.h"
#include "tcpsocket.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TcpSocket s;
    w.show();
    s.doConnect();
    return a.exec();
}
