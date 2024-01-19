#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include "tcpsocket.h"

TcpSocket s;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    s.doConnect();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LeftButton_pressed()
{
    qDebug("Turn Left Pressed");
    s.write("LP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_RightButton_pressed()
{
    qDebug("Turn Right Pressed");
    s.write("RP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_BackwardButton_pressed()
{
    qDebug("Move Backward Pressed");
    s.write("BP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_ForwardButton_pressed()
{
    qDebug("Move Forward Pressed");
    s.write("FP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_ForwardButton_released()
{
    qDebug("Move Forward Released");
    s.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_BackwardButton_released()
{
    qDebug("Move Backward Released");
    s.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_LeftButton_released()
{
    qDebug("Turn Left Released");
    s.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_RightButton_released()
{
    qDebug("Turn Right Released");
    s.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

