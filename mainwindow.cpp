#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tcpsocket.h"
#include "mycamera.h"
#include <QDebug>
#include <QThread>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    my_socket.doConnect();
    ui->setupUi(this);
    /* camera stream input */
    QMediaPlayer *player;
    player = new QMediaPlayer(this);
    player->setVideoOutput(ui->widget);
    player->setSource(QUrl("udp://192.168.0.107:5000"));
    player->play();

    /* PC camera */
    //my_camera.camera_init();
    //updateCameras();
    //setCamera();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCameras(){
    ui->menuDevices->clear();
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraDevice.description(), my_camera.videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);
        ui->menuDevices->addAction(videoDeviceAction);
    }
}

void MainWindow::setCamera(){
    my_camera.m_camera.reset(new QCamera(QMediaDevices::defaultVideoInput()));
    my_camera.m_captureSession.setCamera(my_camera.m_camera.data());
    my_camera.m_captureSession.setVideoOutput(ui->widget);
    my_camera.m_camera->start();
}

void MainWindow::on_LeftButton_pressed()
{
    qDebug("Turn Left Pressed");
    my_socket.write("LP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_RightButton_pressed()
{
    qDebug("Turn Right Pressed");
    my_socket.write("RP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_BackwardButton_pressed()
{
    qDebug("Move Backward Pressed");
    my_socket.write("BP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_ForwardButton_pressed()
{
    qDebug("Move Forward Pressed");
    my_socket.write("FP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_ForwardButton_released()
{
    qDebug("Move Forward Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_BackwardButton_released()
{
    qDebug("Move Backward Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_LeftButton_released()
{
    qDebug("Turn Left Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::on_RightButton_released()
{
    qDebug("Turn Right Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

