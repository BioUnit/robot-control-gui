#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tcpsocket.h"
#include "mycamera.h"
#include <QDebug>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    player = new QMediaPlayer(this);
    ui->setupUi(this);
    initSignals();

    /* camera stream */
    player->setVideoOutput(ui->widget);
    player->setSource(QUrl("udp://192.168.0.107:5000"));
    QThread::sleep(std::chrono::milliseconds{5000});

    /* PC camera */
    //my_camera.camera_init();
    //updateCameras();
    //setCamera();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSignals(){
    connect(ui->LeftButton, SIGNAL(pressed()), this, SLOT(LeftButton_pressed()));
    connect(ui->RightButton, SIGNAL(pressed()), this, SLOT(RightButton_pressed()));
    connect(ui->ForwardButton, SIGNAL(pressed()), this, SLOT(ForwardButton_pressed()));
    connect(ui->BackwardButton, SIGNAL(pressed()), this, SLOT(BackwardButton_pressed()));
    connect(ui->LeftButton, SIGNAL(released()), this, SLOT(LeftButton_released()));
    connect(ui->RightButton, SIGNAL(released()), this, SLOT(RightButton_released()));
    connect(ui->ForwardButton, SIGNAL(released()), this, SLOT(ForwardButton_released()));
    connect(ui->BackwardButton, SIGNAL(released()), this, SLOT(BackwardButton_released()));
    connect(ui->TcpConnButton, SIGNAL(clicked()), this, SLOT(TcpConnButton_clicked()));
    connect(ui->KeyboardSwitchButton, SIGNAL(clicked()), this, SLOT(KeyboardSwitchButton_clicked()));
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

void MainWindow::LeftButton_pressed() {
    qDebug("Turn Left Pressed");
    my_socket.write("LP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::RightButton_pressed() {
    qDebug("Turn Right Pressed");
    my_socket.write("RP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::BackwardButton_pressed() {
    qDebug("Move Backward Pressed");
    my_socket.write("BP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::ForwardButton_pressed() {
    qDebug("Move Forward Pressed");
    my_socket.write("FP");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::ForwardButton_released() {
    qDebug("Move Forward Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::BackwardButton_released() {
    qDebug("Move Backward Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::LeftButton_released() {
    qDebug("Turn Left Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::RightButton_released() {
    qDebug("Turn Right Released");
    my_socket.write("RR");
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::TcpConnButton_clicked() {
    if(my_socket.isConnected() == true){
        my_socket.TcpDisconnect();
        disconnect(player, SIGNAL(errorChanged()), this, SLOT(MediaErrorReceived()));
        player->stop();
        ui->TcpConnButton->setText("Connect");
    } else {
        if(my_socket.TcpConnect() == true){
            player->setSource(QUrl(NULL));
            player->setSource(QUrl("udp://192.168.0.107:5000"));
            connect(player, SIGNAL(errorChanged()), this, SLOT(MediaErrorReceived()));
            qDebug() << "Log: TCP connection established";
            ui->TcpConnButton->setText("Disconnect");
            player->play();
        } else {
            disconnect(player, SIGNAL(errorChanged()), this, SLOT(MediaErrorReceived()));
            player->stop();
            ui->TcpConnButton->setText("Error/Reconnect");
        }
    }
    QThread::sleep(std::chrono::milliseconds{100});
}

void MainWindow::KeyboardSwitchButton_clicked() {

}

/* Recconects video stream if any errors occur */
void MainWindow::MediaErrorReceived() {
    qDebug() << "Error: No input video stream found";
    player->stop();
    player->setSource(QUrl(NULL));
    player->setSource(QUrl("udp://192.168.0.107:5000"));
    player->play();
}
