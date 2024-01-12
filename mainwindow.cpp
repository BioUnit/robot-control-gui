#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LeftButton_pressed()
{
    qDebug("Turn Left Pressed");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_RightButton_pressed()
{
    qDebug("Turn Right Pressed");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_BackwardButton_pressed()
{
    qDebug("Move Backward Pressed");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_ForwardButton_pressed()
{
    qDebug("Move Forward Pressed");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_ForwardButton_released()
{
    qDebug("Move Forward Released");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_BackwardButton_released()
{
    qDebug("Move Backward Released");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_LeftButton_released()
{
    qDebug("Turn Left Released");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_RightButton_released()
{
    qDebug("Turn Right Released");
    QThread::sleep(std::chrono::milliseconds{100});
}

