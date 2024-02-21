#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tcpsocket.h"
#include <QDebug>
#include <QThread>
#include <QCamera>
#include <QAudioDevice>
#include <QPermission>
#include <QAction>
#include <QMediaRecorder>
#include <QVideoWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    s.doConnect();
    ui->setupUi(this);
    //camera_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::camera_init() {
#if QT_CONFIG(permissions)
    // camera
    QCameraPermission cameraPermission;
    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this, &MainWindow::camera_init);
        return;
    case Qt::PermissionStatus::Denied:
        qWarning("Camera permission is not granted!");
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }
    // microphone
    QMicrophonePermission microphonePermission;
    switch (qApp->checkPermission(microphonePermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(microphonePermission, this, &MainWindow::camera_init);
        return;
    case Qt::PermissionStatus::Denied:
        qWarning("Microphone permission is not granted!");
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }
#endif

    m_audioInput.reset(new QAudioInput);
    m_captureSession.setAudioInput(m_audioInput.get());

    // Camera devices:

    videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    updateCameras();

    setCamera(QMediaDevices::defaultVideoInput());
}

void MainWindow::updateCameras(){
    ui->menuDevices->clear();
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraDevice.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);

        ui->menuDevices->addAction(videoDeviceAction);
    }
}

void MainWindow::setCamera(const QCameraDevice &cameraDevice){
    m_camera.reset(new QCamera(cameraDevice));
    m_captureSession.setCamera(m_camera.data());

    m_captureSession.setVideoOutput(ui->widget);

    m_camera->start();
}

void MainWindow::startCamera()
{
    m_camera->start();
}

void MainWindow::stopCamera()
{
    m_camera->stop();
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

